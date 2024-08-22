#include "s21_sprintf.h"

int s21_sprintf(char *line, const char *form, ...) {
  char specificators[] = "cdieEfgGosuxXpn%";
  char *copy_line = line;
  va_list parameters;
  va_start(parameters, form);

  while (*form) {
    if (*form == '%') {
      form++;
      if (*form == 'n') {
        int *n = va_arg(parameters, int *);
        *n = (int)(line - copy_line);
      } else {
        Flags_p flag = {0};
        flag.calculation_system =
            10;  // Дефолтно устанавливаем 10-ричную систему исчисления
        form = install_flags(&flag, form, &parameters);
        if (!s21_strchr(specificators, *form)) {
          fprintf(stderr, "Error");
        }
        line = parsing_specificators(form, flag, &parameters, line, copy_line);
      }
    } else {
      *line = *form;
      line++;
    }
    form++;
  }

  va_end(parameters);
  return (line - copy_line);
}

const char *install_flags(Flags_p *flag, const char *form,
                          va_list *parameters) {
  form = check_shift_flags(flag, form);
  form = check_width_flag(&flag->width, parameters, form);
  form = check_point_flag(form, flag, parameters);
  form = check_length_flag(form, flag);

  if (flag->length != 0) {
    form++;
  }
  return form;
}

const char *check_shift_flags(Flags_p *flag, const char *form) {
  while (form) {
    if (*form == '-') {
      flag->minus = 1;
    } else if (*form == '+') {
      flag->plus = 1;
    } else if (*form == ' ') {
      flag->space = 1;
    } else if (*form == '#') {
      flag->sharp = 1;
    } else if (*form == '0') {
      flag->zero = 1;
    } else {
      break;
    }
    form++;
  }
  return form;
}

const char *check_width_flag(int *width, va_list *parameters,
                             const char *form) {
  *width = 0;
  if (*form ==
      '*') {  // Если вводится символ '*' это говорит о том что запись ширины
              // будет происходить после всей формы (Пример ввода ширины со
              // звездочкой: sprintf(str, "%*.d", 2, 33) )
    *width = va_arg(*parameters,
                    int);  //  функция va_arg помогает нам считать то что должно
                           //  записываться в буфер вместо символа '*'
    form++;
  }
  while (form) {
    if ('0' <= *form && *form <= '9') {  // Проверяем на число
      *width *= 10;  // Умножаем на 10 для того чтобы записать все цифры
                     // введенного числа от единыц до сотых и тд.
      *width +=
          *form - '0';  // Делаем так чтобы получить число а не символ этого
                        // числа (Пример символа числа: '1') (Пример числа: 1)
                        // по ASCII таблице имеют разные значения
    } else {
      break;
    }
    form++;
  }
  return form;
}

const char *check_point_flag(const char *form, Flags_p *flag,
                             va_list *parameters) {
  if (*form == '.') {
    flag->point = 1;
    flag->zero =
        0;  // Заниуляем потому что не может быть одновременно и точность и ноль
    form++;
    form = check_width_flag(&flag->accuracy, parameters, form);
  }
  return form;
}

const char *check_length_flag(const char *form, Flags_p *flag) {
  switch (*form) {
    case 'L':
      flag->length = 'L';
      break;
    case 'l':
      flag->length = 'l';
      break;
    case 'h':
      flag->length = 'h';
      break;
    default:
      break;
  }
  return form;
}

char *parsing_specificators(const char *form, Flags_p flag, va_list *parameters,
                            char *line, char *copy_line) {
  if (*form == 'd' || *form == 'i') {
    line = print_int(flag, parameters, line);

  } else if (*form == 'c') {
    char symbol = (char)va_arg(*parameters, int);
    line = print_char(line, flag, symbol);

  } else if (*form == 's') {
    line = print_string(flag, line, parameters);

  } else if (*form == 'p') {
    flag.size_for_flag = 1;
    line = print_address(line, &flag, parameters);

  } else if (*form == 'x' || *form == 'X' || *form == 'o' || *form == 'u') {
    flag = select_calculation_system(flag, *form);
    line = print_calculate_system(line, flag, *(form - 1), parameters);

  } else if (*form == '%') {
    line = print_char(line, flag, '%');

  } else if (*form == 'e' || *form == 'E' || *form == 'g' || *form == 'G') {
    flag = select_flag(flag, *form);
    line = print_e_or_g(line, flag, *(form - 1), parameters);

  } else if (*form == 'f') {
    line = print_double(line, flag, *(form - 1), parameters);

  } else {
    line = S21_NULL;
  }

  if (line == S21_NULL) {
    *copy_line = '\0';
  }

  return line;
}

