#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "ctype.h"
#include "string.h"

int s21_sprintf(char* buff, const char* format, ...) {
  s21_size_t j = 0;

  va_list args;
  va_start(args, format);
  for (s21_size_t i = 0; format[i] != '\0'; i++) {
    struct s21_format_spec spec = {0};
    if (format[i] == '%') {
      if (format[i + 1] == '%') {
        buff[j] = '%';
        i++;
        j++;
      } else {
        s21_sprintf_parser(format, &i, &spec);
        choose_spacifer(buff, &j, &spec, &args);
      }
    } else {
      buff[j] = format[i];
      j++;
    }
  }
  va_end(args);

  buff[j] = '\0';

  return 0;
}

void s21_sprintf_parser(const char* format, s21_size_t* i,
                        struct s21_format_spec* spec) {
  (*i)++;

  while (format[*i] == '-' || format[*i] == '+' || format[*i] == ' ') {
    switch (format[*i]) {
      case '-':
        spec->flag_minus = 1;
        break;
      case '+':
        spec->flag_plus = 1;
        break;
      case '#':
        spec->flag_hash = 1;
        break;
      case '0':
        spec->flag_zero = 1;
        break;
      case ' ':
        spec->flag_space = 1;
        break;
    }
    (*i)++;
  }

  if (format[*i] >= '1' && format[*i] <= '9') {
    spec->width = 0;
    while (isdigit(format[*i])) {
      spec->width = spec->width * 10 + (format[*i] - '0');
      (*i)++;
    }
  }

  if (format[*i] == '.') {
    (*i)++;
    spec->precision = 0;
    while (isdigit(format[*i])) {
      spec->precision = spec->precision * 10 + (format[*i] - '0');
      (*i)++;
    }
  }

  if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'L') {
    spec->length = format[*i];
    (*i)++;
  }

  spec->specifier = format[*i];
}

void choose_spacifer(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                     va_list* args) {
  switch (spec->specifier) {
    case 'c':
      handle_char(buff, j, spec, args);
      break;
    case 'd':
      handle_int(buff, j, spec, args);
      break;
    case 'f':
      handle_float(buff, j, spec, args);
      break;
    case 's':
      handle_string(buff, j, spec, args);
      break;
    case 'u':
      handle_unsigned_int(buff, j, spec, args);
      break;
    default:
      break;
  }
}

void handle_char(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                 va_list* args) {
  char ch = (char)va_arg(*args, int);

  if (spec->flag_minus) {
    buff[*j] = ch;
    (*j)++;
  }

  for (int i = 0; i < spec->width - 1; i++) {
    buff[*j] = ' ';
    (*j)++;
  }

  if (!spec->flag_minus) {
    buff[*j] = ch;
    (*j)++;
  }
}

void handle_int(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                va_list* args) {
  long long num;

  if (spec->length == 'h') {
    num = (short)va_arg(*args, int);
  } else if (spec->length == 'l') {
    num = va_arg(*args, long);
  } else {
    num = va_arg(*args, int);
  }

  char num_char[64];

  s21_itoa(num, num_char);
  int len = strlen(num_char);
  if (num < 0) len++;

  if (spec->flag_space && spec->precision == 0 &&
      (!spec->flag_plus || num < 0)) {
    if (num >= 0) buff[(*j)++] = ' ';
  }

  if (spec->flag_minus) {
    if (spec->flag_plus && num >= 0) {
      buff[(*j)++] = '+';
    }
    enter_in_string(buff, spec, j, num, num_char);
  }

  int width = spec->width;

  if (len > spec->precision) {
    width -= len;
  } else {
    width -= spec->precision;
  }

  for (int i = 0; i < width; i++) {
    buff[(*j)++] = ' ';
  }

  // вывод если нет флага минус
  if (!spec->flag_minus) {
    if (spec->flag_plus && num >= 0) {
      buff[(*j)++] = '+';
    }
    enter_in_string(buff, spec, j, num, num_char);
  }
}

void handle_float(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                  va_list* args) {
  int len = 1;
  double num = va_arg(*args, double);

  if (num < 0) len++;

  int integer = (int)num;
  double rounded_fractional =
      (num - integer) * pow(10.0, (double)spec->precision) + 0.5;
  int fractional = (int)rounded_fractional;

  if (fractional < 0) fractional = -fractional;
  if (!spec->precision) spec->precision = 6;
  char integer_char[16];
  char fractional_char[16];

  s21_itoa(integer, integer_char);
  s21_itoa(fractional, fractional_char);
  if (fractional == 0) {
    for (int i = 0; i < spec->precision; i++) {
      fractional_char[i] = '0';
    }
  }

  if (spec->flag_minus) {
    if (spec->flag_plus && num >= 0) {
      buff[(*j)++] = '+';
    }
    enter_in_string(buff, spec, j, integer, integer_char);
    buff[(*j)++] = '.';
    enter_in_string(buff, spec, j, fractional, fractional_char);
  }

  len += strlen(integer_char) + strlen(fractional_char);

  if (spec->width && spec->width - len > 0) {
    for (int i = 0; i < spec->width - len; i++) {
      buff[(*j)++] = ' ';
    }
  }

  if (!spec->flag_minus) {
    if (spec->flag_plus && num >= 0) {
      buff[(*j)++] = '+';
    }
    enter_in_string(buff, spec, j, integer, integer_char);
    buff[(*j)++] = '.';
    enter_in_string(buff, spec, j, fractional, fractional_char);
  }
}

void handle_string(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                   va_list* args) {
  char* str = va_arg(*args, char*);

  int len = strlen(str);

  // precision — максимальное количество выводимых символов
  if (spec->precision >= 0 && spec->precision < len) {
    len = spec->precision;
  }

  int pad = 0;
  if (spec->width > len) {
    pad = spec->width - len;
  }

  if (!spec->flag_minus) {
    for (int i = 0; i < pad; i++) {
      buff[(*j)++] = ' ';
    }
  }

  for (int i = 0; str[i] != '\0' && i + 1 <= len; i++) {
    buff[(*j)++] = str[i];
  }

  if (spec->flag_minus) {
    for (int i = 0; i < pad; i++) {
      buff[(*j)++] = ' ';
    }
  }
}

void handle_unsigned_int(char* buff, s21_size_t* j,
                         struct s21_format_spec* spec, va_list* args) {
  unsigned int num = va_arg(*args, unsigned int);

  char num_char[64];

  s21_itoa(num, num_char);
  int len = strlen(num_char);
  if (num < 0) len++;

  // Флаг пробела
  if (spec->flag_space && spec->precision == 0 &&
      (!spec->flag_plus || num < 0)) {
    if (num >= 0) buff[(*j)++] = ' ';
  }

  if (spec->flag_minus) {
    if (spec->flag_plus && num >= 0) {
      buff[(*j)++] = '+';
    }
    enter_in_string(buff, spec, j, num, num_char);
  }

  // Ширина

  int width = spec->width;

  if (len > spec->precision) {
    width -= len;
  } else {
    width -= spec->precision;
  }

  for (int i = 0; i < width; i++) {
    buff[(*j)++] = ' ';
  }

  // вывод если нет флага минус
  if (!spec->flag_minus) {
    if (spec->flag_plus && num >= 0) {
      buff[(*j)++] = '+';
    }
    enter_in_string(buff, spec, j, num, num_char);
  }
}