#include "./model.h"

GameInfo_t create_banner() {
  GameInfo_t tmp;
  tmp.next = new_figure();
  tmp.field = new_field();
  tmp.score = 0;
  FILE *tmp_file;
  tmp_file = fopen("./high_score_tetris.txt", "r");
  char buffer[20];
  fgets(buffer, 20, tmp_file);
  fclose(tmp_file);
  tmp.high_score = strtol(buffer, NULL, 10);
  tmp.level = 1;
  tmp.speed = 1;
  tmp.pause = 0;
  return tmp;
}

Figure_loc create_figure() {
  Figure_loc tmp;
  tmp.figure = new_figure();
  tmp.X = 0;
  tmp.Y = 0;
  return tmp;
}

tmp_data create_Data() {
  tmp_data tmp;
  tmp.tmp_figure = new_figure();
  tmp.only_field = new_field();
  tmp.count = 0;
  return tmp;
}

int **new_field() {
  int status = 1;
  int n;
  int **field = (int **)calloc(25, sizeof(int *));
  if (field != NULL) {
    for (int i = 0; i < 25 && status; ++i) {
      field[i] = (int *)calloc(16, sizeof(int));
      if (field[i] == NULL) {
        status = 0;
        n = i;
      }
    }
    if (!status) {
      for (int i = 0; i < n; ++i) {
        free(field[i]);
      }
      field = NULL;
    }
  }
  return field;
}

int **new_figure() {
  int status = 1;
  int n;
  int **figure = (int **)calloc(4, sizeof(int *));
  if (figure != NULL) {
    for (int i = 0; i < 4 && status; ++i) {
      figure[i] = (int *)calloc(4, sizeof(int));
      if (figure[i] == NULL) {
        status = 0;
        n = i;
      }
    }
    if (!status) {
      for (int i = 0; i < n; ++i) {
        free(figure[i]);
      }
      figure = NULL;
    }
  }
  return figure;
}

void free_memory(int **figure_1, int **figure_2, int **figure_3, int **field_1,
                 int **field_2) {
  free_figure(figure_1);
  free_figure(figure_2);
  free_figure(figure_3);
  free_field(field_1);
  free_field(field_2);
}

void free_field(int **field) {
  if (field) {
    for (int i = 0; i < 25; ++i) {
      free(field[i]);
    }
    free(field);
  }
}

void free_figure(int **figure) {
  if (figure) {
    for (int i = 0; i < 4; ++i) {
      free(figure[i]);
    }
    free(figure);
  }
}

GameInfo_t updateCurrentState() {
  GameInfo_t *tmp = change_info(NULL);
  return *tmp;
}

GameInfo_t *change_info(GameInfo_t *banner) {
  static GameInfo_t *tmp;
  if (banner == NULL) return tmp;
  tmp = banner;
  return tmp;
}

Figure_loc *change_figure(Figure_loc *figure) {
  static Figure_loc *tmp;
  if (figure == NULL) return tmp;
  tmp = figure;
  return tmp;
}

tmp_data *change_data(tmp_data *Data) {
  static tmp_data *tmp;
  if (Data == NULL) return tmp;
  tmp = Data;
  return tmp;
}

state_t *change_state(state_t *state) {
  static state_t *tmp;
  if (state == NULL) return tmp;
  tmp = state;
  return tmp;
}

void userInput(UserAction_t action, bool hold) {
  state_t *state = change_state(NULL);
  GameInfo_t *banner = change_info(NULL);
  Figure_loc *figure_ = change_figure(NULL);
  tmp_data *Data = change_data(NULL);
  if (hold) apply_action(state, action);
  if (*state == START) clean_banner(banner);
  if (*state == SPAWN) {
    Data->count = 0;
    spawn_function(state, Data->only_field, figure_, banner);
  }
  if (*state == REACH) {
    while (*state != ATACHING)
      shift_function(banner->field, Data->only_field, figure_, state);
  }
  if (*state == MOVING)
    move_function(state, action, banner->field, figure_, Data->only_field);
  if (*state == ROTATION)
    rotation_function(state, banner->field, figure_, Data->only_field,
                      Data->tmp_figure);
  if (*state == PAUSE)
    banner->pause = 1;
  else
    banner->pause = 0;
  if (*state == SHIFTING) {
    (Data->count)++;
    if (Data->count == 10) {
      shift_function(banner->field, Data->only_field, figure_, state);
      Data->count = 0;
    }
  }
  if (*state == ATACHING) ataching_function(banner->field, state);
}

