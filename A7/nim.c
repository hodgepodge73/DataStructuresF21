#include "nim.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// memory allocation and free functions
int *new_board( int board_size )
{
    int *returnArray = malloc(board_size * sizeof(int));
    if (returnArray == NULL)
    {
        fprintf(stderr, "ERROR: retrunArray not malloc'd");
        exit(1);
    }
    return returnArray;
}
struct node *mk_nim_hash( int max_hash, int board_size, int *start_board )
{
    struct node *returnNode = malloc(sizeof(struct node) * max_hash);
    if (returnNode == NULL)
    {
        fprintf(stderr, "ERROR: Nim hash failed");
        exit(1);
    }
    for (int i = 0; i < max_hash; i++)
    {
        returnNode[i].moves = -1;
        returnNode[i].move = NULL;
        returnNode[i].nimsum = -1;
        returnNode[i].board = hash2board(board_size, start_board, i);
    }
    return returnNode;
}
void free_board( int *board )
{
    free(board);
}
void free_nim_hash( int max_hash, struct node *nim_hash )
{
    for (int i = 0; i < max_hash; i++)
    {
        free(nim_hash[i].move);
        free(nim_hash[i].board);
    }
    free(nim_hash);
}

// other functions for students to write
int *board_from_argv( int board_size, char **argv )
{
    int *returnBoard = malloc(sizeof(int) * board_size);
    for (int i = 0; i < board_size; i++)
    {
        returnBoard[i] = atoi(argv[i]);
        //printf("%d", returnBoard[i]);
    }
    return returnBoard;
}
int *copy_board( int board_size, int *board )
{
    int * new_board = malloc(board_size * sizeof(int));
    for (int i = 0; i < board_size; i++)
    {
        new_board[i] = board[i];
    }
    return new_board;
}
int game_over( int board_size, int *board )
{
    int sum = 0;
    for (int i = 0; i < board_size; i++)
    {
        sum += board[i];
    }
    if (sum == 1)
    {
        return 1;
    }
    if (sum == 0)
    {
        fprintf(stderr, "ERROR: All matches gone you lose");
        exit(1);
    }
    return 0;
}
void join_graph( struct node *nim_hash, int hash, int board_size, 
    int *start_board )
    {
        if (nim_hash[hash].moves != -1)
        {
            return;
        }
        //calculate total num of possible moves
        // | || ||| 6 matches for x matches per row there is x possible moves
        //therefore sum of matches is the same as sum of possible moves
        int possibleMoves = 0;
        int * temp = malloc(sizeof(int) * board_size);
        int * temp1 = malloc(sizeof(int) * board_size);
        temp1 = hash2board(board_size, start_board, hash);
        for (int i = 0; i < board_size; i++)
        {
            possibleMoves += temp1[i];
            temp[i] = temp1[i];
        }
        nim_hash[hash].move = malloc(sizeof(struct move) * possibleMoves);
        nim_hash[hash].moves = possibleMoves;
        nim_hash[hash].nimsum = compute_nimsum(board_size, temp1);
        int count = 0;
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 1; j < temp1[i] + 1; j++)
            {
                nim_hash[hash].move[count].matches = j;
                nim_hash[hash].move[count].row = i;
                temp[i] -= j;
                nim_hash[hash].move[count].hash = board2hash(board_size, start_board, temp);
                join_graph(nim_hash, nim_hash[hash].move[count].hash, board_size, start_board);
                temp[i] += j;
                count += 1;
            }
        }
    }

int compute_nimsum( int board_size, int *board )
{
    int returnXOR = board[0];
    int sum = 0;
    if (board[0] > 1){
        sum = 1;
    }
    for (int i = 1; i < board_size; i++)
    {
        returnXOR = returnXOR ^ board[i];
        if (board[i] > 1)
        {
            sum = 1;
        }
    }
    if (sum == 0)
    {
        return (returnXOR^1);
    }
    return returnXOR;
}


