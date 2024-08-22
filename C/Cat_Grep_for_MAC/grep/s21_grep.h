#ifndef S21_GREP_H
#define S21_GREP_H

void building(char *flags, char *argv[], int argc, int *n_flags_FLAG);
int word_counting(char *flags, char *argv[], int argc, char *f_words);
int f_word_counting(char *argv[], int argc, int *word_count, char *f_words);
int e_flag(char *argv[], int argc, char word[][256]);
void f_flag(char word[][256], int m, char *f_words);
int word_building(char *argv[], int argc, char word[][256]);
void work_with_the_file(char *flags, char word[][256], char *argv[], int argc,
                        int i, int word_count);
int word_ignoring(char *argv, int i);
void parsing(char *buffer, char *flags, char word[][256], char *filename, int n,
             int *c_counting, int file_counting, int word_count);
void o_flag(char word[][256], char *buffer, char *flags, int word_count,
            int o_FLAG);

#endif