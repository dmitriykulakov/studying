#include "tetris_test.h"

START_TEST(tetris_1) {
  GameInfo_t banner = create_banner();
  Figure_loc figure_ = create_figure();
  tmp_data Data = create_Data();
  state_t state = START;
    bool hold = 1;
    change_info(&banner);
    change_figure(&figure_);
    change_data((&Data));
    change_state(&state);
    userInput(Start, hold);
    ck_assert_int_eq(state, SHIFTING);
    userInput(Down, hold);
    ck_assert_int_eq(state, SPAWN);
    userInput(0, 0);
    userInput(Pause, hold);
    ck_assert_int_eq(state, PAUSE);
    userInput(Pause, hold);
    ck_assert_int_eq(state, SHIFTING);
    ck_assert_int_eq(figure_.X, 6);
    userInput(Right, hold);
    ck_assert_int_eq(figure_.X, 7);
    userInput(Left, hold);
    ck_assert_int_eq(figure_.X, 6);
    ck_assert_int_eq(figure_.Y, 0);
    for (int i = 0; i < 10; i++) {
    userInput(0, 0);
    }
    ck_assert_int_eq(figure_.Y, 1);
    for (int i = 0; i < 2000; i++) {
    userInput(0, 0);
    }
    ck_assert_int_eq(state, GAMEOVER);
    userInput(Start, 1);
    ck_assert_int_eq(state, START);
    userInput(Start, 1);
    ck_assert_int_eq(state, SHIFTING);
    userInput(Action, 1);
    ck_assert_int_eq(figure_.X, 6);
    for (int i = 0; i < 10; i++) {
    userInput(Right, 1);
    }
    ck_assert_int_eq(figure_.X, 10);
     for (int i = 0; i < 2000; i++) {
    userInput(0, 0);
    }
    ck_assert_int_eq(state, GAMEOVER);
    userInput(Terminate, 1);
    ck_assert_int_eq(state, EXIT_STATE);
    free_memory(Data.tmp_figure, banner.next, figure_.figure, Data.only_field,
              banner.field);
}

START_TEST(tetris_2) {
    GameInfo_t banner = create_banner();
    state_t state = SHIFTING;
    change_info(&banner);
    ck_assert_int_eq(banner.score, 0);
    change_game_data(1, &state);
    ck_assert_int_eq(banner.score, 100);
    change_game_data(2, &state);
    ck_assert_int_eq(banner.score, 400);
    change_game_data(3, &state);
    ck_assert_int_eq(banner.score, 1100);
    change_game_data(4, &state);
    ck_assert_int_eq(banner.score, 2600);
    free_field(banner.field);
    free_figure(banner.next);
}

START_TEST(tetris_3) {
    write_high_score(1000);
}

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_TETRIS=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, tetris_1);
  tcase_add_test(tc, tetris_2);
  tcase_add_test(tc, tetris_3);

  suite_add_tcase(suite, tc);
  return suite;
}

void case_test_runner(Suite *suite, int *fail_count) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  *fail_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main(void) {
  int fail_count = 0;
  case_test_runner(suite(), &fail_count);

  return fail_count;
}