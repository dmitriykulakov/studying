#include "s21_smart_calculator.h"

int smart_calculator_simple(char* input_str, double x, double* result) {
  int function_result = 0;
  calculate_element* root = NULL;
  if (strlen(input_str) > 256)
    function_result = 1;
  else {
    function_result = str_validation(input_str, &root);
    if (function_result != 0)
      free_root(root);
    else {
      calculate_element* final = NULL;
      parsing(root, &final);
      *result = calculation(final, x);
    }
  }
  return function_result;
}

int str_validation(char* str, calculate_element** root) {
  int function_result = 0, priority, brake_counter = 0;
  double value = 0.0;
  char letter;
  int n = strlen(str);
  if (str[n - 1] != '=') function_result = 1;
  for (int i = 0; str[i] != '=' && function_result == 0; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      function_result = find_value(str, &i, &value);
      letter = 'd';
    } else if (str[i] == 'x' || str[i] == 'm' || str[i] == 'a' ||
               str[i] == 'c' || str[i] == 's' || str[i] == 'l' ||
               str[i] == 't' || str[i] == '+' || str[i] == '-' ||
               str[i] == '/' || str[i] == '*' || str[i] == '^' ||
               str[i] == '(' || str[i] == ')') {
      value = 0;
      function_result = find_letter(str, &i, &letter, &brake_counter);
    } else
      function_result = 2;
    if (function_result == 0) {
      priority = find_priority(letter);
      if (*root == NULL) {
        *root = init(letter, value, priority);
      } else
        push_back(*root, letter, value, priority);
    }
  }
  if (function_result == 0 && brake_counter != 0) function_result = 3;
  return function_result;
}

int find_value(char* str, int* i, double* value) {
  *value = 0;
  int function_result = 0, n = 0;
  for (; str[*i] >= '0' && str[*i] <= '9' && (str[*i] != '.' && str[*i] != ',');
       (*i)++) {
    *value *= 10;
    *value += (int)(str[*i]) - 48;
  }
  if (str[*i] == '.' || str[*i] == ',') {
    (*i)++;
    if (str[(*i)] >= '0' && str[(*i)] <= '9') {
      for (; str[(*i)] >= '0' && str[(*i)] <= '9'; n++, (*i)++) {
        *value *= 10;
        *value += (int)(str[*i] - 48);
      }
      for (; n > 0; n--) {
        *value /= 10;
      }
    } else
      function_result = 2;
  }
  if (function_result == 0) (*i)--;
  return function_result;
}

int find_letter(char* str, int* i, char* letter, int* brake_counter) {
  int function_result = 0;
  if (str[*i] == '*' || str[*i] == '/' || str[*i] == '^' || str[*i] == ')' ||
      str[*i] == 'm') {
    if (*i == 0)
      function_result = 2;
    else if ((str[(*i) - 1] >= '0' && str[(*i) - 1] <= '9') ||
             str[(*i) - 1] == 'x' || str[(*i) - 1] == ')') {
      *letter = str[*i];
      if (*letter == 'm') (*i) += 2;
      if (*letter == ')') (*brake_counter)--;
    } else
      function_result = 2;
  } else if (str[*i] == 'c' || str[*i] == 's' || str[*i] == 'l' ||
             str[*i] == 't' || str[*i] == 'a') {
    if (*i != 0) {
      if ((str[(*i) - 1] >= '0' && str[(*i) - 1] <= '9') ||
          str[(*i) - 1] == 'x' || str[(*i) - 1] == ')')
        function_result = 2;
    }
    if (function_result == 0) *letter = long_name_operation(str, i);
  } else if (str[*i] == '-' || str[*i] == '+') {
    if (*i == 0) {
      if (str[*i] == '-') *letter = '~';
      if (str[*i] == '+') *letter = '#';
    } else if ((str[(*i) - 1] >= '0' && str[(*i) - 1] <= '9') ||
               str[(*i) - 1] == 'x' || str[(*i) - 1] == ')')
      *letter = str[*i];
    else if (str[*i] == '-')
      *letter = '~';
    else if (str[*i] == '+')
      *letter = '#';
  } else if (str[*i] == '(') {
    if (*i != 0) {
      if ((str[(*i) - 1] >= '0' && str[(*i) - 1] <= '9') ||
          str[(*i) - 1] == 'x' || str[(*i) - 1] == ')')
        function_result = 2;
    }
    if (function_result == 0) {
      *letter = str[*i];
      (*brake_counter)++;
    }
  } else if (str[*i] == 'x') {
    if (*i != 0) {
      if ((str[(*i) - 1] >= '0' && str[(*i) - 1] <= '9') ||
          str[(*i) - 1] == 'x' || str[(*i) - 1] == ')')
        function_result = 2;
    }
    *letter = str[*i];
  }
  if (*brake_counter < 0) function_result = 4;
  return function_result;
}

char long_name_operation(char* str, int* i) {
  char tmp;
  if (str[*i] == 's') {
    if (str[*(i) + 1] == 'i') {
      tmp = 's';
      (*i) += 2;
    } else {
      tmp = 'q';
      (*i) += 3;
    }
  } else if (str[*i] == 'c') {
    tmp = 'c';
    (*i) += 2;
  } else if (str[*i] == 't') {
    tmp = 't';
    (*i) += 2;
  } else if (str[*i] == 'l') {
    if (str[*(i) + 1] == 'n') {
      tmp = 'l';
      (*i)++;
    } else {
      tmp = 'o';
      (*i) += 2;
    }
  } else {
    if (str[*(i) + 1] == 's') tmp = 'a';
    if (str[*(i) + 1] == 'c') tmp = 'b';
    if (str[*(i) + 1] == 't') tmp = 'e';
    (*i) += 3;
  }
  return tmp;
}