Flags_p select_flag(Flags_p flag, char form) {
  if (form == 'e' || form == 'E') {
    flag.e = 1;
  } else if (form == 'g' || form == 'G') {
    flag.g = 1;
  }
  if (form == 'E' || form == 'G') {
    flag.upper_case = 1;
  }
  return flag;
}

char *print_e_or_g(char *line, Flags_p flag, char form, va_list *parameters) {
  long double number = 0;
  int e = 0;

  if (form == 'l' || form == 'L') {
    number = va_arg(*parameters, double);
  } else {
    number = va_arg(*parameters, double);
  }
  long double copy_num = number;

  if (flag.e) {
    e = normalization(&number, &flag);
  } else if (flag.g) {
    flag = short_present(flag, number);
  }

  char *number_to_string = calloc(BUFFER, sizeof(char));

  if (number_to_string != S21_NULL) {
    int position =
        double_to_string(number_to_string, flag, number, copy_num, e);

    for (int i = position - 1; i >= 0; i--) {
      *line = number_to_string[i];
      line++;
    }
    while ((position < flag.width)) {
      *line = ' ';
      line++;
    }
    *line = '\0';

    free(number_to_string);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return line;
}

Flags_p short_present(Flags_p flag, long double number) {
  Flags_p copy_flag = flag;
  long double copy_number = number;
  int e = normalization(&copy_number, &copy_flag);

  if (copy_flag.accuracy == 0 && !copy_flag.point) {
    copy_flag.accuracy = 6;
  }

  if ((e <= 4 && copy_flag.e == 1) || (copy_flag.e == 2 && e < 6)) {
    copy_flag.e = 0;
  }
  return copy_flag;
}

long double normalization(long double *number, Flags_p *flag) {
  int i = 0;
  if (fabsl(*number) > 1) {
    while (fabsl(*number) > 10) {
      *number /= 10;
      i++;
      flag->e = 2;
    }
  } else {
    while (fabsl(*number) < 0.999999) {
      if (*number == 0) {
        flag->e = 2;
        break;
        ;
      }
      *number *= 10;
      i++;
      flag->e = 1;
    }
  }
  return i;
}

char *print_double(char *line, Flags_p flag, char form, va_list *parameters) {
  long double number = 0;
  int e = 0;

  if (form == 'l' || form == 'L') {
    number = va_arg(*parameters, long double);
  } else {
    number = va_arg(*parameters, double);
  }
  long double copy_num = number;

  char *number_to_string = calloc(BUFFER, sizeof(char));

  if (number_to_string != S21_NULL) {
    int position =
        double_to_string(number_to_string, flag, number, copy_num, e);

    for (int i = position - 1; i >= 0; i--) {
      *line = number_to_string[i];
      line++;
    }

    while ((position < flag.width)) {
      *line = ' ';
      line++;
    }
    *line = '\0';

    free(number_to_string);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return line;
}

int double_to_string(char *number_to_string, Flags_p flag, long double number,
                     long double copy_num, int e) {
  char mantis[5] = "";

  if (flag.upper_case && number > 0) {
    s21_strncpy(mantis, "0+E", s21_strlen("0+E"));
  } else {
    s21_strncpy(mantis, "0+e", s21_strlen("0+e"));
  }

  int is_nan_or_infinity = is_infinity_or_nan(number);

  if (number < 0 && number != -INFINITY) {
    number = -number;
  }

  int position = 0;
  long double copy_number = number;
  int count_numbers = 0;

  long double total = 0;
  long double fraction = modfl(number, &total);

  double copy_fraction = fraction;
  long int copy_of_copy_num = copy_num;

  int result = 0;
  if (flag.e) {
    while (copy_of_copy_num != 0) {
      copy_of_copy_num /= flag.calculation_system;
      result++;
    }
    result--;
    int copy_result = result;

    int index = 0;
    char temp[10];
    while (copy_result > 0) {
      temp[index] = copy_result % flag.calculation_system + '0';
      copy_result /= flag.calculation_system;
      index++;
      count_numbers++;
    }
    temp[index] = '\0';

    count_numbers = count_for_flag_e(temp, index, count_numbers);
    if (result == 0) {
      s21_strncpy(&number_to_string[position], "0", 1);
      position++;
      count_numbers++;
    } else {
      s21_strncpy(&number_to_string[position], temp, s21_strlen(temp));
      position++;
      count_numbers++;
    }
  }
  result = 0;

  position = not_nan_or_infinity(
      is_nan_or_infinity, fraction, total, flag, copy_fraction, count_numbers,
      mantis, number_to_string, position, e, number, copy_number);
  return position;
}

int count_for_flag_e(char *temp, int index, int count_numbers) {
  for (int i = 0; i < index; i++) {
    char symbol = temp[i];
    temp[i] = temp[index - i - 1];
    temp[index - i - 1] = symbol;
    count_numbers++;
  }
  return count_numbers;
}

int not_nan_or_infinity(int is_nan_or_infinity, long double fraction,
                        long double total, Flags_p flag, double copy_fraction,
                        int count_numbers, char *mantis, char *number_to_string,
                        int position, int e, long double number,
                        long double copy_number) {
  if (!is_nan_or_infinity) {
    if (fraction + 0.000000000000001 >= 1) {
      fraction = 0;
      total += 1;
    }

    int accuracy = 6;
    if (flag.accuracy) accuracy = flag.accuracy;

    copy_fraction += 0.000000000000001;

    for (int i = 0; i < accuracy; i++) copy_fraction *= flag.calculation_system;

    if (flag.g) {
      accuracy = 0;
    }

    if (fmodl(fabsl(fraction) * 10, 10.0) > 4) fraction = roundl(fraction);

    if (flag.e || e) {
      count_numbers = 4;
      for (int i = 0; mantis[i] != '\0'; i++) {
        number_to_string[position] = mantis[i];
        position++;
      }
    }

    int count = 0;
    count = count_for_flag_g(total, flag, copy_fraction, count);
    int res = 0;
    while ((long)copy_fraction != 0 && flag.g) {
      if (count > 6) {
        copy_fraction /= flag.calculation_system;
        count--;
        continue;
      }
      char symbol = (long)copy_fraction % flag.calculation_system + '0';
      if (symbol == '0' && res == 0) {
        position++;
        copy_fraction /= flag.calculation_system;
        continue;
      }
      if (symbol != '0') res = 1;

      number_to_string[position] = symbol;
      position++;
      count_numbers++;
      copy_fraction /= flag.calculation_system;
    }
    copy_fraction += 0.0000001;

    position = write_double(copy_fraction, flag, number_to_string, position,
                            count_numbers, total, number, copy_number);
  } else {
    position = print_nan_or_inf(number, position, number_to_string);
  }
  return position;
}

int count_for_flag_g(long double total, Flags_p flag, double copy_fraction,
                     int count) {
  long double buff = total;
  while ((long)buff != 0) {
    count++;
    buff /= flag.calculation_system;
  }

  long double cop = copy_fraction;
  while ((long)cop != 0 && flag.g) {
    count++;
    cop /= flag.calculation_system;
  }
  return count;
}

int write_double(double copy_fraction, Flags_p flag, char *number_to_string,
                 int position, int count_numbers, long double total,
                 long double number, long double copy_number) {
  position = zero_fraction(copy_fraction, number_to_string, position);
  while ((long)copy_fraction != 0) {
    char symbol = (long)copy_fraction % flag.calculation_system + '0';
    number_to_string[position] = symbol;
    position++;
    count_numbers++;
    copy_fraction /= flag.calculation_system;
  }
  if ((long)copy_fraction == 0) {
    number_to_string[position] = '.';
    position++;
    count_numbers++;
  }
  while ((long)total != 0) {
    char symbol = (long)total % flag.calculation_system + '0';
    number_to_string[position] = symbol;
    position++;
    count_numbers++;
    total /= flag.calculation_system;
  }
  if (total == 0) {
    number_to_string[position] = 0 + '0';
    position++;
  }
  int copy_position = position;

  while (flag.zero && number_to_string && (flag.width - copy_position)) {
    number_to_string[position] = '0';
    position++;
    count_numbers++;
    flag.width--;
  }
  if (flag.space && number >= 0) {
    number_to_string[position] = ' ';
    position++;
    count_numbers++;
  }
  if (copy_number < 0) {
    number_to_string[position] = '-';
    position++;
    count_numbers++;
  }
  if (number > 0 && flag.plus) {
    number_to_string[position] = '+';
    position++;
    count_numbers++;
  }
  position =
      write_width_for_double(flag, count_numbers, position, number_to_string);

  return position;
}

int zero_fraction(double copy_fraction, char *number_to_string, int position) {
  if ((long)copy_fraction == 0) {
    for (int i = 0; i < 6; i++) {
      number_to_string[position] = '0';
      position++;
    }
  }
  return position;
}

int write_width_for_double(Flags_p flag, int count_numbers, int position,
                           char *number_to_string) {
  if (flag.width && flag.width > count_numbers) {
    flag.width -= count_numbers;
  } else {
    flag.width = 0;
  }

  while (flag.width && number_to_string) {
    number_to_string[position] = ' ';
    position++;
    flag.width--;
  }
  return position;
}

int is_infinity_or_nan(long double number) {
  int result = 0;
  if (number == INFINITY) {
    result = 1;
  }
  if (number == -INFINITY) {
    result = 1;
  }
  if ((number) != (number)) {
    result = 1;
  }

  return result;
}

char *print_address(char *line, Flags_p *flag, va_list *parameters) {
  unsigned long int number =
      (unsigned long int)va_arg(*parameters, unsigned long int);

  flag->calculation_system = 16;
  flag->sharp = 1;
  flag->upper_case = 0;

  char *number_to_string = calloc(BUFFER, sizeof(char));

  if (number_to_string != S21_NULL) {
    int position = unsigned_int_to_string(number_to_string, *flag, number);

    for (int i = position - 1; i >= 0; i--) {
      *line = number_to_string[i];
      line++;
    }
    while ((position < flag->width)) {
      *line = ' ';
      line++;
    }
    free(number_to_string);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return line;
}

Flags_p select_calculation_system(Flags_p flag, char form) {
  if (form == 'x') {
    flag.calculation_system = 16;
  } else if (form == 'X') {
    flag.calculation_system = 16;
    flag.upper_case = 1;
  } else if (form == 'o') {
    flag.calculation_system = 8;
  }
  return flag;
}

char *print_calculate_system(char *line, Flags_p flag, char form,
                             va_list *parameters) {
  unsigned long int number = 0;
  if (form == 'l') {
    number = (unsigned long int)va_arg(*parameters, long int);
  } else if (form == 'h') {
    number = (unsigned short)va_arg(*parameters, int);
  } else {
    number = (unsigned int)va_arg(*parameters, int);
  }

  char *number_to_string = calloc(BUFFER, sizeof(char));

  if (number_to_string != S21_NULL) {
    int position = unsigned_int_to_string(number_to_string, flag, number);

    for (int i = position - 1; i >= 0; i--) {
      *line = number_to_string[i];
      line++;
    }
    while ((position < flag.width)) {
      *line = ' ';
      line++;
    }
    *line = '\0';

    free(number_to_string);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return line;
}

int print_nan_or_inf(long double number, int position, char *number_to_string) {
  char buff_nan[] = "nan";
  char buff_inf[] = "fni";
  char buff_minus_inf[] = "fni-";

  if (number == INFINITY) {
    for (int i = 0; i < 3; i++) {
      number_to_string[position] = buff_inf[i];
      position++;
    }
  }
  if ((number) != (number)) {
    for (int i = 0; i < 3; i++) {
      number_to_string[position] = buff_nan[i];
      position++;
    }
  }
  if (number == -INFINITY) {
    for (int i = 0; i < 4; i++) {
      number_to_string[position] = buff_minus_inf[i];
      position++;
    }
  }
  return position;
}

int unsigned_int_to_string(char *number_to_string, Flags_p flag,
                           unsigned long int number) {
  int position = 0;
  int is_nan_or_inf = is_infinity_or_nan(number);
  if (!is_nan_or_inf) {
    int result = 0;
    unsigned long int copy_number = number;
    long int res = copy_number;
    flag.width = write_width_for_unsigned_int(flag, res, result);
    if (flag.sharp && flag.width && flag.calculation_system == 16) {
      flag.width -= 2;
    }
    if (flag.sharp && flag.width && flag.calculation_system == 8) {
      flag.width -= 1;
    }
    if (flag.accuracy - position > 0) {
      flag.accuracy -= position;
      flag.zero = 1;
    }
    if (flag.sharp && flag.calculation_system == 16) {
      flag.accuracy++;
    }
    while (flag.width && number_to_string && flag.minus) {
      number_to_string[position] = ' ';
      position++;
      flag.width--;
    }
    if ((copy_number == 0 && (flag.accuracy || flag.width || flag.space)) ||
        (copy_number == 0 && !flag.accuracy && !flag.width && !flag.space &&
         !flag.point)) {
      char symbol = copy_number % flag.calculation_system + '0';
      number_to_string[position] = symbol;
      position++;
      copy_number /= flag.calculation_system;
    }
    position = print_letters(flag, copy_number, number_to_string, position);
    if (flag.accuracy - position > 0) {
      flag.accuracy -= position;
      flag.zero = 1;
    }
    if (flag.zero == 1 && flag.size_for_flag == 1) {
      flag.zero = 0;
    }
    flag.accuracy = (flag.sharp) ? flag.accuracy - 1 : flag.accuracy;
    position =
        write_letters_for_calculate_system(flag, number_to_string, position);
  } else {
    position =
        print_nan_or_inf((long double)number, position, number_to_string);
  }
  return position;
}

int write_width_for_unsigned_int(Flags_p flag, int res, int result) {
  if (flag.width) {
    while (res != 0) {
      res /= flag.calculation_system;
      result++;
    }
    if (flag.width <= result) {
      flag.width = 0;
    }
    if (flag.width > result) {
      flag.width -= result;
    }
  }
  return flag.width;
}

int write_letters_for_calculate_system(Flags_p flag, char *number_to_string,
                                       int position) {
  while (number_to_string && flag.accuracy > 0) {
    number_to_string[position] = '0';
    position++;
    flag.accuracy--;
    flag.width--;
  }
  position = write_letters(flag, number_to_string, position);

  return position;
}

int write_letters(Flags_p flag, char *number_to_string, int position) {
  if (flag.sharp && flag.calculation_system == 16 && flag.upper_case) {
    number_to_string[position] = 'X';
    position++;

    number_to_string[position] = '0';
    position++;
  } else if (flag.sharp && flag.calculation_system == 16 && !flag.upper_case) {
    number_to_string[position] = 'x';
    position++;

    number_to_string[position] = '0';
    position++;
  } else if (flag.sharp && flag.calculation_system == 8) {
    number_to_string[position] = '0';
    position++;
  }
  while (flag.width > 0 && number_to_string && !flag.zero) {
    number_to_string[position] = ' ';
    position++;
    flag.width--;
  }
  while (flag.width > 0 && number_to_string && flag.zero) {
    number_to_string[position] = '0';
    position++;
    flag.width--;
  }
  return position;
}

int print_letters(Flags_p flag, unsigned long int copy_number,
                  char *number_to_string, int position) {
  while (copy_number != 0 && number_to_string) {
    char symbol = copy_number % flag.calculation_system + '0';
    if ((symbol >= ':' &&
         symbol <= '?')) {  // Данное условие нужно для печати букв в 16-ричной
                            // системе исчисления
      if (flag.upper_case) {
        symbol -= 32;
      }
      symbol += 39;
    }
    number_to_string[position] = symbol;
    position++;
    copy_number /= flag.calculation_system;
  }
  return position;
}

char *print_int(Flags_p flag, va_list *parameters, char *line) {
  int number = 0;
  if (flag.length == 'l') {
    number = (long int)va_arg(*parameters, long int);
  } else if (flag.length == 'h') {
    number = (short)va_arg(*parameters, int);
  } else {
    number = (int)va_arg(*parameters, int);
  }

  char *number_to_string = calloc(BUFFER, sizeof(char));

  if (number_to_string != S21_NULL) {
    int position = int_to_string(flag, number, number_to_string);
    for (int i = position - 1; i >= 0; i--) {
      *line = number_to_string[i];
      line++;
    }
    while ((position < flag.width)) {
      *line = ' ';
      line++;
    }
    *line = '\0';

    free(number_to_string);
  } else {
    fprintf(stderr, "Memory fail\n");
  }

  return line;
}

char *print_char(char *line, Flags_p flag, char symbol) {
  char *copy_line = S21_NULL;

  while (flag.width > 1 && !flag.minus) {
    *line = ' ';
    line++;
    flag.width--;
  }

  if (symbol < 127) {
    *line = symbol;
    line++;

    while (flag.width > 1 && flag.minus) {
      *line = ' ';
      line++;
      flag.width--;
    }
    *line = '\0';

    copy_line = line;
  }
  return copy_line;
}

char *print_string(Flags_p flag, char *line, va_list *parameters) {
  char *copy_line = line;
  char *string = va_arg(*parameters, char *);

  if (string) {
    int width = flag.width;

    if ((s21_size_t)flag.width < s21_strlen(string)) {
      flag.width = s21_strlen(string);
    }
    int count_space = flag.width - s21_strlen(string);
    if (flag.accuracy == 0) {
      flag.accuracy = flag.width;
    }
    if (flag.accuracy != 0 && flag.accuracy < width) {
      count_space = width - flag.accuracy;
    }
    while (count_space && !flag.minus) {
      *line = ' ';
      line++;
      count_space--;
    }

    while (*string != '\0') {
      if (!flag.accuracy) {
        break;
      }
      *line = *string;
      line++;
      string++;
      flag.accuracy--;
    }

    while (count_space && flag.minus) {
      *line = ' ';
      line++;
      count_space--;
    }
  } else {
    line = s21_memcpy(line, "(null)", 6);
    line += 6;
  }
  *line = '\0';

  if (copy_line) {
    copy_line = line;
  }
  return copy_line;
}

int int_to_string(Flags_p flag, long int number, char *number_to_string) {
  int position = 0;
  int is_nan_or_inf = is_infinity_or_nan(number);
  if (!is_nan_or_inf) {
    int result = 0;

    if (number < 0) {
      result = 1;
      number = -number;
      flag.width--;
    }
    if (flag.space) flag.width--;

    long int copy_number = number;
    long int res = copy_number;

    if (flag.width) {
      int result = 0;
      while (res != 0) {
        res /= flag.calculation_system;
        result++;
      }
      if (flag.width <= result) {
        flag.width = 0;
      }
      if (flag.width > result) {
        flag.width -= result;
      }
    }
    while (flag.minus && number_to_string && flag.width) {
      number_to_string[position] = ' ';
      position++;
      flag.width--;
    }
    position = write_int_number(flag, number_to_string, position, copy_number);

    if (flag.accuracy - position > 0) {
      flag.accuracy -= position;
      flag.zero = 1;
    }
    if (result && !flag.zero) {
      number_to_string[position] = '-';
      position++;
      number = -number;
    }
    while (flag.zero && flag.width) {
      number_to_string[position] = '0';
      position++;
      flag.width--;
    }
    if (result) number = -number;

    position = write_signs(flag, number_to_string, position, number, result);
  } else {
    position =
        print_nan_or_inf((long double)number, position, number_to_string);
  }
  return position;
}

int write_int_number(Flags_p flag, char *number_to_string, int position,
                     long int copy_number) {
  while (flag.width && number_to_string && flag.minus) {
    number_to_string[position] = ' ';
    position++;
    flag.width--;
  }
  if ((copy_number == 0 && (flag.accuracy || flag.width || flag.space)) ||
      (copy_number == 0 && !flag.accuracy && !flag.width && !flag.space &&
       !flag.point)) {
    char symbol = copy_number % flag.calculation_system + '0';
    number_to_string[position] = symbol;
    position++;
    copy_number /= flag.calculation_system;
  }
  while (copy_number != 0 && number_to_string) {
    char symbol = copy_number % flag.calculation_system + '0';
    number_to_string[position] = symbol;
    position++;
    copy_number /= flag.calculation_system;
  }
  return position;
}

int write_signs(Flags_p flag, char *number_to_string, int position,
                long int number, int result) {
  while (flag.zero && number_to_string && flag.accuracy) {
    number_to_string[position] = '0';
    position++;
    flag.accuracy--;
  }
  while (flag.width && number_to_string) {
    number_to_string[position] = ' ';
    position++;
    flag.width--;
  }
  if (flag.space && number >= 0) {
    number_to_string[position] = ' ';
    position++;
  }
  if (number < 0) {
    number_to_string[position] = '-';
    position++;
  }
  if (number > 0 && flag.plus && !result) {
    number_to_string[position] = '+';
    position++;
  }
  return position;
}