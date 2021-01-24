#ifndef GAME_H
#define GAME_H
struct game_of_life;
typedef struct game_of_life * game;

int game_y(game game);
int game_x(game game);
game  game_init(int y, int x);
void  game_free(game game);
char  game_idx(game game, int board, int y, int x);
char  game_mod_idx(game game, int y, int x);
int   game_surrounding_elms(game game, int y, int x);
void  game_switch_boards(game game);
void  game_set_field(game game, int y, int x, char val);
void  game_update_field (game game, int y, int x);
char *game_get_board(game game);
void  game_update_board(game game);
void  game_random_board(game game, int percent);
void  game_print(game game);
#endif
