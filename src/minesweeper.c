#include "minesweeper.h"

int main() {
  initscr();
  start_text();
  if (game_process()) {
    printw("You win!\n");
  } else {
    printw("You lose!\n");
  }
  printw("Press any key to exit");
  refresh();
  getch();
  endwin();
  return 0;
}

bool is_mine(mine_t mines[AMOUNT_OF_MINES], int x, int y) {
  bool res = 0;
  for (int i = 0; i < AMOUNT_OF_MINES && res == 0; ++i) {
    if (mine_x == x && mine_y == y) {
      res = 1;
    }
  }
  return res;
}

void lay_mines(int8_t board[BOARD_SIZE][BOARD_SIZE], int start_x, int start_y,
               mine_t mines[AMOUNT_OF_MINES]) {
  srand(time(NULL));
  for (unsigned i = 0; i < AMOUNT_OF_MINES; ++i) { // функция с ошибкой. Пока не нашел.
    do {
      mine_x = rand() % BOARD_SIZE;
      mine_y = rand() % BOARD_SIZE;
    } while ((mine_x < start_x - 1 || mine_x > start_x + 1) ||
             (mine_y < start_y - 1 || mine_y > start_y + 1) ||
             (board[mine_x][mine_y] != EMPTY_POINT));

    board[mine_x][mine_y] = MINES_POINT;
  }
}

bool game_process() {
  int8_t board[BOARD_SIZE][BOARD_SIZE];
  short res = 2;
  minesweeper_cell_t cell;
  mine_t mines[AMOUNT_OF_MINES];
  bool mines_flag = 1;
  filling_of_board(board);
  unsigned points = 0;
  while (res == 2) {
    clear();
    print_field(board);
    refresh();
    printw("\nEnter coordinates: ");
    cell.input_str = (string_t)calloc(16, sizeof(char));
    scanw("%s", cell.input_str);
    update_cell(&cell);
    mines_flag ? lay_mines(board, cell.x, cell.y, mines), (mines_flag = 0) : 0;
    if (cell.red_flag && (board[cell.x][cell.y] == EMPTY_POINT ||
                          board[cell.x][cell.y] == MINES_POINT)) {
      board[cell.x][cell.y] = '#';
    } else if (cell.red_flag && board[cell.x][cell.y] == RED_FLAG) {
      if (is_mine(mines, cell.x, cell.y)) {
        board[cell.x][cell.y] = MINES_POINT;
      } else {
        board[cell.x][cell.y] = EMPTY_POINT;
      }
    } else {
      if (is_mine(mines, cell.x, cell.y) == 0) {
        points += calculate_points(board, cell.x, cell.y);
        points >= BOARD_SIZE* BOARD_SIZE - AMOUNT_OF_MINES ? res = 1 : 0;
      } else {
        board[cell.x][cell.y] = '*';
        res = 0;
      }
    }
  }
  clear();
  print_field(board);
  return (bool)res;
}

void print_field(int8_t board[BOARD_SIZE][BOARD_SIZE]) {
  printw("   ");
  for (int i = 0; i < BOARD_SIZE; ++i) {
    printw("%2c", 'a' + i);
  }
  printw("\n");
  for (int i = 0; i < BOARD_SIZE; ++i) {
    printw("%2d ", i + 1);
    for (int j = 0; j < BOARD_SIZE; ++j) {
      printw("%2c", board[i][j]);
    }
    printw("\n");
  }
}

void filling_of_board(int8_t board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      board[i][j] = EMPTY_POINT;
    }
  }
}

unsigned calculate_points(int8_t board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
  unsigned res = 0;
  if (!(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE ||
        board[x][y] != EMPTY_POINT)) {
    int points = 0;
    res = 1;
    for (int i = x - 1; i <= x + 1; ++i) {
      for (int j = y - 1; j <= y + 1; ++j) {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
          if (board[i][j] == MINES_POINT || board[i][j] == RED_FLAG) {
            points++;
          }
        }
      }
    }
    board[x][y] = points + '0';
    if (points == 0) {
      res += calculate_points(board, x - 1, y - 1);
      res += calculate_points(board, x - 1, y);
      res += calculate_points(board, x - 1, y + 1);
      res += calculate_points(board, x, y - 1);
      res += calculate_points(board, x, y + 1);
      res += calculate_points(board, x + 1, y - 1);
      res += calculate_points(board, x + 1, y);
      res += calculate_points(board, x + 1, y + 1);
    }
  }
  return res;
}

bool update_cell(minesweeper_cell_t* cell) {
  bool res = 1;
  if (strlen(cell->input_str) == 2) {
    cell->x = cell->input_str[0] - '1';
    cell->y = cell->input_str[1] - 'a';
    cell->red_flag = 0;
    cell->input_str[3] == '\0' ? 0 : (res = 0);
  } else {
    cell->x = cell->input_str[0] - '1';
    if (cell->x < 0 || cell->x >= BOARD_SIZE) {
      res = 0;
    }
    cell->input_str[1] == '#' ? (cell->red_flag = 1) : (res = 0);
    cell->y = cell->input_str[2] - 'a';
    if (cell->y < 0 || cell->y >= BOARD_SIZE) {
      res = 0;
    }
    cell->input_str[3] == '\0' ? 0 : (res = 0);
  }
  free(cell->input_str);
  return res;
}

void start_text() {
  clear();
  printw("Welcome to minesweeper!\n");
  printw("You have %d mines.\n", AMOUNT_OF_MINES);
  printw("You need to open all cells without mines.\n");
  printw(
      "If you want open cell, enter coordinates(num letter) without spaces.\n");
  printw(
      "If you want designate a mine, enter coordinates(num letter) with "
      "hash(#).\n");
  printw("Press any key to start.\n");
  printw("Good luck!\n");
  getch();
  refresh();
}