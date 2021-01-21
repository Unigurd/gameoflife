#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "board.h"

// inline?
char board_idx(char *board, int max_y, int x, int y) {
  return board[x*max_y+y];
}


// inline?
char board_mod_idx(char *board, int max_x, int max_y, int x, int y) {
  int modx = mod(x, max_x);
  int mody = mod(y, max_y);
  return board_idx(board, max_y, modx, mody);
}


void board_print(char *arr, int x,int y) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      printf("%c", board_idx(arr,y,i,j) ? 'x' : '.');
    }
    printf("\n");
  }
}
