#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "board.h"
#include "game.h"

struct game_of_life {
  int x, y;
  char *board0;
  char *board1;
};

game game_init(unsigned int x, unsigned int y) {
  game game = malloc(sizeof(game));
  if (game == NULL) return NULL;
  game->x = x;
  game->y = y;
  game->board0 = malloc(sizeof(char)*x*y);
  game->board1 = malloc(sizeof(char)*x*y);
  return game;
}


void game_free(game game) {
  free(game->board0);
  free(game->board1);
  free(game);
}



char game_idx(game game, int board, int x, int y) {
  return board_idx(board?game->board1:game->board0, game->y, x, y);
}


char game_mod_idx(game game, int x, int y) {
  return board_mod_idx(game->board0, game->x, game->y, x, y);
}

int game_surrounding_elms(game game, int x, int y) {
  char count = 0;
  count += game_mod_idx(game, x-1, y-1);
  count += game_mod_idx(game, x-1, y  );
  count += game_mod_idx(game, x-1, y+1);
  count += game_mod_idx(game, x,   y-1);
  count += game_mod_idx(game, x,   y+1);
  count += game_mod_idx(game, x+1, y-1);
  count += game_mod_idx(game, x+1, y  );
  count += game_mod_idx(game, x+1, y+1);
  return (int) count;
}

void game_switch_boards(game game) {
  char *tmp = game->board0;
  game->board0 = game->board1;
  game->board1 = tmp;
}

void game_set_field(game game, int x, int y, char val) {
  game->board0[x*game->y + y] = val;
}

void game_update_field (game game, int x, int y) {
 int count = game_surrounding_elms(game, x, y);
 char old  = game_idx(game,0,x,y);
 game->board1[x*game->y + y] =
   old
   ? (count == 2 || count == 3)
   : count == 3;
}

char *game_get_board(game game) {
  return game->board0;
}

void game_update_board(game game) {
  for (int i = 0; i < game->x; i++) {
    for (int j = 0; j < game->y; j++) {
      game_update_field(game, i, j);
    }
  }
  game_switch_boards(game);
}

// percent is the percent of fields that will
// be initialized to 1 (or 'x')
void game_random_board(game game, int percent) {
  for (int i = 0; i < game->x; i++) {
    for (int j = 0; j < game->y; j++) {
      char val = mod(rand(), 100) < percent;
      game_set_field(game, i, j, val);
    }
  }
}

void game_print(game game) {
  board_print(game->board0, game->x, game->y);
}
