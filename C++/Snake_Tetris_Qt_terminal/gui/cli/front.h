#ifndef FRONT_H
#define FRONT_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/snake/model_s.h"
#include "../../brick_game/tetris/model.h"

using namespace s21;

void game_loop();
void print_banner(int game, Model_s *m_model);
void print_banner_field(GameInfo_t banner, int game);

#endif