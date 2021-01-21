#include <stdio.h>
#include "utils.h"
#include "game.h"

int main() {
  printf("%d\n", mod(-5,3));
  game game = game_init(10, 10);
  game_random_board(game, 33);
  game_print(game);
  printf("\n");
  game_update_board(game);
  game_print(game);
  game_free(game);
  return 0;
}
