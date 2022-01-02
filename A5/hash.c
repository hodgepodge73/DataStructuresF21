#include "hash.h"

/*
Student Name: Ethan Hodge
Student ID: 1124633
Due Date: 4 11 2021
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



struct HashTable *createTable( struct memsys *memsys, unsigned int capacity, unsigned int width, int (*hash)(void *, int), int (*compar)(const void *, const void*))
{
    struct HashTable *returnTable = malloc(sizeof(struct HashTable));
    int data_ptr = memmalloc(memsys, capacity*sizeof(int));
    int def = MEMNULL;
    if (returnTable == NULL || data_ptr == MEMNULL)
    {
        fprintf(stderr, "ERROR: memory not malloc'd");
        exit(-1);
    }
    returnTable->capacity = capacity;
    returnTable->width = width;
    returnTable->nel = 0;
    returnTable->hash = hash;
    returnTable->compar = compar;
    returnTable->data = data_ptr;
    //set all values to memnull
    for (int i = 0; i < capacity; i ++)
    {
        setval(memsys, &def, sizeof(int), returnTable->data + i*sizeof(int));
    }
    return returnTable;
}

void addElement( struct memsys *memsys, struct HashTable *table, int addr )
{
    //add element to table
    if (table->nel == table->capacity)
    {
        fprintf(stderr, "ERROR hash table full");
        exit(-1);
    }
    int location, tempInt;
    void *tempVal = malloc(table->width);
    getval(memsys, tempVal, table->width, addr);
    location = table->hash(tempVal, table->capacity);
    getval(memsys, &tempInt, sizeof(int), location*sizeof(int) + table->data);
    //linear probing if hash fails
    while (tempInt != MEMNULL)
    {
        location += 1;
        location %= table->capacity;
        getval(memsys, &tempInt, sizeof(int), ((location))*sizeof(int) + table->data);
    }
    table->nel += 1;
    
    setval(memsys, &addr, sizeof(int), location*sizeof(int) + table->data);
    free(tempVal);
}

int getElement( struct memsys *memsys, struct HashTable *table, void *key )
{
    int location = table->hash(key, table->capacity);
    int firstLocal = location;
    int memsysLocation;
    void *tempVal = malloc(table->width);
    getval(memsys, &memsysLocation, sizeof(int), sizeof(int)*location+table->data);
    if (memsysLocation != MEMNULL)
    {
        getval(memsys, tempVal, table->width, memsysLocation);
    }
    //linear probing
    while (table->compar(key, tempVal) != 0 && memsysLocation != MEMNULL)
    {
        
        location += 1;
        location %= table->capacity;
        
        getval(memsys, &memsysLocation, sizeof(int), sizeof(int)*location+table->data);
        if (location == firstLocal)
        {
            free(tempVal);
            return MEMNULL;
        }
        if (MEMNULL == memsysLocation)
        {
           // printf("HERE");
            free(tempVal);
            return MEMNULL;
        }
        
        getval(memsys, tempVal, table->width, memsysLocation);
    }
    
    if (memsysLocation == MEMNULL)
    {
        free(tempVal);
        return MEMNULL;
    }
    free(tempVal);
   
    return memsysLocation;
}
void freeTable(struct memsys *memsys, struct HashTable *table)
{
    //free the table
    memfree(memsys, table->data);
    free(table);
}

int hashAccuracy( struct memsys *memsys, struct HashTable *table )
{
    int returnVal = 0;
    int hashed;
    int real;
    void *tempVal = malloc(table->width);
    int locale;
    //go through each element and check for hashed and index
    for (int i = 0; i < table->capacity; i++)
    {
        getval(memsys, &locale, sizeof(int), table->data + i * sizeof(int));
        if (locale != MEMNULL)
        {
            getval(memsys, tempVal, table->width, locale);
            hashed = table->hash(tempVal, table->capacity);
            real = getId(memsys, table, tempVal);
            if (real < hashed)
            {
                returnVal +=  table->capacity - hashed + real;
            }
            else 
            {
                returnVal += real - hashed;
            }
        }
    }
    free(tempVal);
    return returnVal;
}

int getId( struct memsys *memsys, struct HashTable *table, void *key ){
    //returns the index location of a given element
    int location = table->hash(key, table->capacity);
    int memsysLocation;
    void *tempVal = malloc(table->width);
    getval(memsys, &memsysLocation, sizeof(int), sizeof(int)*location+table->data);
    if (memsysLocation != MEMNULL){
        getval(memsys, tempVal, table->width, memsysLocation);
    }
    while (table->compar(key, tempVal) != 0 && memsysLocation != MEMNULL)
    {
        location += 1;
        location %= table->capacity;
        
        getval(memsys, &memsysLocation, sizeof(int), sizeof(int)*location+table->data);
        if (MEMNULL == memsysLocation)
        {
            free(tempVal);
            return MEMNULL;
        }
        
        getval(memsys, tempVal, table->width, memsysLocation);
    }
    
    if (memsysLocation == MEMNULL)
    {
        free(tempVal);
        return MEMNULL;
    }
    free(tempVal);
    return location;
}
