#include "s21_test.h"
#define BUFF_SIZE 1024

START_TEST(sscanf_string_1) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  const char str[] = "pupupupu free ysl";
  const char format[] = "%s%s";
  int res1 = sscanf(str, format, s1, s3);
  int res2 = s21_sscanf(str, format, s2, s4);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
}
END_TEST

START_TEST(sscanf_string_2) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  const char str[] = "pupupup'as/1\123u free ysl";
  const char format[] = "%s%s";
  int res1 = sscanf(str, format, s1, s3);
  int res2 = s21_sscanf(str, format, s2, s4);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
}
END_TEST

START_TEST(sscanf_string_3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  const char str[] = "pupupup'as/1 free ysl";
  const char format[] = "%s free%s";
  int res1 = sscanf(str, format, s1, s3);
  int res2 = s21_sscanf(str, format, s2, s4);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
}
END_TEST

START_TEST(sscanf_string_4) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  int a1 = 0, a2 = 0;

  const char str[] = "pupupup'as/1 free ysl 123";
  const char format[] = "%s free%s %d";
  int res1 = sscanf(str, format, s1, s3, &a1);
  int res2 = s21_sscanf(str, format, s2, s4, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);

  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
}
END_TEST

Suite *s21_sscanf_test_string(void) {
  Suite *suite = suite_create("s21_sscanf_test_string");
  TCase *tc = tcase_create("s21_sscanf_string_tc");

  tcase_add_test(tc, sscanf_string_1);
  tcase_add_test(tc, sscanf_string_2);
  tcase_add_test(tc, sscanf_string_3);
  tcase_add_test(tc, sscanf_string_4);

  suite_add_tcase(suite, tc);
  return suite;
}
