#ifndef MODEL_H
#define MODEL_H

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../main.h"

typedef enum {
  Cube = 0,
  Stick,
  T_letter,
  N_letter,
  N_other_letter,
  R_letter,
  R_other_letter
} Figure_t;

typedef struct {
  int **figure;
  int X;
  int Y;
} Figure_loc;

typedef struct {
  int **tmp_figure;
  int **only_field;
  int count;
} tmp_data;

GameInfo_t updateCurrentState();
GameInfo_t create_banner();
Figure_loc create_figure();
tmp_data create_Data();
int **new_field();
int **new_figure();

void free_memory(int **figure_1, int **figure_2, int **figure_3, int **field_1,
                 int **field_2);
void free_field(int **field);
void free_figure(int **figure);

GameInfo_t *change_info(GameInfo_t *);
Figure_loc *change_figure(Figure_loc *figure);
tmp_data *change_data(tmp_data *Data);
state_t *change_state(state_t *state);

void userInput(UserAction_t action, bool hold);
void apply_action(state_t *state, UserAction_t action);
void create_next_figure();
void clean_banner(GameInfo_t *banner);
void spawn_function(state_t *state, int **only_field, Figure_loc *figure,
                    GameInfo_t *banner);
void copy_field(int **field_1, int **field_2);
void copy_figure(int **figure_1, int **figure_2);
void shift_function(int **field, int **only_field, Figure_loc *figure_,
                    state_t *state);
void move_function(state_t *state, UserAction_t key, int **field,
                   Figure_loc *figure_, int **only_field);
void rotation_function(state_t *state, int **field, Figure_loc *figure,
                       int **only_field, int **tmp_figure);
void add_figure(Figure_loc figure, int **field, int **only_field);
void check_ataching(state_t *state, Figure_loc figure_, int **only_field);
void ataching_function(int **field, state_t *state);
void change_game_data(int counter, state_t *state);
int check_figure_position(int x, int y, int **only_field, int **figure);
void write_high_score(int high_score);

#endif
