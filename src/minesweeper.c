#include "minesweeper.h"

int main() {
  initscr();
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

bool game_process() {
  int8_t board[BOARD_SIZE][BOARD_SIZE];
  short res = 2;
  int x = 0, y = 0;
  bool mines_flag = 1;
  filling_of_board(board);
  unsigned points = 0;
  while (res == 2) {
    clear();
    print_field(board);
    refresh();
    printw("\nPoints: %u\n", points);
    printw("\nEnter coordinates(num letter): ");
    scanw("%d %c", &x, (char*)&y);
    y -= 'a';
    mines_flag ? lay_mines(board, x - 1, y), mines_flag = 0 : 0;
    if (board[x - 1][y] == EMPTY_POINT) {
      points += calculate_points(board, x - 1, y);
      points >= BOARD_SIZE* BOARD_SIZE - AMOUNT_OF_MINES ? res = 1 : 0;
    } else if (board[x - 1][y] == MINES_POINT) {
      board[x - 1][y] = '*';
      res = 0;
    }
  }
  clear();
  print_field(board);
  return res;
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

void lay_mines(int8_t board[BOARD_SIZE][BOARD_SIZE], int start_x, int start_y) {
  srand(time(NULL));
  for (unsigned i = 0; i < AMOUNT_OF_MINES; ++i) {
    int x = 1, y = 1;
    do {
      int tmp = rand() % BOARD_SIZE;
      if (tmp < start_x - 1 || tmp > start_x + 1) {
        x = tmp;
      }
      tmp = rand() % BOARD_SIZE;
      if (tmp < start_y - 1 || tmp > start_y + 1) {
        y = tmp;
      }
    } while (board[x][y] != EMPTY_POINT);
    board[x][y] = MINES_POINT;
  }
}

unsigned calculate_points(int8_t board[BOARD_SIZE][BOARD_SIZE], int x,
                          int y) {  // Я еб** рез
  unsigned res = 0;
  if (!(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE ||
        board[x][y] != EMPTY_POINT)) {
    int points = 0;
    res = 1;
    for (int i = x - 1; i <= x + 1; ++i) {
      for (int j = y - 1; j <= y + 1; ++j) {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
          if (board[i][j] == MINES_POINT) {
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