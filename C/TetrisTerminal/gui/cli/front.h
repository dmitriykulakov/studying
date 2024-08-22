#ifndef FRONT_H
#define FRONT_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/model.h"

void game_loop();
void print_banner();
void print_banner_field(GameInfo_t banner);

#endif