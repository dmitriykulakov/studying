#include <stdio.h>
#include <string.h>

#include "s21_cat.h"

int flags_building(char *flags, char *argv[], int argc, int *n_flags_FLAG) {
  int i, n_flags = 0;
  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (!strcmp(argv[i], "--number-nonblank")) strcpy(argv[i], "-b");
    if (!strcmp(argv[i], "--number")) strcpy(argv[i], "-n");
    if (!strcmp(argv[i], "--squeeze-blank")) strcpy(argv[i], "-s");
  }
  for (i = 1; i < argc && argv[i][0] == '-' && *(n_flags_FLAG) == 0; i++) {
    *(n_flags_FLAG) = massive_building(flags, argv[i], &n_flags);
  }
  flags[n_flags] = '\0';
  return i;
}

int massive_building(char *flags, char *argv, int *n_flags) {
  int j = 1, n_flags_FLAG = 0;
  while (argv[j] != '\0' && n_flags_FLAG == 0) {
    switch (argv[j]) {
      case 'b':
        flags[*n_flags] = argv[j];
        break;
      case 'n':
        flags[*n_flags] = argv[j];
        break;
      case 'T':
        flags[*n_flags] = 't';
        break;
      case 'E':
        flags[*n_flags] = 'e';
        break;
      case 's':
        flags[*n_flags] = 's';
        break;
      case 'v':
        flags[*n_flags] = 'v';
        break;
      case 't':
        flags[*n_flags] = 't';
        flags[*n_flags + 1] = 'v';
        (*n_flags)++;
        break;
      case 'e':
        flags[*n_flags] = 'e';
        flags[*n_flags + 1] = 'v';
        (*n_flags)++;
        break;
      default:
        n_flags_FLAG = 1;
        fprintf(stderr,
                "cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n",
                argv[j]);
    }
    (*n_flags)++;
    j++;
  }
  return n_flags_FLAG;
}

void work_with_the_file(char *flags, char *argv[], int argc, int i) {
  char letter;
  int FLAG = 0, n_FLAG = 1;
  for (; i < argc; i++) {
    int n = 1;
    FILE *fp;
    if ((fp = fopen(argv[i], "r")) != NULL) {
      n_FLAG = 1;
      letter = fgetc(fp);
      while (letter != EOF) {
        parsing(letter, flags, &FLAG, &n, &n_FLAG);
        letter = fgetc(fp);
      }
    } else
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
    fclose(fp);
  }
}

void parsing(char letter, char *flags, int *FLAG, int *n, int *n_FLAG) {
  int b_FLAG = 0, s_FLAG = 0;
  if (letter != '\n' && *n_FLAG == 1) {
    b_FLAG = 1;
  }
  if (strchr(flags, 's') != NULL && *n_FLAG == 1 && *FLAG == 1 &&
      letter == '\n')
    s_FLAG = 1;
  if (*n_FLAG == 1 && letter == '\n') *FLAG = 1;
  if (s_FLAG == 0) {
    if (strchr(flags, 'b') != NULL) {
      if (b_FLAG == 1) {
        printf("%6d\t", *n);
        if (strchr(flags, 'e') != NULL) e_flag(letter);
        (*n)++;
      }
    } else {
      if (strchr(flags, 'n') != NULL && *n_FLAG == 1) {
        printf("%6d\t", *n);
        (*n)++;
      }
    }
    if (strchr(flags, 'v') != NULL) v_flag(&letter);
    if (strchr(flags, 't') != NULL) t_flag(&letter);
    if (strchr(flags, 'e') != NULL) e_flag(letter);
    printf("%c", letter);
  }
  if (letter != '\n') {
    *n_FLAG = 0;
    *FLAG = 0;
  } else {
    *n_FLAG = 1;
  }
}

void v_flag(char *letter) {
  if (((*letter >= 0 && *letter <= 32) || *letter == 127) && *letter != '\n' &&
      *letter != ' ' && *letter != '\t') {
    printf("^");
    if (*letter == 127)
      *letter = 63;
    else
      *letter = *letter + 64;
  }
}

void t_flag(char *letter) {
  if (*letter == '\t') {
    printf("^");
    *letter = *letter + 64;
  }
}

void e_flag(char letter) {
  if (letter == '\n') printf("$");
}