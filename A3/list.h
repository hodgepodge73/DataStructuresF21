#include <stdio.h>
#include <stdlib.h>
#include "memsys.h"

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

struct Node {
    int data;
    int next;
};

struct List{
    unsigned int width;
    int head;
};

void push( struct memsys *memsys, int *node_ptr,void *src, size_t width );

void insert( struct memsys *memsys, int *node_ptr, void *src, size_t width );

void delete( struct memsys *memsys, int *node_ptr );

void readHead( struct memsys *memsys, int *node_ptr,void *dest, unsigned int width );

void pop( struct memsys *memsys, int *node_ptr );

int next( struct memsys *memsys, int *node_ptr );

int isNull( struct memsys *memsys, int *node_ptr );

struct List *newList( struct memsys *memsys, unsigned int width );

void freeList( struct memsys *memsys, struct List *list );

int isEmpty( struct memsys *memsys, struct List *list );

void readItem( struct memsys *memsys, struct List *list, unsigned int index, void *dest );

void appendItem( struct memsys *memsys, struct List *list,void *src );

void insertItem( struct memsys *memsys, struct List *list, unsigned int index, void *src );

void prependItem( struct memsys *memsys, struct List *list, void *src);

void deleteItem( struct memsys *memsys, struct List *list, unsigned int index);

//bonus
int findItem( struct memsys *memsys, struct List *list, int (*compar)(const void*, const void*), void *target );

void printList(struct memsys *memsys, struct List *list);

