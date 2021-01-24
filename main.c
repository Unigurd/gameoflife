#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <ncurses.h>
#include "utils.h"
#include "game.h"

int nano_sleep_repeat (int time) {
  struct timespec a, b;
  struct timespec *pa, *pb, *tmp;
  int retval;

  a.tv_sec  = time / 1000000000;
  a.tv_nsec = time % 1000000000;
  pa = &a;
  pb = &b;

  while (1) {
    retval = nanosleep((const struct timespec *)pa,pb);
    if (retval == 0)
      return retval;
    else if (retval == EINTR && pb != NULL) {
      tmp = pa;
      pa = pb;
      pb = tmp;
    } else {
      exit(-1);
    }
  }
}



int print_board(WINDOW *win, game game) {
  for (int i = 0; i < game_y(game); i++) {
    wmove(win, i+1, 1);
    for (int j = 0; j < game_x(game); j++) {
      if (game_idx(game,0,i,j))
        waddch(win, 'x');
      else waddch(win, ' ');
    }
  }
  return 0;
}

int main() {
  WINDOW *game_win;

  int board_x = 10;
  int board_y = 10;
  int outer_board_x = board_x + 2;
  int outer_board_y = board_y + 2;

  game game = game_init(board_y, board_x);
  game_random_board(game, 33);

  initscr();
  clear();
  cbreak();
  noecho();
  curs_set(0);
  //keypad();
  game_win = newwin(outer_board_y, outer_board_x, 10, 10);
  int box = box(game_win, 0, 0);
  refresh();

  while(1) {
    print_board(game_win, game);
    game_update_board(game);
    wrefresh(game_win);
    nano_sleep_repeat(500000000);
  }

  // This is never reached because program is closed with C-c
  game_free(game);
  delwin(game_win);
  endwin();
  return 0;
}
