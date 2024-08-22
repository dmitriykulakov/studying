#ifndef S21_SMART_CALCULATOR_H
#define S21_SMART_CALCULATOR_H

#define P M_PI

typedef struct element {
  double value;
  char letter;
  int priority;
  struct element *next;
} calculate_element;

// q - sqrt
// s - sin
// c - cos
// t - tan
// l - ln
// o - log
// ~ - unary minus
// # - unary plus
// m - mod
// a - asin
// b - acos
// e - atan

int smart_calculator_simple(char *input_str, double x, double *result);
int str_validation(char *str, calculate_element **root);
int find_value(char *str, int *i, double *value);
int find_letter(char *str, int *i, char *letter, int *brake_counter);
char long_name_operation(char *str, int *i);
int find_priority(char letter);
calculate_element *init(char letter, double value, int priority);
calculate_element *push_back(calculate_element *root, char letter, double value,
                             int priority);
calculate_element *push(calculate_element *root, char letter, double value,
                        int priority);
void parsing(calculate_element *root, calculate_element **final);
calculate_element *pop(double *value, char *letter, int *priority,
                       calculate_element *root);
double calculation(calculate_element *final, double x);
void free_root(calculate_element *root);
void annuity(double total_sum, int time, double persent, double *overpayment,
             double *total_payment, double *month_payment);
void diff(double total_sum, int time, double persent, double *overpayment,
          double *total_payment, double *month_payment);

void test_function(char *input_str, double *result);

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif
