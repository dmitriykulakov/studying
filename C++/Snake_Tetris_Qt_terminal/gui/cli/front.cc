#include "front.h"

int main() {
  initscr();
  noecho();
  curs_set(0);
  srand(time(NULL));
  game_loop();
  endwin();
  return 0;
}

void game_loop() {
  int game = 0;
  GameInfo_t banner;
  state_t state = START;
  bool hold = 1;
  UserAction_t key = (UserAction_t)0;
  Figure_loc figure_;
  tmp_data Data;
  Model_s m_model;
  printw("PRESS:\n    1 - TO PLAY TETRIS\n    2 - TO PLAY SNAKE ");
  while (!game) {
    char tmp = getch();
    if (tmp == '1') game = 1;
    if (tmp == '2') game = 2;
  }
  if (game == 1) {
    banner = create_banner();
    figure_ = create_figure();
    Data = create_Data();
    if (figure_.figure && Data.tmp_figure && banner.next && banner.field &&
        Data.only_field) {
      key = Pause;
      change_info(&banner);
      change_figure(&figure_);
      change_data((&Data));
      change_state(&state);
    }
  }
  if (game == 2) {
    banner = m_model.updateCurrentState_s();
  }
  if (game) {
    while (state != EXIT_STATE) {
      timeout(80 - banner.speed * 6);
      if (state != SPAWN) {
        key = (UserAction_t)getch();
        if (key) hold = 1;
      } else {
        key = (UserAction_t)0;
        hold = 0;
      }

      if (game == 1) userInput(key, hold);
      if (game == 2) {
        m_model.userInput_s(key, hold);
        state = m_model.getStateModel();
      }
      key = (UserAction_t)0;
      print_banner(game, &m_model);
    }
  }
  if (game == 1) {
    write_high_score(banner.high_score);
    free_memory(Data.tmp_figure, banner.next, figure_.figure, Data.only_field,
                banner.field);
  }
  if (game == 2) {
    banner = m_model.updateCurrentState_s();
    m_model.writeHighScore(banner.high_score);
  }
}

void print_banner(int game, Model_s *m_model) {
  GameInfo_t banner;
  state_t *state;
  state_t state_tmp;
  if (game == 1) {
    banner = updateCurrentState();
    state = change_state(NULL);
  }
  if (game == 2) {
    banner = m_model->updateCurrentState_s();
    state_tmp = (m_model->getStateModel());
    state = &state_tmp;
  }
  clear();
  if (*state == WIN) {
    printw(
        "      YOU ARE THE WINNER\n\n    Press q to EXIT the game\n    Press "
        "ENTER to try AGAIN\n");
  } else if (*state == GAMEOVER) {
    printw(
        "           GAMEOVER\n\n    Press q to EXIT the game\n    Press ENTER "
        "to try AGAIN\n");
  } else {
    if (*state == START) {
      printw("Press ENTER to start the game\n");
    }
    print_banner_field(banner, game);
  }
}

void print_banner_field(GameInfo_t banner, int game) {
  for (int i = 0; i < 20; i++) {
    for (int j = 3; j < 13; j++) {
      if (banner.field[i][j]) {
        if (banner.field[i][j] == 1) printw("[]");
        if (banner.field[i][j] == 2) printw("()");
      } else
        printw("--");
    }
    if (i == 1)
      printw(" |      LEVEL: %d\n", banner.level);
    else if (i == 3)
      printw(" |      SPEED: %d\n", banner.speed);
    else if (i == 5)
      printw(" |      SCORE: %d\n", banner.score);
    else if (i == 7)
      printw(" |      HIGH SCORE: %d\n", banner.high_score);
    else if (i == 9 && game == 1)
      printw(" |      NEXT FIGURE:\n");
    else if (i == 11 && game == 1) {
      printw(" |      ");
      for (int m = 0, n = 0; n < 4; n++) {
        if (banner.next[m][n] == 1)
          printw("[]");
        else
          printw("  ");
      }
      printw("\n");
    } else if (i == 12 && game == 1) {
      printw(" |      ");
      for (int m = 1, n = 0; n < 4; n++) {
        if (banner.next[m][n] == 1)
          printw("[]");
        else
          printw("  ");
      }
      printw("\n");
    } else if (i == 18 && banner.pause)
      printw(" |      PAUSE\n");
    else
      printw(" | \n");
  }
}