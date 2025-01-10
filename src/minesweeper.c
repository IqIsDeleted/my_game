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
  bool filling_flag = 1;
  while (res == 2) {
    clear();
    print_field(board);
    refresh();
    printw("\nEnter coordinates(num letter): ");
    scanw("%d %c", &x, (char*)&y);
    y -= 'a';
    filling_flag ? filling_of_board(board, x - 1, y), filling_flag = 0 : 0;
    if (board[x - 1][y] == MINES_POINT) {
      board[x - 1][y] = '*';
      res = 0;
      clear();
      print_field(board);
    } else if (board[x - 1][y] == EMPTY_POINT) {
      calculate_points(board, x - 1, y);
    }
  }
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

void filling_of_board(int8_t board[BOARD_SIZE][BOARD_SIZE], int start_x,
                      int start_y) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      board[i][j] = EMPTY_POINT;
    }
  }
  srand(time(NULL));
  for (unsigned i = 0; i < 15; ++i) {
    int x, y;

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

void calculate_points(int8_t board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
  if (!(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE ||
        board[x][y] != EMPTY_POINT)) {
    int points = 0;
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
      calculate_points(board, x - 1, y - 1);
      calculate_points(board, x - 1, y);
      calculate_points(board, x - 1, y + 1);
      calculate_points(board, x, y - 1);
      calculate_points(board, x, y + 1);
      calculate_points(board, x + 1, y - 1);
      calculate_points(board, x + 1, y);
      calculate_points(board, x + 1, y + 1);
    }
  }
}