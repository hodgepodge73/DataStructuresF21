#include "list.h"

/*
Student Name: Ethan Hodge
Student ID: 1124633
Due Date: 14 10 2021
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


void push( struct memsys *memsys, int *node_ptr,void *src, size_t width ){
    //add to top 
    int data_ptr = memmalloc(memsys, width);
    setval(memsys, src, width, data_ptr);
    struct Node newNode;
    newNode.data = data_ptr;
    newNode.next = *node_ptr;
    *node_ptr = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &newNode, sizeof(struct Node), *node_ptr);
    
}

void insert( struct memsys *memsys, int *node_ptr, void *src, size_t width ){
    //add after a list.
    struct Node oldNode;
    getval(memsys, &oldNode, sizeof(struct Node), *node_ptr);
    int data_ptr = memmalloc(memsys, width);
    setval(memsys, src, width, data_ptr);
    struct Node newNode;
    newNode.data = data_ptr;
    newNode.next = oldNode.next;
    oldNode.next = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &newNode, sizeof(struct Node), oldNode.next);
    setval(memsys, &oldNode, sizeof(struct Node), *node_ptr);
}

void delete( struct memsys *memsys, int *node_ptr ){
    //delete after passed node
    struct Node oldNode;
    int delNode;
    int nextNode;
    getval(memsys, &oldNode, sizeof(struct Node), *node_ptr);
    delNode  = next(memsys, node_ptr);
    nextNode = next(memsys, &delNode);
    oldNode.next = nextNode;
    memfree(memsys, delNode);
    setval(memsys, &oldNode, sizeof(struct Node), *node_ptr);
}

void readHead( struct memsys *memsys, int *node_ptr, void *dest, unsigned int width ){
    //read top/read node
    if (isNull(memsys, node_ptr)){
        fprintf(stderr, "ERROR: List empty");
        exit(-1);
    }
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    getval(memsys, dest, width,temp.data );

}

void pop( struct memsys *memsys, int *node_ptr ){
    //remove top
    if (isNull(memsys, node_ptr)){
        fprintf(stderr, "ERROR: List empty");
        exit(-1);
    }
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    memfree(memsys, *node_ptr);
    *node_ptr = temp.next;
    memfree(memsys, temp.data);
    
}

int next( struct memsys *memsys, int *node_ptr ){
    //return next
    if (isNull(memsys, node_ptr)){
        fprintf(stderr, "ERROR: List empty");
        exit(-1);
    }
    
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    return temp.next;
}

int isNull( struct memsys *memsys, int *node_ptr ){
    //check for null
    if (node_ptr == NULL || *node_ptr == MEMNULL){
        return 1;
    }
    return 0;
}

struct List *newList( struct memsys *memsys, unsigned int width ){
    //make list
    struct List *returnList = malloc(width); 
    if (returnList == NULL ){
        fprintf(stderr, "Error: Memory not malloc'd");
        exit(-1);
    }
    returnList->width = width;
    returnList->head = MEMNULL;
    return returnList;
}

void freeList( struct memsys *memsys, struct List *list ){
    //free list
    while(!isEmpty(memsys, list)){
        pop(memsys, &list->head);
    }
    free(list);

}

int isEmpty( struct memsys *memsys, struct List *list ){
    if (list->head == MEMNULL){
        return 1;
    }
    return 0;
}

void readItem( struct memsys *memsys, struct List *list, unsigned int index, void *dest ){
    if (index < 0){
        //neg index
        fprintf(stderr, "ERROR: Index out of Bounds");
        exit(-1);
    }
    if (index == 0){
        //head
        readHead(memsys, &list->head, dest, list->width);
    }
    else{
        //go to index and read
        struct Node temp;
        int returnAdd;
        int curr = 0;
        getval(memsys, &temp, sizeof(struct Node), list->head);
        returnAdd = temp.next;
        while (!isNull(memsys, &returnAdd) && curr < index - 1){
            returnAdd = next(memsys, &returnAdd);
            curr += 1;
            //getval(memsys, &temp, sizeof(struct Node),temp->next)
        }        
        if (returnAdd == MEMNULL){
            fprintf(stderr, "ERROR: Index out of Bounds");
            exit(-1);
        }
        else {
            getval(memsys, &temp, sizeof(struct Node), returnAdd);
            getval(memsys, dest, list->width, temp.data);
        }
    }
}

void appendItem( struct memsys *memsys, struct List *list,void *src ){
    int returnAdd = list->head;
    if (isEmpty(memsys, list) == 1){
        //add to front == add to end when empty
        prependItem(memsys, list, src);
    }
    else {
        //go to and add
        int actualReturn = returnAdd;
        int curr = 0;
        while (!isNull(memsys, &returnAdd)){
            actualReturn = returnAdd;
            returnAdd = next(memsys, &returnAdd);
            curr += 1;
        }
        insert(memsys, &actualReturn, src, list->width);
    }
        
}

void insertItem( struct memsys *memsys, struct List *list, unsigned int index, void *src ){
    if (index < 0){
        fprintf(stderr, "ERROR: index invalid");
        exit(-1);
    }
    if (index == 0){
        push(memsys, &list->head, src, list->width);
    }
    else{
        //go to and insert
        struct Node temp;
        int curr = 0;
        int returnAdd = list->head;
        getval(memsys, &temp, sizeof(struct Node), list->head);
        if (!isNull(memsys, &temp.next)){
            returnAdd = temp.next;
        }
        while (!isNull(memsys, &returnAdd) && curr < index - 2 && temp.next != -1){
            returnAdd = next(memsys, &returnAdd);
            curr += 1;
        }
        insert(memsys, &returnAdd, src, list->width);
    }
}

void prependItem( struct memsys *memsys, struct List *list, void *src){
    insertItem(memsys, list, 0, src);
}

void deleteItem( struct memsys *memsys, struct List *list, unsigned int index){
    if (index == 0){
        //weird head stuff
        int nextH = next(memsys, &list->head);
        memfree(memsys, list->head);
        list->head = nextH;
    }
    else{
        struct Node temp;
        int curr = 0;
        int returnAdd = list->head;
        getval(memsys, &temp, sizeof(struct Node), list->head);
        while (!isNull(memsys, &returnAdd) && curr < index-1){
            returnAdd = next(memsys, &returnAdd);
            curr += 1;
        }
        delete(memsys, &returnAdd);
    }
}

//bonus
int findItem( struct memsys *memsys, struct List *list, int (*compar)(const void*, const void*), void *target ){
    //go till find
    struct Node temp;
    int returnAdd = list->head;
    int *tempVal = malloc(list->width);
    int count = 0;
    while (!isNull(memsys, &returnAdd)){
        getval(memsys, &temp, sizeof(struct Node), returnAdd);
            getval(memsys, tempVal, list->width, temp.data);
            if (compar(tempVal, target)==0){
                free(tempVal);
                return count;
            }
            returnAdd = next(memsys, &returnAdd);
            count ++;
    }
    free(tempVal);
    return -1;
}


void printList(struct memsys *memsys, struct List *list){
    //assisting function to help make sure it works
    struct Node temp;
    double *tempVal = malloc (sizeof (list->width));
    //printf("%d %d\n", list->head, list->width);
    getval(memsys, &temp, sizeof(struct Node), list->head);
    getval(memsys, tempVal, list->width, temp.data);
   // printf("temp.data: %d temp.next: %d, tempVal: %d\n", temp.data, temp.next, *tempVal);
    while (temp.next != MEMNULL){
        getval(memsys, &temp, sizeof(struct Node), temp.next);
        getval(memsys, tempVal, list->width, temp.data);
        printf("temp.data: %d temp.next: %d, tempVal: %lf\n", temp.data, temp.next, (double)*tempVal);
        //printf("%d %d\n", *tempVal, temp.next);
    }
    //printf("%d\n", *tempVal);
    free(tempVal);
}
