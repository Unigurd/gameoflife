#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "board.h"
#include "game.h"

struct game_of_life {
  int y, x;
  char *board0;
  char *board1;
};

int game_y(game game) { return game->y; }
int game_x(game game) { return game->x; }

game game_init(int y, int x) {
  game game = malloc(sizeof(game));
  if (game == NULL) return NULL;
  game->y = y;
  game->x = x;
  game->board0 = malloc(sizeof(char)*y*x);
  game->board1 = malloc(sizeof(char)*y*x);
  return game;
}

void game_free(game game) {
  free(game->board0);
  free(game->board1);
  free(game);
}

char game_idx(game game, int board, int y, int x) {
  return board_idx(board?game->board1:game->board0, game->x, y, x);
}

char game_mod_idx(game game, int y, int x) {
  return board_mod_idx(game->board0, game->y, game->x, y, x);
}

int game_surrounding_elms(game game, int y, int x) {
  char count = 0;
  count += game_mod_idx(game, y-1, x-1);
  count += game_mod_idx(game, y-1, x  );
  count += game_mod_idx(game, y-1, x+1);
  count += game_mod_idx(game, y,   x-1);
  count += game_mod_idx(game, y,   x+1);
  count += game_mod_idx(game, y+1, x-1);
  count += game_mod_idx(game, y+1, x  );
  count += game_mod_idx(game, y+1, x+1);
  return (int) count;
}

void game_switch_boards(game game) {
  char *tmp = game->board0;
  game->board0 = game->board1;
  game->board1 = tmp;
}

void game_set_field(game game, int y, int x, char val) {
  game->board0[y*game->x + x] = val;
}

void game_update_field (game game, int y, int x) {
 int count = game_surrounding_elms(game, y, x);
 char old  = game_idx(game,0,y,x);
 game->board1[y*game->x + x] =
   old
   ? (count == 2 || count == 3)
   : count == 3;
}

char *game_get_board(game game) {
  return game->board0;
}

void game_update_board(game game) {
  for (int i = 0; i < game->y; i++) {
    for (int j = 0; j < game->x; j++) {
      game_update_field(game, i, j);
    }
  }
  game_switch_boards(game);
}

// percent is the percent of fields that will
// be initialized to 1 (or 'x')
void game_random_board(game game, int percent) {
  for (int i = 0; i < game->y; i++) {
    for (int j = 0; j < game->x; j++) {
      char val = mod(rand(), 100) < percent;
      game_set_field(game, i, j, val);
    }
  }
}

void game_print(game game) {
  board_print(game->board0, game->y, game->x);
}
