#include <stdio.h>
#include "memsys.h"

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

struct Array
{
    unsigned int width;
    unsigned int nel;
    unsigned int capacity;
    int data;
};

struct  Array *newArray(struct memsys *memsys, unsigned int width, unsigned int capacity);

void readItem(struct memsys *memsys, struct Array *array, unsigned int index, void *dest);

void writeItem(struct memsys *memsys, struct Array *array, unsigned int index, void *src);

void contract(struct memsys *memsys, struct Array *array);

void freeArray(struct memsys *memsys, struct Array *array);

void appendItem(struct memsys *memsys, struct Array *array, void *src);

void insertItem(struct memsys *memsys, struct Array *array, unsigned int index, void *src);

void prependItem(struct memsys *memsys, struct Array *array, void *src);

void deleteItem(struct memsys *memsys, struct Array *array, unsigned int index);

//Bonus
int findItem(struct memsys *memsys, struct Array *array, int (*compar)(const void *, const void *), void *target);

int searchItem(struct memsys *memsys, struct Array *array, int (*compar)(const void *, const void *), void *target);

