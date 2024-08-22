#ifndef STRINGPLUS_S21_TEST_ME_H_
#define STRINGPLUS_S21_TEST_ME_H_

#include <check.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../functions/s21_sprintf.h"
#include "../functions/s21_sscanf.h"
#include "../functions/s21_string.h"

Suite *s21_memchr_test(void);
Suite *s21_memcmp_test(void);
Suite *s21_memcpy_test(void);
Suite *s21_memset_test(void);
Suite *s21_sprintf_test_float(void);
Suite *s21_sprintf_test_int(void);
Suite *s21_sprintf_test_str(void);
Suite *s21_sprintf_test_other(void);
Suite *s21_strchr_test(void);
Suite *s21_strcmp_test(void);
Suite *s21_strerror_test(void);
Suite *s21_strlen_test(void);
Suite *s21_strncat_test(void);
Suite *s21_strncmp_test(void);
Suite *s21_strncpy_test(void);
Suite *s21_strpbrk_test(void);
Suite *s21_strrchr_test(void);
Suite *s21_strstr_test(void);
Suite *s21_strtok_test(void);
Suite *s21_atoi_test(void);
Suite *s21_insert_test(void);
Suite *s21_strtold_test(void);
Suite *s21_to_lower_test(void);
Suite *s21_to_upper_test(void);
Suite *s21_trim_test(void);
Suite *s21_sscanf_test_int(void);
Suite *s21_sscanf_test_float(void);
Suite *s21_sscanf_test_char(void);
Suite *s21_sscanf_test_pointer(void);
Suite *s21_sscanf_test_x(void);
Suite *s21_sscanf_test_string(void);
Suite *s21_sscanf_test_i(void);
Suite *s21_sscanf_test_o(void);
Suite *s21_sscanf_test_n(void);

#endif  // STRINGPLUS_S21_TEST_ME_H_
