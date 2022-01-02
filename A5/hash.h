#include <stdio.h>
#include <stdlib.h>
#include "memsys.h"

struct HashTable
{
    unsigned int capacity;
    unsigned int nel;
    unsigned int width;
    int data;
    int (*hash) (void *, int);
    int (*compar)(const void *, const void *);
};

//nel is number l
//cap is max
//data points to array where elements are stored
//width is width of element

struct HashTable *createTable( struct memsys *memsys, unsigned int capacity, unsigned int width, int (*hash)(void *, int), int (*compar)(const void *, const void*));

void addElement( struct memsys *memsys, struct HashTable *table, int addr );

void freeTable(struct memsys *memsys, struct HashTable *table);

int getElement( struct memsys *memsys, struct HashTable *table, void *key );

int hashAccuracy( struct memsys *memsys, struct HashTable *table );

int getId( struct memsys *memsys, struct HashTable *table, void *key );

