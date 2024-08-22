#ifndef S21_CAT_H
#define S21_CAT_H

int flags_building(char *flags, char *argv[], int argc, int *n_flags_FLAG);
int massive_building(char *flags, char *argv, int *n_flags);
void work_with_the_file(char *flags, char *argv[], int argc, int i);
void parsing(char letter, char *flags, int *FLAG, int *n, int *b_FLAG);
void v_flag(char *letter);
void t_flag(char *letter);
void e_flag(char letter);

#endif