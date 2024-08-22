#include "s21_test.h"

START_TEST(sscanf_no_int_1) {
  char form[] = "%d";
  char str[] = "";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_no_int_2) {
  char form[] = "%d";
  char str[] = "                   ";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_no_int_3) {
  char form[] = "%d";
  char str[] = "fgra1";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_no_int_4) {
  char form[] = "%d";
  char str[] = "\t";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_no_int_5) {
  char form[] = "%d";
  char str[] = "\t\t\t\n";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_no_int_6) {
  char form[] = "%d";
  char str[] = "\n";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_int_1) {
  char form[] = "%d";
  char str[] = "777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_2) {
  char form[] = "%d";
  char str[] = "+777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_3) {
  char form[] = "%d";
  char str[] = "-777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_4) {
  char form[] = "%2d";
  char str[] = "777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_5) {
  char form[] = "%10d";
  char str[] = "777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_6) {
  char form[] = "%2d";
  char str[] = "+777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_7) {
  char form[] = "%2d";
  char str[] = "-777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_8) {
  char form[] = "%10d";
  char str[] = "-777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_9) {
  char form[] = "%10d";
  char str[] = "+777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_10) {
  char form[] = "%*2d";
  char str[] = "+777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_11) {
  char form[] = "%*2d";
  char str[] = "-777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_12) {
  char form[] = "%*10d";
  char str[] = "+777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_13) {
  char form[] = "%*10d";
  char str[] = "-777";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_14) {
  char form[] = "%d";
  char str[] = "2147483647";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_15) {
  char form[] = "%d";
  char str[] = "+2147483647";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_16) {
  char form[] = "%d";
  char str[] = "-2147483647";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_int_17) {
  char form[] = "%d";
  char str[] = "214748364751";
  int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_1) {
  char form[] = "%d%d";
  char str[] = "777 123";
  int p1, p2, p3, p4;

  int res1 = sscanf(str, form, &p1, &p3);
  int res2 = s21_sscanf(str, form, &p2, &p4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
  ck_assert_int_eq(p3, p4);
}
END_TEST

START_TEST(sscanf_longint_2) {
  char form[] = "%ld";
  char str[] = "364751";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_3) {
  char form[] = "%ld";
  char str[] = "-777";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_4) {
  char form[] = "%ld";
  char str[] = "+777";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_5) {
  char form[] = "%*2ld";
  char str[] = "+777";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_6) {
  char form[] = "%*2ld";
  char str[] = "-777";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_7) {
  char form[] = "%*10ld";
  char str[] = "+777";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_longint_8) {
  char form[] = "%*10ld";
  char str[] = "-777";
  long int p1 = 0, p2 = 0;

  int res1 = sscanf(str, form, &p1);
  int res2 = s21_sscanf(str, form, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
}
END_TEST

Suite *s21_sscanf_test_int(void) {
  Suite *suite = suite_create("s21_sscanf_test_int");
  TCase *tc = tcase_create("s21_sscanf_int_tc");

  tcase_add_test(tc, sscanf_no_int_1);
  tcase_add_test(tc, sscanf_no_int_2);
  tcase_add_test(tc, sscanf_no_int_3);
  tcase_add_test(tc, sscanf_no_int_4);
  tcase_add_test(tc, sscanf_no_int_5);
  tcase_add_test(tc, sscanf_no_int_6);

  tcase_add_test(tc, sscanf_int_1);
  tcase_add_test(tc, sscanf_int_2);
  tcase_add_test(tc, sscanf_int_3);
  tcase_add_test(tc, sscanf_int_4);
  tcase_add_test(tc, sscanf_int_5);
  tcase_add_test(tc, sscanf_int_6);
  tcase_add_test(tc, sscanf_int_7);
  tcase_add_test(tc, sscanf_int_8);
  tcase_add_test(tc, sscanf_int_9);
  tcase_add_test(tc, sscanf_int_10);
  tcase_add_test(tc, sscanf_int_11);
  tcase_add_test(tc, sscanf_int_12);
  tcase_add_test(tc, sscanf_int_13);
  tcase_add_test(tc, sscanf_int_14);
  tcase_add_test(tc, sscanf_int_15);
  tcase_add_test(tc, sscanf_int_16);
  tcase_add_test(tc, sscanf_int_17);

  tcase_add_test(tc, sscanf_longint_1);
  tcase_add_test(tc, sscanf_longint_2);
  tcase_add_test(tc, sscanf_longint_3);
  tcase_add_test(tc, sscanf_longint_4);
  tcase_add_test(tc, sscanf_longint_5);
  tcase_add_test(tc, sscanf_longint_6);
  tcase_add_test(tc, sscanf_longint_7);
  tcase_add_test(tc, sscanf_longint_8);

  suite_add_tcase(suite, tc);
  return suite;
}