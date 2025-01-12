#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 9
#define MINES_POINT -2
#define EMPTY_POINT -1
#define AMOUNT_OF_MINES 14
#define RED_FLAG '#'
#define mine_x mines[i].x
#define mine_y mines[i].y

typedef char* string_t;

typedef struct minesweeper_cell {
  int x;
  int y;
  bool red_flag;
  string_t input_str;
} minesweeper_cell_t;

typedef struct mine {
  int x;
  int y;
} mine_t;

void start_text();
bool game_process();
void print_field(int8_t board[BOARD_SIZE][BOARD_SIZE]);
void filling_of_board(int8_t board[BOARD_SIZE][BOARD_SIZE]);
bool update_cell(minesweeper_cell_t*);
void lay_mines(int8_t board[BOARD_SIZE][BOARD_SIZE], int, int, mine_t mines[AMOUNT_OF_MINES]);
unsigned calculate_points(int8_t board[BOARD_SIZE][BOARD_SIZE], int, int);