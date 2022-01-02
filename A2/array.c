#include "array.h"
#include <stdlib.h>
#include <stdbool.h>

/*
Student Name: Ethan Hodge
Student ID: 1124633
Due Date: 4 10 2021
Course: CIS*2520 Instructor: Kremer
I have exclusive control over this submission via my password.
By including this header comment, I certify that:
1) I have read and understood the policy on academic integrity.
2) I have completed Moodle's module on academic integrity.
3) I have achieved at least 80% on the academic integrity quiz
I assert that this work is my own. I have appropriate acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by me in its entirety.
*/

struct Array *newArray(struct memsys *memsys, unsigned int width, unsigned int capacity){
    struct Array *returnArr = malloc(sizeof(struct Array));
    int data_ptr = memmalloc(memsys, width*capacity);
    //check for succesful allocation
    if ( data_ptr == -1){
        fprintf( stderr, "Segmentation fault - Memory not allocated\n" );
        exit(-1);
    }
    returnArr->capacity = capacity;
    returnArr->width = width;
    returnArr->data = data_ptr;
    returnArr->nel = 0;
    //setval(memsys, &returnArr, sizeof(struct Array), array_ptr);
    //print(memsys);
    return returnArr;
}

void readItem(struct memsys *memsys, struct Array *array, unsigned int index, void *dest){
    if (index >= array->nel){
        fprintf( stderr, "Segmentation fault - Index out of bounds\n" );
        exit(-1);
    }
    getval(memsys, dest, array->width, array->data+index*(array->width));
}

void writeItem(struct memsys *memsys, struct Array *array, unsigned int index, void *src){
    if ((index > array->nel) || (index >= array->capacity)){
        fprintf( stderr, "Segmentation fault - Index out of bounds\n" );
        exit(-1);
    }
    //increment nel
    if ((array->nel) == index ){
        array->nel = array->nel + 1;
    }
    //use index*array->width to move over width bytes
    setval(memsys, src, array->width, array->data + index*(array->width));
}

//My interpretation is to shrink it
void contract(struct memsys *memsys, struct Array *array){
    if (array->nel == 0){
        fprintf( stderr, "Segmentation fault - No elements\n" );
        exit(-1);
    }
    array->nel -= 1;
}

//free
void freeArray(struct memsys *memsys, struct Array *array){
    memfree(memsys, array->data);
    free(array);
}

void appendItem(struct memsys *memsys, struct Array *array, void *src){
    writeItem(memsys, array, array->nel, src);
}

void insertItem(struct memsys *memsys, struct Array *array, unsigned int index, void *src){
    //works by first moving all to the right then adding it in at index
    void *ptr = malloc(array->width);
    int counter;
    printf("\n%d %d\n", index, array->nel);
    if ((index > array->nel + 1) || (index >= array->capacity)){
        fprintf( stderr, "Segmentation fault - Index out of bounds\n" );
        exit(-1);
    }
    if (array->nel >= array->capacity){
        fprintf( stderr, "Segmentation fault - Array Full\n" );
        exit(-1);
    }
    if (index == array->nel){
        appendItem(memsys, array, src);
        return;
    }
    if (array->nel == 0 && array->nel != index){
        fprintf( stderr, "Segmentation fault - Invalid Index" );
        exit(-1);
    }
    for (counter = array->nel - 1; counter >= index; counter--){
        printf("\n\n%d\n\n", counter+array->data);
        readItem(memsys, array, counter + array->data, ptr);
        
        writeItem(memsys, array, array->data + counter + 1, ptr);
    }
    writeItem(memsys, array, index, src);
    free(ptr);
}

void prependItem(struct memsys *memsys, struct Array *array, void *src){
    void *ptr = malloc(array->width);
    int counter;
    if (array->nel >= array->capacity){
        fprintf( stderr, "Segmentation fault - Array Full\n" );
        exit(-1);
    }
    for (counter = array->nel - 1; counter >= 0; counter--){
        readItem(memsys, array, counter + array->data, ptr);
        writeItem(memsys, array, array->data + counter + 1, ptr);
    }
    writeItem(memsys, array, array->data, src);
    free(ptr);
    //array->nel += 1;
    
}

void deleteItem(struct memsys *memsys, struct Array *array, unsigned int index){
    //find then shift left
   // printf("\n\n\n%d\n%d\n%d\n", index, array->nel, array->capacity);
    if ((index > array->nel) || (index >= array->capacity)){
        fprintf( stderr, "Segmentation fault - Index out of bounds\n" );
        exit(-1);
    }
    if (array->nel == 0){
        fprintf( stderr, "Segmentation fault - No elements\n" );
        exit(-1);
    }
    void *ptr = malloc(array->width);
    for (int counter = index; counter < array->nel-1; counter++){
        //printf("\n\nINDEX:%d \n", counter);
       readItem(memsys, array, counter + array->data + 1, ptr);
       writeItem(memsys, array, counter + array->data, ptr);
    }
    contract(memsys, array);
    free(ptr);
}

//Bonus
int findItem(struct memsys *memsys, struct Array *array, int (*compar)(const void *, const void *), void *target){
    //lin search
    bool done = false;
    int index = array->data;
    void *ptr = malloc(array->width);
    while(!done){
        if (index >= array->nel+array->data){
            free(ptr);
            return -1;
        }
        readItem(memsys, array, index, ptr);
        if (compar(ptr, target)==0){
            done = true;
        }
        else{
            index+=1;
        }
    }
    free(ptr);
    return index;
}

int searchItem(struct memsys *memsys, struct Array *array, int (*compar)(const void *, const void *), void *target){
    //bin search assuming sorted
    int mid = 0;
    int low = 0;
    int high = array->nel - 1;
    void *ptr = malloc(array->width);
    while (high >= low) {
        mid = (high + low) / 2;
        readItem(memsys, array, mid, ptr);
        if (compar(ptr, target)<0) {
            low = mid + 1;
        }
        else if (compar(ptr, target)>0) {
            high = mid - 1;
        }
        else {
            free(ptr);
            return mid;
        }
   }
   free(ptr);
   return -1;
}
