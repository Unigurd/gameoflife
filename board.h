#ifndef BOARD_H
#define BOARD_H
char board_idx(char *board, int max_y, int x, int y);
char board_mod_idx(char *board, int max_x, int max_y, int x, int y);
void board_print(char *arr, int x,int y);
#endif
