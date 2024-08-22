#include "s21_test.h"

START_TEST(sprintf_int_1) {
  char s1[128] = "", s2[128] = "";
  int num = 14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%d", num);
  res2 = sprintf(s2, "%d", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_2) {
  char s1[128] = "", s2[128] = "";
  int num = -14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%+d", num);
  res2 = sprintf(s2, "%+d", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_3) {
  char s1[128] = "", s2[128] = "";
  int num = -14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%014d", num);
  res2 = sprintf(s2, "%014d", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_4) {
  char s1[128] = "", s2[128] = "";
  int num = 14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%-d", num);
  res2 = sprintf(s2, "%-d", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_5) {
  char s1[128] = "", s2[128] = "";
  int num = 14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%i", num);
  res2 = sprintf(s2, "%i", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_6) {
  char s1[128] = "", s2[128] = "";
  int num = 14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%.13i", num);
  res2 = sprintf(s2, "%.13i", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_7) {
  char s1[128] = "", s2[128] = "";
  int num = 14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%07i", num);
  res2 = sprintf(s2, "%07i", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_8) {
  char s1[128] = "", s2[128] = "";
  int num = 14;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "% 7i", num);
  res2 = sprintf(s2, "% 7i", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_9) {
  char s1[128] = "", s2[128] = "";
  unsigned int num = 2376;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%o", num);
  res2 = sprintf(s2, "%o", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_10) {
  char s1[128] = "", s2[128] = "";
  unsigned int num = 2376;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%.*o", 7, num);
  res2 = sprintf(s2, "%.*o", 7, num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_11) {
  char s1[128] = "", s2[128] = "";
  unsigned int num = 123;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%u", num);
  res2 = sprintf(s2, "%u", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_12) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 0x3f3, num2 = 0x270F;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%x %x", num1, num2);
  res2 = sprintf(s2, "%x %x", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_13) {
  char s1[128] = "", s2[128] = "";
  int num1 = 0x3f3;
  long int num2 = 0x270F;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%hx %lx", num1, num2);
  res2 = sprintf(s2, "%hx %lx", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_14) {
  char s1[128] = "";
  unsigned int num1 = 0x3f3, num2 = 0x270F;

  s21_sprintf(s1, "% +x %x", num1, num2);
}
END_TEST

START_TEST(sprintf_int_15) {
  char s1[128] = "";
  unsigned int num1 = 0x3f3, num2 = 0x270F;

  s21_sprintf(s1, "%-0x %x", num1, num2);
}
END_TEST

START_TEST(sprintf_int_16) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 0x3f3, num2 = 0x270F;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%X %X", num1, num2);
  res2 = sprintf(s2, "%X %X", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_17) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 0x3f3, num2 = 0x270F;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%#X %X", num1, num2);
  res2 = sprintf(s2, "%#X %X", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_18) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 1234321;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%#o", num1);
  res2 = sprintf(s2, "%#o", num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_19) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 1234321, num2 = 6999;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%#x %#X", num1, num2);
  res2 = sprintf(s2, "%#x %#X", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_20) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 1234321;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%#x", num1);
  res2 = sprintf(s2, "%#x", num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_21) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 1234321, num2 = 6999;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%#X%#x", num1, num2);
  res2 = sprintf(s2, "%#X%#x", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_22) {
  char s1[128] = "", s2[128] = "";
  int num1 = 123;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%0*x", 12, num1);
  res2 = sprintf(s2, "%0*x", 12, num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_int_23) {
  char s1[128] = "", s2[128] = "";
  unsigned int num1 = 0, num2 = 0x270F;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%x %x", num1, num2);
  res2 = sprintf(s2, "%x %x", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *s21_sprintf_test_int(void) {
  Suite *suite = suite_create("s21_sprintf_int_test");
  TCase *tc = tcase_create("s21_sprintf_int_tc");

  tcase_add_test(tc, sprintf_int_1);
  tcase_add_test(tc, sprintf_int_2);
  tcase_add_test(tc, sprintf_int_3);
  tcase_add_test(tc, sprintf_int_4);
  tcase_add_test(tc, sprintf_int_5);
  tcase_add_test(tc, sprintf_int_6);
  tcase_add_test(tc, sprintf_int_7);
  tcase_add_test(tc, sprintf_int_8);
  tcase_add_test(tc, sprintf_int_9);
  tcase_add_test(tc, sprintf_int_10);
  tcase_add_test(tc, sprintf_int_11);
  tcase_add_test(tc, sprintf_int_12);
  tcase_add_test(tc, sprintf_int_13);
  tcase_add_test(tc, sprintf_int_14);
  tcase_add_test(tc, sprintf_int_15);
  tcase_add_test(tc, sprintf_int_16);
  tcase_add_test(tc, sprintf_int_17);
  tcase_add_test(tc, sprintf_int_18);
  tcase_add_test(tc, sprintf_int_19);
  tcase_add_test(tc, sprintf_int_20);
  tcase_add_test(tc, sprintf_int_21);
  tcase_add_test(tc, sprintf_int_22);
  tcase_add_test(tc, sprintf_int_23);

  suite_add_tcase(suite, tc);
  return suite;
}
