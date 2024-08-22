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
  GameInfo_t banner = create_banner();
  Figure_loc figure_ = create_figure();
  tmp_data Data = create_Data();
  state_t state = START;
  bool hold = 0;
  if (figure_.figure && Data.tmp_figure && banner.next && banner.field &&
      Data.only_field) {
    UserAction_t key = Pause;
    change_info(&banner);
    change_figure(&figure_);
    change_data((&Data));
    change_state(&state);
    while (state != EXIT_STATE) {
      key = 0;
      timeout(80 - banner.speed * 6);
      if (state != SPAWN) {
        key = getch();
        if (key) hold = 1;
      } else
        hold = 0;
      userInput(key, hold);
      print_banner();
    }
    write_high_score(banner.high_score);
  }
  free_memory(Data.tmp_figure, banner.next, figure_.figure, Data.only_field,
              banner.field);
}

void print_banner() {
  GameInfo_t banner = updateCurrentState();
  clear();
  state_t *state = change_state(NULL);
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
    print_banner_field(banner);
  }
}

void print_banner_field(GameInfo_t banner) {
  for (int i = 0; i < 20; i++) {
    for (int j = 3; j < 13; j++) {
      if (banner.field[i][j])
        printw("[]");
      else
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
    else if (i == 9)
      printw(" |      NEXT FIGURE:\n");
    else if (i == 11) {
      printw(" |      ");
      for (int m = 0, n = 0; n < 4; n++) {
        if (banner.next[m][n] == 1)
          printw("[]");
        else
          printw("  ");
      }
      printw("\n");
    } else if (i == 12) {
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