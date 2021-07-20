#ifndef __GAME_GAME_H__
#define __GAME_GAME_H__

#include <stdbool.h>

bool game_is_running(void);

void init_game(void);
void update_game(void);
void cleanup_game(void);

#endif