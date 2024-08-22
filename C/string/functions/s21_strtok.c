#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  int FLAG = 0, FLAG_tok = 0;
  static char *adress;
  int n = s21_strlen(delim);
  if (str == S21_NULL)
    str = adress;
  else
    adress = S21_NULL;
  int i = 0;
  int m = s21_strlen(str);
  for (i = 0; i < m && FLAG == 0; i++) {
    for (int j = 0; i < m && j < n && FLAG == 0; j++) {
      if (str[i] == delim[j] && FLAG_tok == 0) {
        str++;
        m = s21_strlen(str);
        j = -1;
      } else if ((j + 1) == n && i < m)
        FLAG_tok = 1;
      if (j >= 0 && str[i] == delim[j] && FLAG_tok == 1) {
        str[i] = '\0';
        FLAG = 1;
      }
    }
  }
  if (*str != '\0')
    adress = &str[i];
  else
    adress = str;
  if (*str == '\0') str = S21_NULL;
  return str;
}
