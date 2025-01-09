#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define BOARD_SIZE 10
#define MINES_POINT -2
#define EMPTY_POINT -1

typedef struct mine {
    int x;
    int y;
} mine;

bool game_process();
void print_field(int8_t board[BOARD_SIZE][BOARD_SIZE]);
void filling_of_board(int8_t board[BOARD_SIZE][BOARD_SIZE]);