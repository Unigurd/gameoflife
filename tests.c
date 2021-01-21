#include <stdio.h>
#include "game.h"
#include "board.h"
#include "utils.h"


void fill_board(game game, int x, int y, char *arr) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
    game_get_board(game)[i*y+j] = arr[i*y+j];
    }
  }
}

void report_error(int x, int y, char *start, char *expected, char *actual) {
  printf("ERROR:\nOn input:\n");
  board_print(start,x,y);
  printf("\nExpected:\n");
  board_print(expected,x,y);
  printf("\nGot:\n");
  board_print(actual,x,y);
  printf("\n");
}

int test_board(game game, int x, int y, char *step0, char *step1) {
  fill_board(game, x, y, step0);
  game_update_board(game);
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      if (game_get_board(game)[i*y+j] != step1[i*y+j]) {
        report_error(x, y, step0, step1, game_get_board(game));
        return -1;
      }
    }
  }
  return 0;
}


int main() {
  game game = game_init(3,3);
  int errors = 0;

  errors += test_board(game, 3, 3,
                       (char[])
                       {0,0,0,
                        0,0,0,
                        0,0,0},
                       (char[])
                       {0,0,0,
                        0,0,0,
                        0,0,0});

  errors += test_board(game, 3, 3,
                       (char[])
                       {1,0,0,
                        0,0,1,
                        1,0,0},
                       (char[])
                       {1,1,1,
                        1,1,1,
                        1,1,1});

  errors += test_board(game, 3, 3,
                       (char[])
                       {0,1,0,
                        0,1,1,
                        1,0,0},
                       (char[])
                       {0,1,0,
                        0,1,1,
                        1,0,0});

  errors += test_board(game, 3, 3,
                       (char[])
                       {1,0,1,
                        0,1,1,
                        1,0,0},
                       (char[])
                       {0,0,0,
                        0,0,0,
                        0,0,0});

  game_free(game);
  return errors;
}
