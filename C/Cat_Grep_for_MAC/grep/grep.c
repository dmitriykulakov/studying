#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "s21_grep.h"

void building(char *flags, char *argv[], int argc, int *n_flags_FLAG) {
  int n = 0, FLAG, ef_FLAG;
  for (int i = 1; i < argc && *n_flags_FLAG == 0; i++) {
    int j = 1;
    FLAG = 0;
    ef_FLAG = 0;
    if (argv[i][0] != '-') FLAG = 1;
    while (argv[i][j] != '\0' && *n_flags_FLAG == 0 && FLAG == 0) {
      if (argv[i][j] == 'e' || argv[i][j] == 'f' || argv[i][j] == 'i' ||
          argv[i][j] == 'v' || argv[i][j] == 'c' || argv[i][j] == 'l' ||
          argv[i][j] == 'n' || argv[i][j] == 's' || argv[i][j] == 'h' ||
          argv[i][j] == 'o') {
        if (argv[i][j] == 'e' || argv[i][j] == 'f') FLAG = 1;
        if ((argv[i][j] == 'e' || argv[i][j] == 'f') &&
            argv[i][j + 1] == '\0') {
          flags[n] = argv[i][j];
          n++;
          ef_FLAG = 1;
          i++;
        }
        if (ef_FLAG != 1) {
          flags[n] = argv[i][j];
          n++;
          j++;
        } else
          j++;
      } else {
        *n_flags_FLAG = 1;
        fprintf(stderr,
                "grep: invalid option -- %c\nusage: grep "
                "[-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
                "[-C[num]]\n[-e pattern] [-f file] [--binary-files=value] "
                "[--color=when]\n[--context[=num]] [--directories=action] "
                "[--label] [--line-buffered]\n[--null] [pattern] [file ...]\n",
                argv[i][j]);
      }
    }
  }
  flags[n] = '\0';
}

int word_counting(char *flags, char *argv[], int argc, char *f_words) {
  int n = strlen(flags), word_count = 0, file_FLAG = 0;
  for (int i = 0; i < n; i++) {
    if (flags[i] == 'e') word_count++;
  }
  if (strchr(flags, 'f'))
    file_FLAG = f_word_counting(argv, argc, &word_count, f_words);
  if (word_count < 1) word_count = 1;
  if (file_FLAG == 1) word_count = 0;
  return word_count;
}

int f_word_counting(char *argv[], int argc, int *word_count, char *f_words) {
  int file_FLAG = 0, n = 0;
  char buffer[256], file_name[256];
  for (int k = 1; k < argc; k++) {
    int j = 0, f_FLAG = 0, error = 0;
    if (argv[k][j] == '-') {
      j++;
      f_FLAG = 1;
    }
    if (strchr(argv[k], 'f')) {
      while (argv[k][j] != 'f' && f_FLAG == 1 && error == 0) {
        if (argv[k][j] == 'e') error = 1;
        j++;
      }
    }
    if (argv[k][j] == 'f' && f_FLAG == 1 && error == 0) {
      j++;
      if (argv[k][j] != '\0') {
        for (; argv[k][j] != '\0'; j++, n++) {
          file_name[n] = argv[k][j];
        }
        file_name[n] = '\0';
      }
      if (argv[k][j] == '\0' && n == 0) {
        k++;
        strcpy(file_name, argv[k]);
      }
      FILE *pattern_file;
      if ((pattern_file = fopen(file_name, "r")) != NULL) {
        for (; fgets(buffer, 256, pattern_file) != NULL; (*word_count)++) {
          strcat(f_words, buffer);
        }
      } else {
        fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
        file_FLAG = 1;
      }
      int len = strlen(f_words);
      if (f_words[len - 1] != '\n') {
        f_words[len] = '\n';
        f_words[len + 1] = '\0';
      }
      fclose(pattern_file);
    }
  }
  return file_FLAG;
}

int e_flag(char *argv[], int argc, char word[][256]) {
  int m = 0;
  for (int k = 1; k < argc; k++) {
    int j = 0, n = 0, e_FLAG = 0, error = 0;
    if (argv[k][j] == '-') {
      j++;
      e_FLAG = 1;
    }
    if (strchr(argv[k], 'e')) {
      while (argv[k][j] != 'e' && e_FLAG == 1 && error == 0) {
        if (argv[k][j] == 'f') error = 1;
        j++;
      }
    }
    if (argv[k][j] == 'e' && e_FLAG == 1 && error == 0) {
      j++;
      if (argv[k][j] != '\0') {
        while (argv[k][j] != '\0') {
          word[m][n] = argv[k][j];
          j++;
          n++;
        }
        word[m][n] = '\0';
        m++;
      }
      if (argv[k][j] == '\0' && n == 0) {
        k++;
        strcpy(word[m], argv[k]);
        m++;
      }
    } else
      j++;
  }
  return m;
}

void f_flag(char word[][256], int m, char *f_words) {
  int n = strlen(f_words);
  int j;
  for (int i = 0; i < n; i++, m++) {
    for (j = 0; f_words[i] != '\n'; i++, j++) {
      word[m][j] = f_words[i];
    }
    word[m][j] = '\0';
  }
}

