#include "tree.h"

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


void attachNode( struct memsys *memsys, int *node_ptr, void *src, unsigned int width )
//find where it could go and full send DONT FIND
{
    //two memmallocs/set vals again
    struct Node newNode;
    int data_ptr = memmalloc(memsys, width);
    int new_ptr = memmalloc(memsys, sizeof(struct Node));
    if (data_ptr == MEMNULL || new_ptr == MEMNULL)
    {
        fprintf(stderr, "ERROR: Not malloced");
        exit(-1);
    }
    newNode.data = data_ptr;
    newNode.lt = MEMNULL;
    newNode.gte = MEMNULL;
    setval(memsys, src, width, data_ptr);
    setval(memsys, &newNode, sizeof(struct Node), new_ptr);
    *node_ptr = new_ptr;
}

void attachChild( struct memsys *memsys, int *node_ptr, void *src, unsigned int width, int direction )
//attach if direction is less than zero go to lt
{
    //get parent at node ptr
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    if (direction < 0)
    //call attach node to set in child node
    {
        int lt = temp.lt;
        attachNode(memsys, &lt, src, width);
        temp.lt = lt;
    }
    else
    {
        int gte = temp.gte;
        attachNode(memsys, &gte, src, width);
        temp.gte = gte;
    }
    //now update parent node
    setval(memsys, &temp, sizeof(struct Node), *node_ptr);
}

int comparNode( struct memsys *memsys, int *node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width)
//data in variable to data in the node
{
    //might have to malloc to get var val
    struct Node temp;
    //ERROR HERE ISH
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    void *tempVal = malloc (width);
    // printf("HERE width %d local%d", width, temp.data);
    //make sure passing right args to this function
    getval(memsys, tempVal, width, temp.data);
    //printf("HERE width %d", width);
    int returnVal = compar(target, tempVal);
    free(tempVal);
    //get val of node then get val of data then use compar
    //target with width is the variable to compar to
    //return >= 0 if gte return <0 if lt OR compar's return
    return returnVal;
}

int next( struct memsys *memsys, int *node_ptr, int direction )
//find next value given direction <0 = lt >=0 = gte
//To test
{
    //return node address in memsys
    int returnVal = 0;
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    if (direction < 0)
    {
        //printf("Lt %d", temp.lt);
        returnVal = temp.lt;
    }
    else
    {
        //printf("GTE %d", temp.gte);
        returnVal = temp.gte;
    }

    return returnVal;
}

void readNode( struct memsys *memsys, int *node_ptr, void *dest, unsigned int width)
//reads node
{
    //copy node data into destination
    if (*node_ptr == MEMNULL)
    {
        fprintf(stderr, "ERROR: Null node pointer");
        exit(-1);
    }
    //getval  of node_ptr
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    getval(memsys, dest, width, temp.data);
}

void detachNode( struct memsys *memsys, int *node_ptr )
//used in free tree
//takes away a leafnode
{
    if (*node_ptr==MEMNULL)
    {
        fprintf(stderr, "ERROR: Null pointer");
        exit(-1);
    }
    //get node to make sure no children memfree node struct and data
    struct Node temp;
    getval(memsys, &temp, sizeof(struct Node), *node_ptr);
    memfree(memsys, temp.data);
    memfree(memsys, *node_ptr);
    *node_ptr = MEMNULL;
    
    //temp.
    //but first make sure no children
}

void freeNodes( struct memsys *memsys, int *node_ptr )
//go to depths and then start freeing on the way up
{
    //recursively call till detach node
    if (*node_ptr != MEMNULL)
    {
        int left = next(memsys, node_ptr, -1);
        int right = next(memsys, node_ptr, 1);
        freeNodes(memsys, &left);
        freeNodes(memsys, &right);
        detachNode(memsys, node_ptr);
    }

}

struct Tree *newTree( struct memsys *memsys, unsigned int width )
//return address of tree with width set to width and root set to memnull
{
    struct Tree *returnTree = malloc(sizeof(struct Tree));
    if (returnTree == NULL)
    {
        fprintf(stderr, "ERROR: could not malloc tree");
        exit(-1);
    }
    returnTree->width = width;
    returnTree->root = MEMNULL;
    return returnTree;
}

void freeTree( struct memsys *memsys, struct Tree *tree)
{
    //free nodes on root
    freeNodes(memsys, &tree->root);
    free(tree);
    //then free(tree);
}

