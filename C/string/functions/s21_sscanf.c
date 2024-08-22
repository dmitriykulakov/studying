#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  Count count = {0};
  PTR ptr = {0};
  int flag_continue = 0;
  va_list args;
  va_start(args, format);

  while (*format) {
    Flags_s flags = {0};
    count.count_format += 1;

    if (*format == ' ') {
      flags.flag_space = 1;
    }
    flag_continue = skip_symbols(str, format, &ptr, &count);
    format = ptr.format;
    str = ptr.str;

    if (flag_continue) {
      continue;
    }

    if (*format == '%') {
      if (count.count_format > 1) {
        format--;
        if (*format < ASCII_TECH_SYMBOLS) {
          flags.flag_space = 1;
        }
        format++;
      }
      while (!get_spec(format, &flags)) {
        format++;
        format = get_width(format, &flags);
        get_length(format, &flags);
      }
      count.first_read += 1;
      if (flags.spec != 'c' && count.first_read == 1) {
        str = skip_space(str, &count, 1);
        if (*str < ASCII_TECH_SYMBOLS) {
          count.count_eof = 1;
        }
      }
      str = parser(str, &flags, &args, &count);
    } else {
      format++;
    }
  }
  va_end(args);
  return count.end = (count.count_eof && !count.end) ? -1 : count.end;
}

// пропуск повторяющихся символов в str и format
int skip_symbols(const char *str, const char *format, PTR *ptr, Count *count) {
  int flag_continue = 0;

  if (*str == *format) {
    if (*str == '%' && *format == '%') {
      format++;
      if (s21_strchr("cdieEfgGosuxXpn", *format)) {
        format--;
      } else {
        count->count_symbols += 1;
        str++;
        flag_continue = 1;
      }
    } else {
      count->count_symbols += 1;
      format++;
      str++;
      flag_continue = 1;
    }
  }

  ptr->format = format;
  ptr->str = str;

  return flag_continue;
}

// добавление значения ширины в структуру
const char *get_width(const char *format, Flags_s *flags) {
  int flag_end = 0;

  while (*format && !flag_end) {
    if (*format == '*') {
      flags->width = '*';
    } else if (*format >= '0' && *format <= '9') {
      if (flags->width != '*') {
        flags->width = flags->width * 10 + (*format - '0');
      }
    } else {
      flag_end = 1;
    }
    if (!flag_end) {
      format++;
    }
  }

  return format;
}

// добавление значения длины в структуру
void get_length(const char *format, Flags_s *flags) {
  char buff_length[20] = "hlL";
  if (s21_strchr(buff_length, *format)) {
    flags->length = *format;
  }
}

// добавление значения спецификатора в структуру
int get_spec(const char *f, Flags_s *flags) {
  int detected_flag = 0;
  char buff_spec[20] = "cdieEfgGosuxXpn";
  if (s21_strchr(buff_spec, *f)) {
    flags->spec = *f;
    detected_flag = 1;
  } else {
    flags->spec = 0;
  }

  return detected_flag;
}

const char *parser(const char *str, Flags_s *flags, va_list *args,
                   Count *count) {
  if ((flags->spec == 'd' || flags->spec == 'i') &&
      count->start == count->end) {
    str = scanf_int(str, flags, args, count);
  } else if ((flags->spec == 'u' || flags->spec == 'o' || flags->spec == 'x' ||
              flags->spec == 'X') &&
             count->start == count->end) {
    str = scanf_unsign(str, flags, args, count);
  } else if (flags->spec == 'c' && count->start == count->end) {
    str = scanf_c(str, *flags, args, count);
  } else if (flags->spec == 's' && count->start == count->end) {
    str = scanf_s(str, *flags, args, count);
  } else if (flags->spec == 'p' && count->start == count->end) {
    str = scanf_p(str, flags, args, count);
  } else if (flags->spec == 'n' && count->start == count->end) {
    str = scan_n(str, args, count);
  } else if ((flags->spec == 'f' || flags->spec == 'e' || flags->spec == 'E' ||
              flags->spec == 'g' || flags->spec == 'G') &&
             count->start == count->end) {
    str = scan_f(str, flags, args, count);
  }
  return str;
}

