#include "minesweeper.h"

int main(int argc, char *argv[]) {
  if (game_process()) {
    printf("You win!\n");
  } else {
    printf("You lose!\n");
  }
  return 0;
}

void print_field(int8_t board[BOARD_SIZE][BOARD_SIZE]) {
  printf("   ");
  for (int i = 0; i < BOARD_SIZE; ++i) {
    printf("%2c", 'a' + i);
  }
  printf("\n");
  for (int i = 0; i < BOARD_SIZE; ++i) {
    printf("%2d ", i + 1);
    for (int j = 0; j < BOARD_SIZE; ++j) {
      printf("%2c", board[i][j]);
    }
    printf("\n");
  }
  printf("\nEnter coordinates(x y): ");
}

void filling_of_board(int8_t board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      board[i][j] = EMPTY_POINT;
    }
  }
  srand(time(NULL));
  for (unsigned i = 0; i < 15; ++i) {
    int x, y;
    do {
      x = rand() % BOARD_SIZE;
      y = rand() % BOARD_SIZE;
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

bool game_process() {
  int8_t board[BOARD_SIZE][BOARD_SIZE];
  uint8_t mines = 0;
  short res = 2;
  int x = 0, y = 0;
  filling_of_board(board);
  while (res == 2) {
    print_field(board);
    scanf("%d %c", &x, &y);
    y -= 'a';
    if (board[x - 1][y - 1] == MINES_POINT) {
      board[x - 1][y - 1] = '*';
      res = 0;
      print_field(board);
    } else if (board[x - 1][y - 1] == EMPTY_POINT) {
      calculate_points(board, x - 1, y - 1);
    }
  }
  return res;
}