void addItem( struct memsys *memsys, struct Tree *tree, int (*compar)(const void*, const void*), void *src )
//add item in right spot using compar
{
    if (tree->root == MEMNULL)
    {
        //tree->width or sizeof(struct Node);
        attachNode(memsys, &tree->root, src, tree->width);
    }
    else
    {
        int done = 0;
        struct Node temp;
        int current = tree->root;
        int next_ptr;
        getval(memsys, &temp, sizeof(struct Node), tree->root);
        //getval(memsys, &tempVal, tree->width, temp.data);
        while (!done)
        {
            
            if (comparNode(memsys, &current, compar, src, tree->width) < 0)
            {
                //printf("leftHERE");
                next_ptr = temp.lt;
                //next(memsys, &current, -1);
                if (next_ptr == MEMNULL)
                {
                    attachChild(memsys, &current, src, tree->width, -1);
                    done = 1;
                }
                else
                {
                    current = temp.lt;
                    getval(memsys, &temp, sizeof(struct Node), temp.lt);
                }
                //printf("HERE");
            }
            else 
            {
               // printf("32HERE");
                next_ptr = temp.gte;
                //next(memsys, &current, 1);
                if (next_ptr == MEMNULL)
                {
                    attachChild(memsys, &current, src, tree->width, 1);
                    done = 1;
                }
                else
                {
                    current = temp.gte;
                    getval(memsys, &temp, sizeof(struct Node), temp.gte);
                    //getval(memsys, &tempVal, tree->width, temp.data);
                }
                
                
            }
            
        }
    }
    //loop through tree
    
    //grab node from before empty
}

int searchItem( struct memsys *memsys, struct Tree *tree,int(*compar)(const void*, const void*),void *target)
//recurse through? loop through and find the val that matches
//get val to target
{
    
    int done = 0;
    struct Node temp;
    int current = tree->root;
    int next_ptr;
    //struct record tempr;

    getval(memsys, &temp, sizeof(struct Node), tree->root);
    //getval(memsys, &tempVal, tree->width, temp.data);
    while (!done)
    {
        printf("COMPAR NODE: %d\n", comparNode(memsys, &current, compar, target, tree->width));
        if (comparNode(memsys, &current, compar, target, tree->width) < 0)
        {
            next_ptr = temp.lt;
            if (next_ptr == MEMNULL)
            {
                //attachChild(memsys, &current, src, tree->width, -1);
                return 0;
            }
            else
            {
                current = temp.lt;
                getval(memsys, &temp, sizeof(struct Node), temp.lt);
            }
        }
        else if (comparNode(memsys, &current, compar, target, tree->width) > 0)
        {
            
            next_ptr = temp.gte;
            if (next_ptr == MEMNULL)
            {
                //attachChild(memsys, &current, src, tree->width, 1);
                return 0;
            }
            else
            {
                current = temp.gte;
                getval(memsys, &temp, sizeof(struct Node), temp.gte);
            }           
        
        }
        else{
            printf("FOUND: ");
            getval(memsys, target, tree->width, temp.data);
            return 1;
        }  
    }
    //printf("NOT FOUND: ");
    return 0;
}

void printTree(struct memsys *memsys, int *node_ptr, unsigned int width)
{                 
    int *temp_data = malloc(width);
    int lt=0, gte=0;
    readNode(memsys, node_ptr, temp_data, width);
    if (*node_ptr != MEMNULL)
    {
        lt = next(memsys, node_ptr, -1);
        gte = next(memsys, node_ptr, 1);
        //printf("1\n");
    }    
    if (lt == MEMNULL && gte == MEMNULL)
    {
        printf("Value of node = %d\n", *temp_data); 
    }
    else
    {
        
        if (gte == MEMNULL)
        {
            printf("Value of node = %d\n", *temp_data); 
            printTree(memsys, &lt, width); 
            
        }
        else if (lt == MEMNULL)
        {
            printf("Value of node = %d\n", *temp_data); 
            printTree(memsys, &gte, width); 
            
        }
        else{
            
            printTree(memsys, &lt, width); 
            printf("Value of node = %d\n", *temp_data); 
            printTree(memsys, &gte, width); 
            //printf("Value of node = %d\n", *temp_data); 
        }
    
        
        //printf("Value of node = %d\n", *temp_data);  
    }
    //printf("Value of node = %d\n", *temp_data);  
    free(temp_data);
}