// работа спец. при строго интовых значениях, спец. d и i
const char *scanf_int(const char *str, Flags_s *flags, va_list *args,
                      Count *count) {
  count->start += 1;
  char *buff = calloc(SMAX, sizeof(char));
  flags->width = (!flags->width && flags->width != '*') ? SMAX : flags->width;

  if (buff != S21_NULL) {
    str = skip_space(str, count, 1);
    str = search_sign(str, count, flags);

    if (flags->spec == 'd') {
      str = use_d(str, buff, flags, count);
    } else if (flags->spec == 'i') {
      str = use_i(str, buff, flags, count);
    }

    if (s21_strlen(buff) > 0) {
      if (flags->width != '*') {
        count->end += 1;
        return_int(args, buff, flags);
      } else {
        va_arg(*args, int *);
      }
    }

    free(buff);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return str;
}

// перевод из 16 и 8 системы счисления
void transform(char *buff, int number) {
  int n = s21_strlen(buff), tmp, m;
  unsigned int result = 0;

  char *buff_lower = s21_to_lower(buff);

  if (buff_lower != S21_NULL) {
    s21_strncpy(buff, buff_lower, s21_strlen(buff));
    free(buff_lower);

    for (int i = 0, j = n - 1; j > -1; i++, j--) {
      if (number == 16) {
        if (buff[j] > 47 && buff[j] < 58) m = (int)buff[j] - 48;
        if (buff[j] > 96 && buff[j] < 103) m = (int)buff[j] - 87;
      }
      if (number == 8) m = (int)buff[j] - 48;
      result = result + m * (unsigned int)pow(number, i);
    }
    for (int i = 0; result != 0; i++) {
      tmp = result % 10;
      result = result / 10;
      buff[i] = tmp + 48;
      buff[i + 1] = '\0';
    }
    n = s21_strlen(buff);
    for (int i = 0; i < n / 2; i++) {
      char tmp = buff[n - 1 - i];
      buff[n - 1 - i] = buff[i];
      buff[i] = tmp;
    }
  } else {
    fprintf(stderr, "Memory fail");
  }
}

// присваивание int значений с помощью va_arg
void return_int(va_list *args, char *buff, Flags_s *flags) {
  long int new_buff = s21_atoi(buff);

  if (flags->length == 'h') {
    short int *result = va_arg(*args, short int *);
    *result = (flags->flag_sign == '-') ? -new_buff : new_buff;
  } else if (flags->length == 'l') {
    long int *result = va_arg(*args, long int *);
    *result = (flags->flag_sign == '-') ? -new_buff : new_buff;
  } else if (flags->length != 'L') {
    int *result = va_arg(*args, int *);
    *result = (flags->flag_sign == '-') ? -new_buff : new_buff;
  }
}

//присваивание unsigned int значений с помощью va_arg
void return_unsigned(va_list *args, char *buff, Flags_s *flags, int sign_flag) {
  unsigned long int new_buff = s21_atoi(buff);

  if (flags->length == 'h') {
    unsigned short int *result = va_arg(*args, unsigned short int *);
    *result = (sign_flag) ? -new_buff : new_buff;
  } else if (flags->length == 'l') {
    unsigned long int *result = va_arg(*args, unsigned long int *);
    *result = (sign_flag) ? -new_buff : new_buff;
  } else if (flags->length != 'L') {
    unsigned int *result = va_arg(*args, unsigned int *);
    *result = (sign_flag == '-') ? -new_buff : new_buff;
  }
}

// считывание строки при спецификаторе d
const char *use_d(const char *str, char *buff, Flags_s *flags, Count *count) {
  for (int i = 0; !for_use_d(i, str, flags, count->sign, 58); ++i) {
    buff[i] = *str;
    count->count_symbols += 1;
    str++;
  }
  return str;
}

// условия для считывания строки при спец. d
int for_use_d(int i, const char *str, Flags_s *flags, int sign_flag, int top) {
  int flag = 0;
  if (!(i < SMAX && *str != ' ')) {
    flag = 1;
  } else if (!(*str > 47 && *str < top && i < flags->width - sign_flag)) {
    flag = 1;
  }

  return flag;
}

//вся логика при выборе спец. i
const char *use_i(const char *str, char *buff, Flags_s *flags, Count *count) {
  if (*str == '0') {
    flags->zero_symbols = 1;
    count->count_symbols += 1;
    str++;
    if (*str == 'x' || *str == 'X') {
      count->count_symbols += 1;
      str++;
      for (int i = 0; !for_use_i(i, str, flags, count->sign, 0); ++i) {
        buff[i] = *str;
        count->count_symbols += 1;
        str++;
      }
      if (s21_strlen(buff)) {
        transform(buff, 16);
      }
    } else {
      str = system_8(str, buff, flags, count);
    }
    if (s21_strlen(buff) == 0 && flags->zero_symbols == 1) {
      str--;
      if (*str == 'x' || *str == 'X') {
        buff[0] = '0';
        count->count_symbols -= 1;
      } else {
        buff[0] = '0';
        str++;
      }
    }
  } else {
    str = use_d(str, buff, flags, count);
  }

  return str;
}

// условия для считывания строки при спец. i
int for_use_i(int i, const char *str, Flags_s *flags, int sign_flag,
              int range) {
  int flag = 0;
  if (!(i < SMAX && *str != ' ')) {
    flag = 1;
  } else if (!(i < flags->width - sign_flag)) {
    flag = 1;
  } else if (range_0x(str, i, range)) {
    flag = 1;
  }

  return flag;
}

// входит ли символ в диапазон для 16ричной системы исчисления
int range_0x(const char *str, int index, int flag_start) {
  int flag = 0;
  if ((*str == 'x' || *str == 'X') && index == 1 && flag_start == 1) {
    flag = 0;
  } else if (!((*str > 47 && *str < 58) || (*str > 64 && *str < 71) ||
               (*str > 96 && *str < 103))) {
    flag = 1;
  }
  if (*str == ' ') {
    flag = 1;
  }

  return flag;
}

// работа спец. отвечающих за считывание unsigned значений: u o x X
const char *scanf_unsign(const char *str, Flags_s *flags, va_list *args,
                         Count *count) {
  count->start += 1;
  char *buff = calloc(SMAX, sizeof(char));
  int sign_flag = 0;
  flags->width = (!flags->width && flags->width != '*') ? SMAX : flags->width;

  str = skip_space(str, count, 1);
  str = search_sign(str, count, flags);

  if (buff != S21_NULL) {
    if ((flags->spec == 'x' || flags->spec == 'X')) {
      str = use_x(str, flags, count, buff, sign_flag);
    } else if (flags->spec == 'o') {
      str = system_8(str, buff, flags, count);
    } else if (flags->spec == 'u') {
      str = use_d(str, buff, flags, count);
    }
    if (s21_strlen(buff) > 0) {
      count->end += 1;
      if (flags->length != '*') {
        return_unsigned(args, buff, flags, sign_flag);
      }
    }
    free(buff);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return str;
}

// считывание строки при спецификаторе x X
const char *use_x(const char *str, Flags_s *flags, Count *count, char *buff,
                  int sign_flag) {
  int flag_x0 = 0;

  for (int i = 0; !for_use_i(i, str, flags, sign_flag, 1); ++i) {
    if ((i == 0 && *str == '0') || (i == 1 && *str == 'x')) {
      str++;
      count->count_symbols += 1;
      flag_x0++;
      continue;
    }
    buff[i - flag_x0] = *str;
    str++;
    count->count_symbols += 1;
  }
  transform(buff, 16);

  return str;
}

// поиск на наличие отрицательного значения
const char *search_sign(const char *str, Count *count, Flags_s *flags) {
  if (*str == '-') {
    count->sign = 1;
    count->count_symbols += 1;
    flags->flag_sign = '-';
    str++;
  } else if (*str == '+') {
    count->count_symbols += 1;
    flags->flag_sign = '+';
    count->sign = 1;
    str++;
  }

  return str;
}

// пропуск пробелов
const char *skip_space(const char *str, Count *count, int activate) {
  while (*str == ' ') {
    if (activate) {
      count->count_symbols += 1;
    }
    str++;
  }

  return str;
}

// считывание строки в 8 системе счисления
const char *system_8(const char *str, char *buff, Flags_s *flags,
                     Count *count) {
  for (int i = 0; !for_use_d(i, str, flags, count->sign, 56); ++i) {
    buff[i] = *str;
    str++;
    count->count_symbols += 1;
  }
  if (s21_strlen(buff)) {
    transform(buff, 8);
  }

  return str;
}

//вся логика при выборе спец. c
const char *scanf_c(const char *str, Flags_s flags, va_list *args,
                    Count *count) {
  count->start += 1;
  count->count_symbols += 1;
  if (flags.flag_space == 1) {
    for (; *str < 33 && *str; str++)
      ;
  }

  if (flags.width != '*') {
    char *result;
    result = va_arg(*args, char *);
    *result = *str;
    str++;
  }
  count->end += 1;
  return str;
}

//вся логика при выборе спец. s
const char *scanf_s(const char *str, Flags_s flags, va_list *args,
                    Count *count) {
  count->start += 1;
  char *buff = calloc(SMAX, sizeof(char));

  str = skip_space(str, count, 1);
  flags.width = (!flags.width || flags.width == '*') ? 1000 : flags.width;

  if (buff != S21_NULL) {
    for (int i = 0; i < SMAX && *str != '\0' && *str != ' ' && i < flags.width;
         ++i) {
      buff[i] = *str;
      str++;
      count->count_symbols += 1;
    }

    if (s21_strlen(buff) > 0) {
      count->end += 1;
      if (flags.width != '*') {
        char *result;
        result = va_arg(*args, char *);
        s21_strncpy(result, buff, s21_strlen(buff));
      }
    }
    free(buff);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return str;
}

//вся логика при выборе спец. p
const char *scanf_p(const char *str, Flags_s *flags, va_list *args,
                    Count *count) {
  count->start += 1;
  char *buff = calloc(SMAX, sizeof(char));
  str = skip_space(str, count, 1);

  flags->width = (!flags->width && flags->width != '*') ? 1000 : flags->width;
  if (buff != S21_NULL) {
    int flag_x0 = 0;
    for (int i = 0; !for_scan_p(i, str, flags); ++i) {
      if ((i == 0 && *str == '0') || (i == 1 && *str == 'x')) {
        str++;
        count->count_symbols += 1;
        flag_x0++;
        continue;
      }
      buff[i - flag_x0] = *str;
      str++;
      count->count_symbols += 1;
    }

    if (s21_strlen(buff) > 0) {
      count->end += 1;
      if (flags->width != '*') {
        transform(buff, 16);
        int new_buff = s21_strtold(buff);
        int *result = va_arg(*args, int *);
        *result = new_buff;
      }
    } else {
      void **res = va_arg(*args, void **);
      *res = S21_NULL;
    }
    free(buff);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return str;
}

// условия считывания строки при спец. p
int for_scan_p(int i, const char *str, Flags_s *flags) {
  int flag = 0;
  if (!(i < SMAX && i < flags->width)) {
    flag = 1;
  } else if ((i == 1 && *str == 'x')) {
    flag = 0;
  } else if (range_0x(str, i, 1)) {
    flag = 1;
  }
  return flag;
}

// подсчет считанных символов до спец. n
const char *scan_n(const char *str, va_list *args, Count *count) {
  str = skip_space(str, count, 1);

  int *result = va_arg(*args, int *);
  *result = count->count_symbols;

  return str;
}

// вся логика при выборе спец. f
const char *scan_f(const char *str, Flags_s *flags, va_list *args,
                   Count *count) {
  count->start += 1;
  if (s21_strchr("0Ll", flags->length)) {
    char *buff = calloc(SMAX, sizeof(char));
    if (buff != S21_NULL) {
      str = skip_space(str, count, 1);
      str = search_sign(str, count, flags);

      str = use_f(str, flags, count, buff);

      if (s21_strlen(buff) > 0) {
        scan_f_record(buff, flags, count, args);
      }

      free(buff);
    } else {
      fprintf(stderr, "Memory error!");
    }
  }

  return str;
}

void scan_f_record(char *buff, Flags_s *flags, Count *count, va_list *args) {
  int flag_int = 0;

  for (int i = 0; i < (int)s21_strlen(buff) && !flag_int; ++i) {
    if (buff[i] > 47 && buff[i] < 58) {
      flag_int = 1;
    }
  }
  char *lower_buff = s21_to_lower(buff);

  if (lower_buff != S21_NULL) {
    if (!flag_int) {
      if (s21_strstr("nan", lower_buff) || s21_strstr("inf", lower_buff)) {
        flag_int = 1;
      }
    }
    if (flag_int) {
      count->end += 1;
      return_float(args, lower_buff, flags);
    }
    free(lower_buff);
  } else {
    fprintf(stderr, "Memory fail");
  }
}

// считывание строки при спец. f
const char *use_f(const char *str, Flags_s *flags, Count *count, char *buff) {
  FL fl = {0};
  flags->width = (!flags->width && flags->width != '*') ? SMAX : flags->width;
  count->index = 0;

  for (int i = 0; !for_use_f(str, flags, count, &fl); ++i) {
    count->index += 1;
    buff[i] = *str;
    count->count_symbols += 1;
    str++;
  }

  return str;
}

// условия считывания строки при спец. f
int for_use_f(const char *str, Flags_s *flags, Count *count, FL *fl) {
  int flag = 0;

  if (!(count->index < SMAX && count->index < flags->width - count->sign)) {
    flag = 1;
  } else if ((*str == '-' || *str == '+') && fl->flag_e) {
    str--;
    if (*str != 'e') {
      flag = 1;
    }
  } else if (*str == 'e' && !fl->flag_e) {
    fl->flag_e = 1;
  } else if (*str == '.' && !fl->dot) {
    fl->dot = 1;
  } else if (!(*str > 47 && *str < 58)) {
    if (search_nan(str, count->index) && search_inf(str)) {
      flag = 1;
    }
  }
  return flag;
}

int search_nan(const char *str, int index) {
  int flag_return = 0;

  if ((*str == 'N' || *str == 'n') && (index == 0)) {
    str++;
    if (*str == 'A' || *str == 'a') {
      str++;
      if (*str == 'N' || *str == 'n') {
        flag_return = 0;
      } else {
        flag_return = 1;
      }
    } else {
      flag_return = 1;
    }
  } else if ((*str == 'A' || *str == 'a') && (index == 1)) {
    str--;
    if (*str == 'N' || *str == 'n') {
      str++;
      str++;
      if (*str == 'N' || *str == 'n') {
        flag_return = 0;
      } else {
        flag_return = 1;
      }
    } else {
      flag_return = 1;
    }
  } else if ((*str == 'N' || *str == 'n') && (index == 2)) {
    str--;
    if (*str == 'A' || *str == 'a') {
      str--;
      if (*str == 'N' || *str == 'n') {
        flag_return = 0;
      } else {
        flag_return = 1;
      }
    } else {
      flag_return = 1;
    }
  } else {
    flag_return = 1;
  }

  return flag_return;
}

int search_inf(const char *str) {
  int flag_return = 0;

  if (*str == 'I' || *str == 'i') {
    str++;
    if (*str == 'N' || *str == 'n') {
      str++;
      if (*str == 'F' || *str == 'f') {
        flag_return = 0;
      } else {
        flag_return = 1;
      }
    } else {
      flag_return = 1;
    }
  } else if (*str == 'N' || *str == 'n') {
    str--;
    if (*str == 'I' || *str == 'i') {
      str++;
      str++;
      if (*str == 'F' || *str == 'f') {
        flag_return = 0;
      } else {
        flag_return = 1;
      }
    } else {
      flag_return = 1;
    }
  } else if (*str == 'F' || *str == 'f') {
    str--;
    if (*str == 'N' || *str == 'n') {
      str--;
      if (*str == 'I' || *str == 'i') {
        flag_return = 0;
      } else {
        flag_return = 1;
      }
    } else {
      flag_return = 1;
    }
  } else {
    flag_return = 1;
  }

  return flag_return;
}

// присваивание float значений с помощью va_arg
void return_float(va_list *args, char *buff, Flags_s *flags) {
  long double buffer = s21_strtold(buff);

  if (flags->length == 'L') {
    long double *result = va_arg(*args, long double *);
    *result = (flags->flag_sign == '-') ? -buffer : buffer;
  } else if (flags->length == 'l') {
    double *result = va_arg(*args, double *);
    *result = (flags->flag_sign == '-') ? -buffer : buffer;
  } else {
    float *result = va_arg(*args, float *);
    *result = (flags->flag_sign == '-') ? -buffer : buffer;
  }
}
