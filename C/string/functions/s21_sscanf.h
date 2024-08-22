#ifndef STRINGPLUS_S21_SSCANF_H_
#define STRINGPLUS_S21_SSCANF_H_

#include "s21_string.h"

#define SMAX 1024
#define ASCII_TECH_SYMBOLS 33

typedef struct Flags_s {
  int width;         // ширина
  int length;        // длина
  char spec;         // спецификатор
  int zero_symbols;  // для корректного считывания приставки 0x спец. i
  char flag_sign;
  char flag_space;
} Flags_s;

// подсчет удачно считанных спец. и счетчик для спец. n
typedef struct Count {
  int count_format;
  int start;  // подсчет вхождений в функцию
  int end;  // подсчет корректного завершения функций
  int count_symbols;  // подсчет символов для спец. n
  int count_eof;  // запоминаем если первый считываемый символ был конец строки
  int first_read;  // фиксируем первое считывание
  int sign;
  int index;
} Count;

// считывание чисел с плавающей точкой
typedef struct FL {
  int dot;     // найдена точка во float
  int flag_e;  // найдена буква е во float
} FL;

// для сохранения изменений указателей
typedef struct PTR {
  const char *str;
  const char *format;
} PTR;

int s21_sscanf(const char *str, const char *format, ...);

const char *get_width(const char *format, Flags_s *flags);
void get_length(const char *format, Flags_s *flags);
int get_spec(const char *f, Flags_s *flags);

const char *scanf_int(const char *str, Flags_s *flags, va_list *args,
                      Count *count);
const char *scanf_unsign(const char *str, Flags_s *flags, va_list *args,
                         Count *count);
const char *scanf_c(const char *str, Flags_s flags, va_list *args,
                    Count *count);
const char *scanf_s(const char *str, Flags_s flags, va_list *args,
                    Count *count);
const char *scanf_p(const char *str, Flags_s *flags, va_list *args,
                    Count *count);
const char *scan_n(const char *str, va_list *args, Count *count);
const char *scan_f(const char *str, Flags_s *flags, va_list *args,
                   Count *count);

void return_int(va_list *args, char *buff, Flags_s *flags);
void return_unsigned(va_list *args, char *buff, Flags_s *flags, int sign_flag);
void return_float(va_list *args, char *buff, Flags_s *flags);

const char *use_d(const char *str, char *buff, Flags_s *flags, Count *count);
const char *use_i(const char *str, char *buff, Flags_s *flags, Count *count);
const char *use_f(const char *str, Flags_s *flags, Count *count, char *buff);
const char *use_x(const char *str, Flags_s *flags, Count *count, char *buff,
                  int sign_flag);

int for_use_d(int i, const char *str, Flags_s *flags, int sign_flag, int top);
int for_use_i(int i, const char *str, Flags_s *flags, int sign_flag, int range);
int for_use_f(const char *str, Flags_s *flags, Count *count, FL *fl);
int for_scan_p(int i, const char *str, Flags_s *flags);

const char *skip_space(const char *str, Count *count, int activate);
int skip_symbols(const char *str, const char *format, PTR *ptr, Count *count);

void transform(char *buff, int number);
int range_0x(const char *str, int index, int flag_start);
const char *system_8(const char *str, char *buff, Flags_s *flags, Count *count);

const char *add_elem(const char *str, Flags_s *flags, va_list *args);
const char *parser(const char *str, Flags_s *flags, va_list *args,
                   Count *count);
const char *search_sign(const char *str, Count *count, Flags_s *flags);
int search_nan(const char *str, int index);
int search_inf(const char *str);
void scan_f_record(char *buff, Flags_s *flags, Count *count, va_list *args);

#endif  // STRINGPLUS_S21_SSCANF_H_