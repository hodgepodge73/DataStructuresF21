#include <stdlib.h>
#include <stdio.h>
#include "memsys.h"

/*
Student Name: Ethan Hodge
Student ID: 1124633
Due Date: 27 10 2021
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


struct Node 
{
    int data;
    int lt;
    int gte;
}; 

struct Tree
{  
    unsigned int width;
    int root;
};

void attachNode( struct memsys *memsys, int *node_ptr, void *src, unsigned int width );

void attachChild( struct memsys *memsys, int *node_ptr,void *src, unsigned int width, int direction );

int comparNode( struct memsys *memsys, int *node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width);

int next( struct memsys *memsys, int *node_ptr, int direction );

void readNode( struct memsys *memsys, int *node_ptr, void *dest, unsigned int width);

void detachNode( struct memsys *memsys, int *node_ptr );

void freeNodes( struct memsys *memsys, int *node_ptr );

struct Tree *newTree( struct memsys *memsys, unsigned int width );

void freeTree( struct memsys *memsys, struct Tree *tree);

void addItem( struct memsys *memsys, struct Tree *tree, int (*compar)(const void*, const void*), void *src );

int searchItem( struct memsys *memsys, struct Tree *tree,int(*compar)(const void*, const void*),void *target);

void printTree(struct memsys *memsys, int *node_ptr, unsigned int width);
