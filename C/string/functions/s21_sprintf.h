#ifndef STRINGPLUS_S21_SPRINTF_H_
#define STRINGPLUS_S21_SPRINTF_H_

#define BUFFER 1024

#include "s21_string.h"

typedef struct {
  int minus;     // Сдвиг в левый край
  int plus;      // Указать знак числа
  int space;     // Доп пробел/Доп знак
  int sharp;     // 16/8-ричная запись
  int zero;      // Заполнить пустоту нулями
  int width;     // Ширина
  int length;    // Длина для переменных типа double
  int accuracy;  // Точность после .
  int calculation_system;  // Система исчисления
  int point;               // Точка
  int upper_case;          // Верхний регистр
  int size_for_flag;       //
  int g;                   // Флаг g
  int e;                   // Научная нотация
} Flags_p;

int s21_sprintf(char *line, const char *form, ...);
char *parsing_specificators(const char *form, Flags_p flag, va_list *parameters,
                            char *line, char *copy_line);
char *print_int(Flags_p flag, va_list *parameters, char *line);
int int_to_string(Flags_p flag, long int number, char *number_to_string);
const char *install_flags(Flags_p *flag, const char *form, va_list *parameters);
const char *check_shift_flags(Flags_p *flag, const char *form);
const char *check_width_flag(int *width, va_list *parameters, const char *form);
const char *check_point_flag(const char *form, Flags_p *flag,
                             va_list *parameters);
const char *check_length_flag(const char *form, Flags_p *flag);
char *print_char(char *line, Flags_p flag, char symbol);
char *print_string(Flags_p flag, char *line, va_list *parameters);
void print_count(va_list *parameters, char *line, char *copy_line);
Flags_p select_calculation_system(Flags_p flag, char form);
char *print_calculate_system(char *line, Flags_p flag, char form,
                             va_list *parameters);
int unsigned_int_to_string(char *number_to_string, Flags_p flag,
                           unsigned long int number);
char *print_address(char *line, Flags_p *flag, va_list *parameters);
char *print_double(char *line, Flags_p flag, char form, va_list *parameters);
int double_to_string(char *number_to_string, Flags_p flag, long double number,
                     long double copy_num, int e);
int is_infinity_or_nan(long double number);

long double normalization(long double *number, Flags_p *flag);
Flags_p short_present(Flags_p flag, long double number);
char *print_e_or_g(char *line, Flags_p flag, char form, va_list *parameters);
Flags_p select_flag(Flags_p flag, char form);

int write_int_number(Flags_p flag, char *number_to_string, int position,
                     long int copy_number);
int write_signs(Flags_p flag, char *number_to_string, int position,
                long int number, int result);
int print_letters(Flags_p flag, unsigned long int copy_number,
                  char *number_to_string, int position);

int write_letters_for_calculate_system(Flags_p flag, char *number_to_string,
                                       int position);
int write_letters(Flags_p flag, char *number_to_string, int position);

int print_nan_or_inf(long double number, int position, char *number_to_string);
int write_width_for_double(Flags_p flag, int count_numbers, int position,
                           char *number_to_string);
int count_for_flag_g(long double total, Flags_p flag, double copy_fraction,
                     int count);
int count_for_flag_e(char *temp, int index, int count_numbers);
int write_width_for_unsigned_int(Flags_p flag, int res, int result);
int zero_fraction(double copy_fraction, char *number_to_string, int position);

int not_nan_or_infinity(int is_nan_or_infinity, long double fraction,
                        long double total, Flags_p flag, double copy_fraction,
                        int count_numbers, char *mantis, char *number_to_string,
                        int position, int e, long double number,
                        long double copy_number);
int write_double(double copy_fraction, Flags_p flag, char *number_to_string,
                 int position, int count_numbers, long double total,
                 long double number, long double copy_number);

#endif  // STRINGPLUS_S21_SPRINTF_H_