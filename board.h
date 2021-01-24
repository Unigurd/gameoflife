#ifndef BOARD_H
#define BOARD_H
char board_idx(char *board, int max_x, int y, int x);
char board_mod_idx(char *board, int max_y, int max_x, int y, int x);
void board_print(char *arr, int y,int x);
#endif