void apply_action(state_t *state, UserAction_t action) {
  if (*state != GAMEOVER && *state != WIN) {
    if (*state == START) {
      if (action == Start) {
        *state = SPAWN;
        create_next_figure();
      }
    } else if (action == Pause) {
      if (*state != PAUSE)
        *state = PAUSE;
      else
        *state = SHIFTING;
    } else if (action == Left || action == Right) {
      *state = MOVING;
    } else if (action == Down) {
      *state = REACH;
    } else if (action == Action) {
      *state = ROTATION;
    }
  } else {
    if (action == Start) {
      *state = START;
    }
  }
  if (action == Terminate) {
    *state = EXIT_STATE;
  }
}

void create_next_figure() {
  Figure_t figure = (Figure_t)(rand() % 7);
  GameInfo_t banner_tmp = updateCurrentState();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      banner_tmp.next[i][j] = 0;
    }
  }
  switch (figure) {
    case Cube:
      for (int i = 0; i < 2; i++)
        for (int j = 1; j < 3; j++) banner_tmp.next[i][j] = 1;
      break;
    case Stick:
      for (int i = 0, j = 0; j < 4; j++) banner_tmp.next[i][j] = 1;
      break;
    case T_letter:
      for (int i = 0, j = 0; j < 3; j++) banner_tmp.next[i][j] = 1;
      banner_tmp.next[1][1] = 1;
      break;
    case N_letter:
      banner_tmp.next[0][0] = 1;
      banner_tmp.next[0][1] = 1;
      banner_tmp.next[1][1] = 1;
      banner_tmp.next[1][2] = 1;
      break;
    case N_other_letter:
      banner_tmp.next[0][1] = 1;
      banner_tmp.next[0][2] = 1;
      banner_tmp.next[1][0] = 1;
      banner_tmp.next[1][1] = 1;
      break;
    case R_letter:
      for (int i = 1, j = 0; j < 3; j++) banner_tmp.next[i][j] = 1;
      banner_tmp.next[0][0] = 1;
      break;
    case R_other_letter:
      for (int i = 1, j = 0; j < 3; j++) banner_tmp.next[i][j] = 1;
      banner_tmp.next[0][2] = 1;
      break;
  }
}

void clean_banner(GameInfo_t *banner) {
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 16; j++) {
      banner->field[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      banner->next[i][j] = 0;
    }
  }
  banner->score = 0;
  banner->level = 1;
  banner->speed = 1;
  banner->pause = 0;
}

void spawn_function(state_t *state, int **only_field, Figure_loc *figure,
                    GameInfo_t *banner) {
  *state = SHIFTING;
  figure->X = 6;
  figure->Y = 0;
  copy_field(only_field, banner->field);
  for (int i = 0; i < 2; i++) {
    for (int j = 6; j < 10; j++) {
      banner->field[i][j] += banner->next[i][j - 6];
      if (banner->field[i][j] == 2) *state = GAMEOVER;
    }
  }
  if (*state != GAMEOVER) check_ataching(state, *figure, only_field);
  copy_figure(figure->figure, banner->next);
  create_next_figure();
}

void copy_field(int **field_1, int **field_2) {
  for (int i = 0; i < 20; i++) {
    for (int j = 3; j < 13; j++) {
      field_1[i][j] = field_2[i][j];
    }
  }
}

void copy_figure(int **figure_1, int **figure_2) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure_1[i][j] = figure_2[i][j];
    }
  }
}

