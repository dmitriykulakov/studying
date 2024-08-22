#include "s21_test.h"

START_TEST(sscanf_x_1) {
  char str[] = "777";
  unsigned int x1 = 0, x2 = 0;

  int res1 = s21_sscanf(str, "%x", &x1);
  int res2 = sscanf(str, "%x", &x2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(sscanf_x_2) {
  char str[] = "123 52";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%x %x", &x1, &x3);
  int res2 = sscanf(str, "%x %x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_3) {
  char str[] = "12a3 5b2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%x %x", &x1, &x3);
  int res2 = sscanf(str, "%x %x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_4) {
  char str[] = "12i3 5j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%x %x", &x1, &x3);
  int res2 = sscanf(str, "%x %x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_5) {
  char str[] = "+12i3 +5j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%x %x", &x1, &x3);
  int res2 = sscanf(str, "%x %x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_6) {
  char str[] = "+012i3 +05j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%x %x", &x1, &x3);
  int res2 = sscanf(str, "%x %x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_7) {
  char str[] = "+012i3 +05j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1x %1x", &x1, &x3);
  int res2 = sscanf(str, "%1x %1x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_8) {
  char str[] = "+012i3 bc";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1x %1x", &x1, &x3);
  int res2 = sscanf(str, "%1x %1x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_x_9) {
  char str[] = "2i3 bCc";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1x %2x", &x1, &x3);
  int res2 = sscanf(str, "%1x %2x", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_1) {
  char str[] = "777";
  unsigned long int x1 = 0, x2 = 0;

  int res1 = s21_sscanf(str, "%lx", &x1);
  int res2 = sscanf(str, "%lx", &x2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(sscanf_lx_2) {
  char str[] = "123 52";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%lx %lx", &x1, &x3);
  int res2 = sscanf(str, "%lx %lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_3) {
  char str[] = "12a3 5b2";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%lx %lx", &x1, &x3);
  int res2 = sscanf(str, "%lx %lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_4) {
  char str[] = "12i3 5j2";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%lx %lx", &x1, &x3);
  int res2 = sscanf(str, "%lx %lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_5) {
  char str[] = "+12i3 +5j2";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%lx %lx", &x1, &x3);
  int res2 = sscanf(str, "%lx %lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_6) {
  char str[] = "+012i3 +05j2";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%lx %lx", &x1, &x3);
  int res2 = sscanf(str, "%lx %lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_7) {
  char str[] = "+012i3 +05j2";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1lx %1lx", &x1, &x3);
  int res2 = sscanf(str, "%1lx %1lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_8) {
  char str[] = "+012i3 bc";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1lx %1lx", &x1, &x3);
  int res2 = sscanf(str, "%1lx %1lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_lx_9) {
  char str[] = "2i3 bCc";
  unsigned long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1lx %2lx", &x1, &x3);
  int res2 = sscanf(str, "%1lx %2lx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_1) {
  char str[] = "777";
  unsigned long long int x1 = 0, x2 = 0;

  int res1 = s21_sscanf(str, "%llx", &x1);
  int res2 = sscanf(str, "%llx", &x2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(sscanf_llx_2) {
  char str[] = "123 52";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%llx %llx", &x1, &x3);
  int res2 = sscanf(str, "%llx %llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_3) {
  char str[] = "12a3 5b2";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%llx %llx", &x1, &x3);
  int res2 = sscanf(str, "%llx %llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_4) {
  char str[] = "12i3 5j2";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%llx %llx", &x1, &x3);
  int res2 = sscanf(str, "%llx %llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_5) {
  char str[] = "+12i3 +5j2";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%llx %llx", &x1, &x3);
  int res2 = sscanf(str, "%llx %llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_6) {
  char str[] = "+012i3 +05j2";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%llx %llx", &x1, &x3);
  int res2 = sscanf(str, "%llx %llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_7) {
  char str[] = "+012i3 +05j2";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1llx %1llx", &x1, &x3);
  int res2 = sscanf(str, "%1llx %1llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_llx_8) {
  char str[] = "2i3 bCc";
  unsigned long long int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1llx %2llx", &x1, &x3);
  int res2 = sscanf(str, "%1llx %2llx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_1) {
  char str[] = "777";
  unsigned short x1 = 0, x2 = 0;

  int res1 = s21_sscanf(str, "%hx", &x1);
  int res2 = sscanf(str, "%hx", &x2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(sscanf_hx_2) {
  char str[] = "123 52";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%hx %hx", &x1, &x3);
  int res2 = sscanf(str, "%hx %hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_3) {
  char str[] = "12a3 5b2";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%hx %hx", &x1, &x3);
  int res2 = sscanf(str, "%hx %hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_4) {
  char str[] = "12i3 5j2";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%hx %hx", &x1, &x3);
  int res2 = sscanf(str, "%hx %hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_5) {
  char str[] = "+12i3 +5j2";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%hx %hx", &x1, &x3);
  int res2 = sscanf(str, "%hx %hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_6) {
  char str[] = "+012i3 +05j2";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%hx %hx", &x1, &x3);
  int res2 = sscanf(str, "%hx %hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_7) {
  char str[] = "+012i3 +05j2";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1hx %1hx", &x1, &x3);
  int res2 = sscanf(str, "%1hx %1hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_8) {
  char str[] = "+012i3 bc";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1hx %1hx", &x1, &x3);
  int res2 = sscanf(str, "%1hx %1hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_hx_9) {
  char str[] = "2i3 bCc";
  unsigned short x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, "%1hx %2hx", &x1, &x3);
  int res2 = sscanf(str, "%1hx %2hx", &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

Suite *s21_sscanf_test_x(void) {
  Suite *suite = suite_create("s21_sscanf_test_x");
  TCase *tc = tcase_create("s21_sscanf_x_tc");

  tcase_add_test(tc, sscanf_x_1);
  tcase_add_test(tc, sscanf_x_2);
  tcase_add_test(tc, sscanf_x_3);
  tcase_add_test(tc, sscanf_x_4);
  tcase_add_test(tc, sscanf_x_5);
  tcase_add_test(tc, sscanf_x_6);
  tcase_add_test(tc, sscanf_x_7);
  tcase_add_test(tc, sscanf_x_8);
  tcase_add_test(tc, sscanf_x_9);

  tcase_add_test(tc, sscanf_lx_1);
  tcase_add_test(tc, sscanf_lx_2);
  tcase_add_test(tc, sscanf_lx_3);
  tcase_add_test(tc, sscanf_lx_4);
  tcase_add_test(tc, sscanf_lx_5);
  tcase_add_test(tc, sscanf_lx_6);
  tcase_add_test(tc, sscanf_lx_7);
  tcase_add_test(tc, sscanf_lx_8);
  tcase_add_test(tc, sscanf_lx_9);

  tcase_add_test(tc, sscanf_llx_1);
  tcase_add_test(tc, sscanf_llx_2);
  tcase_add_test(tc, sscanf_llx_3);
  tcase_add_test(tc, sscanf_llx_4);
  tcase_add_test(tc, sscanf_llx_5);
  tcase_add_test(tc, sscanf_llx_6);
  tcase_add_test(tc, sscanf_llx_7);
  tcase_add_test(tc, sscanf_llx_8);

  tcase_add_test(tc, sscanf_hx_1);
  tcase_add_test(tc, sscanf_hx_2);
  tcase_add_test(tc, sscanf_hx_3);
  tcase_add_test(tc, sscanf_hx_4);
  tcase_add_test(tc, sscanf_hx_5);
  tcase_add_test(tc, sscanf_hx_6);
  tcase_add_test(tc, sscanf_hx_7);
  tcase_add_test(tc, sscanf_hx_8);
  tcase_add_test(tc, sscanf_hx_9);

  suite_add_tcase(suite, tc);
  return suite;
}