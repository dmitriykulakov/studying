#include "s21_grep.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char flags[100] = {0};
  char f_words[1000] = {0};
  int n_flags_FLAG = 0, i = 1, m = 0;
  if (argc >= 2) {
    building(flags, argv, argc, &n_flags_FLAG);
    int word_count = word_counting(flags, argv, argc, f_words);
    char word[word_count][256];
    if (n_flags_FLAG == 0 && word_count > 0) {
      if (strchr(flags, 'e')) m = e_flag(argv, argc, word);
      if (strchr(flags, 'f')) f_flag(word, m, f_words);
      if (!strchr(flags, 'e') && !strchr(flags, 'f'))
        i = word_building(argv, argc, word);
      work_with_the_file(flags, word, argv, argc, i, word_count);
    }
  }
  return 0;
}