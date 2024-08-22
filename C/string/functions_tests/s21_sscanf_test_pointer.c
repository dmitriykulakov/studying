#include "s21_test.h"

START_TEST(sscanf_pointer_1) {
  char format[] = "%p";
  char str[] = "0xBBBB";
  int *p1 = 0, *p2 = 0;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_pointer_2) {
  char format[] = "%6p";
  char str[] = "0xBBBBB";
  int *p1 = 0, *p2 = 0;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_pointer_3) {
  char format[] = "%p";
  char str[] = "0x12345";
  int *p1 = 0, *p2 = 0;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_pointer_4) {
  char format[] = "%p";
  char str[] = "0x12345xd";
  int *p1 = 0, *p2 = 0;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_pointer_5) {
  char format[] = "%p";
  char str[] = "123123";
  int *p1 = 0, *p2 = 0;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

Suite *s21_sscanf_test_pointer(void) {
  Suite *suite = suite_create("s21_sscanf_test_pointer");
  TCase *tc = tcase_create("s21_sscanf_pointer_tc");

  tcase_add_test(tc, sscanf_pointer_1);
  tcase_add_test(tc, sscanf_pointer_2);
  tcase_add_test(tc, sscanf_pointer_3);
  tcase_add_test(tc, sscanf_pointer_4);
  tcase_add_test(tc, sscanf_pointer_5);

  suite_add_tcase(suite, tc);
  return suite;
}