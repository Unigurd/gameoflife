#ifndef GAME_H
#define GAME_H
struct game_of_life;
typedef struct game_of_life * game;

game  game_init(unsigned int x, unsigned int y);
void  game_free(game game);
char  game_idx(game game, int board, int x, int y);
char  game_mod_idx(game game, int x, int y);
int   game_surrounding_elms(game game, int x, int y);
void  game_switch_boards(game game);
void  game_set_field(game game, int x, int y, char val);
void  game_update_field (game game, int x, int y);
char *game_get_board(game game);
void  game_update_board(game game);
void  game_random_board(game game, int percent);
void  game_print(game game);
#endif
