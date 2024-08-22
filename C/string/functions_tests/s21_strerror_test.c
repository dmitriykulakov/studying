#include "s21_test.h"

START_TEST(strerror_1) {
  int n1 = 0;
  ck_assert_str_eq(strerror(n1), s21_strerror(n1));
}
END_TEST

START_TEST(strerror_2) {
  int n2 = 107;
  ck_assert_str_eq(strerror(n2), s21_strerror(n2));
}
END_TEST

START_TEST(strerror_3) {
  int n3 = -1;
  ck_assert_str_eq(strerror(n3), s21_strerror(n3));
}
END_TEST

START_TEST(strerror_4) {
  for (int i = 1; i < 106; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

Suite *s21_strerror_test(void) {
  Suite *suite = suite_create("s21_test_strerror_test");
  TCase *tc = tcase_create("strerror_tc");

  suite_add_tcase(suite, tc);
  tcase_add_test(tc, strerror_1);
  tcase_add_test(tc, strerror_2);
  tcase_add_test(tc, strerror_3);
  tcase_add_test(tc, strerror_4);

  suite_add_tcase(suite, tc);
  return suite;
}