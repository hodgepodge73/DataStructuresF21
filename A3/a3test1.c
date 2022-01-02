#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "memsys.h"

int cmp( const void *p1, const void *p2 )
{
  int *i1, *i2;

  i1 = p1;
  i2 = p2;
  printf("%d, %d\n", *i1, *i2);
  return *i1 - *i2;
}


int main( int argc, char **argv )
{
  int i,j;
  int ten = 10, three=3;
  struct memsys *memsys;
  struct List *list;

  // struct Node *list;
  // struct Node **list_ptr;
  //

  memsys = init( 1024, 128 );

  list = newList( memsys, sizeof( int ) );

  printf( "isEmpty = %d\n", isEmpty( memsys, list ));
  // should print 1
 //print(memsys);
  // should print isEmpty=0 and j increasing from 0 to 9
  // int p = 9;
  // //push(memsys, &list->head, &p, sizeof(int));
  // insertItem(memsys, list, 0, &p);
  // print(memsys);
  // printf("%d %d\n", list->head, list->width);
  // struct Node temp;
  // int q = 0;
  // //getval(memsys, &temp, sizeof(struct Node), list->head);
  // p = 111;
  // print(memsys);
  // prependItem(memsys, list, &p);
  // printList(memsys, list);
  // readHead(memsys, &list->head, &q, list->width);
  // printf("HEAD: %d \n", q);
  // deleteItem(memsys, list, 0);

  // readHead(memsys, &list->head, &q, list->width);
  // printf("HEAD: %d \n", q);
  // p = 12;
  // appendItem(memsys, list, &p);
  // printList(memsys, list);
  // //insert(memsys, &list->head,&p, list->width);
  // //printf("%d %d\n", list->head, list->width);
  // printList(memsys, list);
  // //printf("HERE3\n");
  // int addy = list->head;
  // //printf("HERE1\n");
  // addy = next(memsys, &list->head);
  // //printf("HERE2 %d \n", addy);
  // getval(memsys, &temp, sizeof(struct Node), addy);
  // //printf("HERE3\n");
  // printf("\n%d %d\n", temp.data, temp.next);
  // p = 12;
  // printf("%d\n", findItem(memsys, list, cmp, &p));
  // //printf("HERE4\n");
  // getval(memsys, &q, sizeof(int), temp.data);
  //printf("HERE5\n");
  //printf("\n%d \n", q);
  printf( "prependItem\n" );
  for (i=0;i<10;i++)
  {
    printf( "%d: ", i );
    prependItem( memsys, list, &i );
   //print(memsys);
    readItem( memsys, list, 0, &j );
      // should print 0
    printf( "j = %d\n", j );
  }
  printf( "isEmpty = %d\n", isEmpty( memsys, list ) );
  //printList(memsys, list);
  for (i=11;i<21;i++)
  {
    printf( "%d: \n\n", i-1 );
    appendItem( memsys, list, &i );
    //printf( "%d: \n\n", i-1 );
    readItem( memsys, list, i-1, &j );
    printf( "j = %d\n", j );
  }
  
  insertItem( memsys, list, 10, &ten );
  fprintf( stderr, "1\n" );
  deleteItem( memsys, list, 3 );
  fprintf( stderr, "2\n" );

  // should print j decreasing from 9 to 0 and and then increasing from 10 to 20
  for ( i=0;i<20;i++)
  {
    readItem( memsys, list, i, &j );
    printf( "%d, ", j );
  }
  printf( "\n" );

  print( memsys );

  // should be at position 5 in the list
  printf( "%d is at %d\n", three, findItem( memsys, list, cmp, &three ) );

  while (!isEmpty(memsys,list))
  {
    deleteItem( memsys, list, 0 );
  }
  // should print isEmpty = 1
  printf( "isEmpty = %d\n", isEmpty( memsys, list ) );

  print( memsys );
  freeList(memsys, list);
  shutdown( memsys );

  return 0;
}