int find_priority(char letter) {
  int preority = 0;
  if (letter == '+' || letter == '-') preority = 1;
  if (letter == '*' || letter == '/' || letter == 'm') preority = 2;
  if (letter == '^') preority = 3;
  if (letter == '~' || letter == '#') preority = 4;
  if (letter == 'q' || letter == 'a' || letter == 'b' || letter == 'e' ||
      letter == 's' || letter == 'c' || letter == 'g' || letter == 't' ||
      letter == 'l' || letter == 'o')
    preority = 5;
  if (letter == '(' || letter == ')') preority = 6;
  return preority;
}

calculate_element* init(char letter, double value, int priority) {
  calculate_element* tmp = NULL;
  tmp = (calculate_element*)malloc(sizeof(calculate_element));
  if (tmp != NULL) {
    tmp->letter = letter;
    tmp->value = value;
    tmp->priority = priority;
    tmp->next = NULL;
  }
  return tmp;
}

calculate_element* push_back(calculate_element* root, char letter, double value,
                             int priority) {
  calculate_element* new;
  new = init(letter, value, priority);
  calculate_element* tmp;
  tmp = root;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = new;
  return root;
}

calculate_element* push(calculate_element* root, char letter, double value,
                        int priority) {
  calculate_element* new;
  new = init(letter, value, priority);
  new->next = root;
  return new;
}

void parsing(calculate_element* root, calculate_element** final) {
  int priority;
  double value;
  char letter;
  calculate_element* tmp = NULL;
  while (root != NULL) {
    root = pop(&value, &letter, &priority, root);
    if (priority == 0) {
      if (*final == NULL) {
        *final = init(letter, value, priority);
      } else
        *final = push_back(*final, letter, value, priority);
    } else if (tmp == NULL) {
      tmp = init(letter, value, priority);
    } else if (letter == '(') {
      tmp = push(tmp, letter, value, priority);
    } else if (letter == ')') {
      while (letter != '(') {
        tmp = pop(&value, &letter, &priority, tmp);
        if (letter != '(') *final = push_back(*final, letter, value, priority);
      }
    } else if (priority > tmp->priority) {
      tmp = push(tmp, letter, value, priority);
    } else {
      char letter_tmp = letter;
      double value_tmp = value;
      int priority_tmp = priority;
      while (priority_tmp <= tmp->priority && tmp->priority != 6) {
        tmp = pop(&value, &letter, &priority, tmp);
        *final = push_back(*final, letter, value, priority);
        if (tmp == NULL) break;
      }
      tmp = push(tmp, letter_tmp, value_tmp, priority_tmp);
    }
  }
  while (tmp != NULL) {
    tmp = pop(&value, &letter, &priority, tmp);
    *final = push_back(*final, letter, value, priority);
  }
}

calculate_element* pop(double* value, char* letter, int* priority,
                       calculate_element* root) {
  *letter = root->letter;
  *value = root->value;
  *priority = root->priority;
  calculate_element* tmp = root;
  root = root->next;
  free(tmp);
  return root;
}

double calculation(calculate_element* final, double x) {
  double massive[128] = {0}, value;
  int priority, i = -1, function_result = 0;
  char letter;
  while (final != NULL && function_result == 0) {
    final = pop(&value, &letter, &priority, final);
    if (letter == 'd') {
      i++;
      massive[i] = value;
    } else if (letter == 'x') {
      i++;
      massive[i] = x;
    } else if (letter == '+') {
      massive[i - 1] += massive[i];
      i--;
    } else if (letter == '-') {
      massive[i - 1] -= massive[i];
      i--;
    } else if (letter == '*') {
      massive[i - 1] *= massive[i];
      i--;
    } else if (letter == '/') {
      massive[i - 1] /= massive[i];
      i--;
    } else if (letter == 'm') {
      massive[i - 1] = fmod(massive[i - 1], massive[i]);
      i--;
    } else if (letter == '^') {
      massive[i - 1] = pow(massive[i - 1], massive[i]);
      i--;
    } else if (letter == '~')
      massive[i] = massive[i] * (-1);
    else if (letter == 'c')
      massive[i] = cos(massive[i]);
    else if (letter == 's')
      massive[i] = sin(massive[i]);
    else if (letter == 't')
      massive[i] = tan(massive[i]);
    else if (letter == 'l')
      massive[i] = log(massive[i]);
    else if (letter == 'o')
      massive[i] = log10(massive[i]);
    else if (letter == 'a')
      massive[i] = asin(massive[i]);
    else if (letter == 'b')
      massive[i] = acos(massive[i]);
    else if (letter == 'e')
      massive[i] = atan(massive[i]);
    else if (letter == 'q')
      massive[i] = sqrt(massive[i]);
  }
  return massive[0];
}

void free_root(calculate_element* root) {
  while (root != NULL) {
    calculate_element* tmp = root;
    root = root->next;
    free(tmp);
  }
}

void annuity(double total_sum, int time, double percent, double* overpayment,
             double* total_payment, double* month_payment) {
  double tmp_percent = percent / 100 / 12;
  *month_payment =
      total_sum * (tmp_percent / (1 - pow(1 + tmp_percent, time * (-1))));
  *total_payment = *month_payment * time;
  *overpayment = *total_payment - total_sum;
}

void diff(double total_sum, int time, double percent, double* overpayment,
          double* total_payment, double* month_payment) {
  *month_payment = (total_sum / time) + (total_sum * percent / 100 / 12);
  *overpayment = 0;
  *total_payment = 0;
  double month_clear_payment = total_sum / time;
  for (int i = 0; i < time; i++) {
    *overpayment = *overpayment +
                   ((total_sum - month_clear_payment * i) * percent / 100 / 12);
  }
  *total_payment = total_sum + *overpayment;
}
