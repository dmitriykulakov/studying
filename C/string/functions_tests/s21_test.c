#include "s21_test.h"

int main() {
  int failed = 0;
  Suite *s21_string_test[] = {s21_memchr_test(),
                              s21_memcmp_test(),
                              s21_memcpy_test(),
                              s21_memset_test(),
                              s21_sprintf_test_float(),
                              s21_sprintf_test_int(),
                              s21_sprintf_test_str(),
                              s21_sprintf_test_other(),
                              s21_strchr_test(),
                              s21_strcmp_test(),
                              s21_strerror_test(),
                              s21_strlen_test(),
                              s21_strncat_test(),
                              s21_strncmp_test(),
                              s21_strncpy_test(),
                              s21_strpbrk_test(),
                              s21_strrchr_test(),
                              s21_strstr_test(),
                              s21_strtok_test(),
                              s21_atoi_test(),
                              s21_insert_test(),
                              s21_strtold_test(),
                              s21_to_lower_test(),
                              s21_to_upper_test(),
                              s21_trim_test(),
                              s21_sscanf_test_int(),
                              s21_sscanf_test_float(),
                              s21_sscanf_test_char(),
                              s21_sscanf_test_pointer(),
                              s21_sscanf_test_x(),
                              s21_sscanf_test_string(),
                              s21_sscanf_test_i(),
                              s21_sscanf_test_o(),
                              s21_sscanf_test_n(),
                              NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
