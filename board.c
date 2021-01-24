#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "board.h"

// inline?
char board_idx(char *board, int max_x, int y, int x) {
  return board[y*max_x+x];
}


// inline?
char board_mod_idx(char *board, int max_y, int max_x, int y, int x) {
  int mody = mod(y, max_y);
  int modx = mod(x, max_x);
  return board_idx(board, max_x, mody, modx);
}


void board_print(char *arr, int y, int x) {
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      printf("%c", board_idx(arr,x,i,j) ? 'x' : '.');
    }
    printf("\n");
  }
}
