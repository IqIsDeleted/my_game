#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#define BOARD_SIZE 10
#define MINES_POINT -2
#define EMPTY_POINT -1
#define AMOUNT_OF_MINES 15

typedef struct mine {
  int x;
  int y;
} mine;

bool game_process();
void print_field(int8_t board[BOARD_SIZE][BOARD_SIZE]);
void filling_of_board(int8_t board[BOARD_SIZE][BOARD_SIZE]);
void lay_mines(int8_t board[BOARD_SIZE][BOARD_SIZE], int, int);
unsigned calculate_points(int8_t board[BOARD_SIZE][BOARD_SIZE], int, int);