int word_building(char *argv[], int argc, char word[][256]) {
  int FLAG = 0, i;
  for (i = 1; i < argc && FLAG == 0; i++) {
    if (argv[i][0] != '-') {
      strcpy(word[0], argv[i]);
      FLAG = 1;
    }
  }
  return i;
}

void work_with_the_file(char *flags, char word[][256], char *argv[], int argc,
                        int i, int word_count) {
  char buffer[4096];
  int file_counting = 0, k, FILE_FLAG = 0;
  k = i;
  for (; k < argc; k++) {
    if (argv[k][0] != '-') file_counting++;
    k = word_ignoring(argv[k], k);
  }
  for (; i < argc; i++) {
    int n = 1, c_counting = 0;
    while (argv[i][0] == '-' &&
           (strchr(argv[i], 'e') || strchr(argv[i], 'f'))) {
      i = word_ignoring(argv[i], i);
      i++;
      if (!(i < argc)) break;
    }
    FILE *fp;
    if (i < argc) {
      if ((fp = fopen(argv[i], "r")) != NULL) FILE_FLAG = 1;
    }
    if (FILE_FLAG == 1) {
      while ((fgets(buffer, 4096, fp)) != NULL) {
        int m = strlen(buffer);
        if (buffer[m - 1] != '\n') {
          buffer[m] = '\n';
          buffer[m + 1] = '\0';
        }
        parsing(buffer, flags, word, argv[i], n, &c_counting, file_counting,
                word_count);
        n++;
      }
      if (strchr(flags, 'c')) {
        if (file_counting > 1 && !strchr(flags, 'h')) printf("%s:", argv[i]);
        if (strchr(flags, 'l') && c_counting > 0) c_counting = 1;
        printf("%d\n", c_counting);
      }
      if (strchr(flags, 'l') && c_counting > 0) printf("%s\n", argv[i]);
      fclose(fp);
    } else {
      if (!strchr(flags, 's') && argv[i][0] != '-' && i < argc)
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
    }
  }
}

int word_ignoring(char *argv, int i) {
  int m = strlen(argv);
  int e_counting = 0;
  int f_counting = 0;
  for (int k = 0; k < m; k++) {
    if (argv[k] == 'e') e_counting++;
    if (argv[k] == 'f') f_counting++;
  }
  if (argv[0] == '-' && argv[m - 1] == 'e' && e_counting < 2 && f_counting == 0)
    i++;
  if (argv[0] == '-' && argv[m - 1] == 'f' && f_counting < 2 && e_counting == 0)
    i++;
  return i;
}

void parsing(char *buffer, char *flags, char word[][256], char *filename, int n,
             int *c_counting, int file_counting, int word_count) {
  int without_v_FLAG = 1, v_FLAG = 0, FLAG = 0, o_FLAG = 0;
  regex_t regex;
  for (int i = 0; i < word_count && FLAG == 0; i++) {
    if (strchr(flags, 'i') != NULL)
      regcomp(&regex, word[i], REG_ICASE);
    else
      regcomp(&regex, word[i], 0);
    if (strchr(flags, 'v') == NULL) {
      without_v_FLAG = 0;
      if (regexec(&regex, buffer, 0, NULL, 0) != 0) {
        without_v_FLAG = 1;
      }
    } else {
      if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
        v_FLAG = 1;
      }
    }
    regfree(&regex);
    if ((without_v_FLAG == 0 && !strchr(flags, 'v')) ||
        (v_FLAG == 0 && i == (word_count - 1) && strchr(flags, 'v'))) {
      FLAG = 1;
      if (!strchr(flags, 'l') && !strchr(flags, 'c')) {
        if (file_counting > 1 && !strchr(flags, 'h') && o_FLAG == 0)
          printf("%s:", filename);
        if (strchr(flags, 'n') && o_FLAG == 0) printf("%d:", n);
        if (strchr(flags, 'o') && !strchr(flags, 'v') && !strchr(flags, 'l') &&
            !strchr(flags, 'c')) {
          o_flag(word, buffer, flags, word_count, o_FLAG);
          o_FLAG = 1;
          FLAG = 0;
        } else
          printf("%s", buffer);
      }
      (*c_counting)++;
    }
  }
}

void o_flag(char word[][256], char *buffer, char *flags, int word_count,
            int o_FLAG) {
  regex_t regex;
  regmatch_t pmatch[100];
  if (o_FLAG == 0) {
    for (int k = 0; k < word_count; k++) {
      if (strchr(flags, 'i') != NULL)
        regcomp(&regex, word[k], REG_ICASE);
      else
        regcomp(&regex, word[k], 0);
      while (regexec(&regex, buffer, 1, pmatch, 0) == 0) {
        int len = pmatch[0].rm_eo - pmatch[0].rm_so;
        buffer = buffer + pmatch[0].rm_so;
        for (int i = 0; i < len; i++) {
          printf("%c", buffer[i]);
        }
        printf("\n");
        buffer = buffer + len;
      }
      regfree(&regex);
    }
  }
}