void shift_function(int **field, int **only_field, Figure_loc *figure_,
                    state_t *state) {
  (figure_->Y)++;
  add_figure(*figure_, field, only_field);
  check_ataching(state, *figure_, only_field);
}

void move_function(state_t *state, UserAction_t key, int **field,
                   Figure_loc *figure_, int **only_field) {
  if (key == Right) {
    if (check_figure_position(figure_->X + 1, figure_->Y, only_field,
                              figure_->figure)) {
      (figure_->X)++;
      add_figure(*figure_, field, only_field);
    }
  }
  if (key == Left) {
    if (check_figure_position(figure_->X - 1, figure_->Y, only_field,
                              figure_->figure)) {
      (figure_->X)--;
      add_figure(*figure_, field, only_field);
    }
  }
  *state = SHIFTING;
  check_ataching(state, *figure_, only_field);
}

int check_figure_position(int x, int y, int **only_field, int **figure) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure[i][j]) {
        if (only_field[y + i][x + j] || x + j > 12 || x + j < 3 || y + i > 19)
          return 0;
      }
    }
  }
  return 1;
}

void rotation_function(state_t *state, int **field, Figure_loc *figure,
                       int **only_field, int **tmp_figure) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) tmp_figure[i][j] = 0;
  if (figure->figure[0][3]) {
    if (figure->figure[0][0])
      for (int i = 0, j = 3; i < 4; i++) tmp_figure[i][j] = 1;
    else {
      for (int i = 0, j = 0; j < 4; j++) tmp_figure[i][j] = 1;
    }
  } else {
    for (int i = 0, n = 2; i < 3; i++, n--)
      for (int j = 0; j < 3; j++) tmp_figure[j][n] = figure->figure[i][j];
  }
  if (!(figure->figure[0][1] && figure->figure[0][2] && figure->figure[1][1] &&
        figure->figure[1][2])) {
    if (check_figure_position(figure->X, figure->Y, only_field, tmp_figure)) {
      copy_figure(figure->figure, tmp_figure);
      add_figure(*figure, field, only_field);
    }
  }
  *state = SHIFTING;
  check_ataching(state, *figure, only_field);
}

void add_figure(Figure_loc figure, int **field, int **only_field) {
  copy_field(field, only_field);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure.figure[i][j]) field[i + figure.Y][j + figure.X] = 1;
    }
  }
}

void check_ataching(state_t *state, Figure_loc figure_, int **only_field) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure_.figure[i][j] && figure_.Y + i == 19) *state = ATACHING;
      if (figure_.figure[i][j] && only_field[figure_.Y + i + 1][figure_.X + j])
        *state = ATACHING;
    }
  }
}

void ataching_function(int **field, state_t *state) {
  int counter = 0;
  for (int i = 19; i > 0; i--) {
    int FLAG = 1;
    for (int j = 3; j < 13 && FLAG; j++)
      if (!(field[i][j])) FLAG = 0;
    if (FLAG) {
      counter++;
      for (int m = i; m > 0; m--) {
        for (int n = 3; n < 13; n++) {
          field[m][n] = field[m - 1][n];
        }
      }
      for (int n = 3; n < 13; n++) field[0][n] = 0;
      i++;
    }
  }
  *state = SPAWN;
  change_game_data(counter, state);
}

void change_game_data(int counter, state_t *state) {
  if (counter) {
    GameInfo_t *banner = change_info(NULL);
    if (counter == 1)
      banner->score += 100;
    else if (counter == 2)
      banner->score += 300;
    else if (counter == 3)
      banner->score += 700;
    else if (counter == 4)
      banner->score += 1500;
    banner->level = (banner->score / 600) + 1;
    banner->speed = banner->level;
    if (banner->score > banner->high_score) banner->high_score = banner->score;
    if (banner->level == 11) *state = WIN;
  }
}

void write_high_score(int high_score) {
  char str[10];
  sprintf(str, "%d", high_score);
  FILE *tmp_file;
  tmp_file = fopen("./high_score_tetris.txt", "w");
  fputs(str, tmp_file);
  fclose(tmp_file);
}
