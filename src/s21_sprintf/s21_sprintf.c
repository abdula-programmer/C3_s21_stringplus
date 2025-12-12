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
    // case 'f':
    //   handle_float(buff, j, spec, args);
    //   break;
    // case 's':
    //   handle_string(buff, j, spec, args);
    //   break;
    // case 'u':
    //   handle_unsigned_int(buff, j, spec, args);
    //   break;
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
  int num = va_arg(*args, int);
  char num_char[16];

  s21_itoa(num, num_char, 10);
  int len = strlen(num_char);

  // Флаг пробела
  if (spec->flag_space) {
    if (num >= 0) buff[(*j)++] = ' ';
  }

  // Флаг минус
  if (spec->flag_minus) {
    for (int i = 0; num_char[i] != '\0'; i++) {
      buff[(*j)++] = num_char[i];
    }
  }

  // Ширина
  for (int i = 0; i < spec->width - len; i++) {
    buff[(*j)++] = ' ';
  }

  // вывод если нет флага минус
  if (!spec->flag_minus) {
    for (int i = 0; num_char[i] != '\0'; i++) {
      buff[(*j)++] = num_char[i];
    }
  }
}
// void handle_float(char* buff, s21_size_t* j, struct s21_format_spec* spec,
//                   va_list* args) {
//   printf("%s", buff);

//   float ch = va_arg(*args, float);
//   printf("\n\n%f", ch);
// }

// void handle_string(char* buff, s21_size_t* j, struct s21_format_spec* spec,
//                    va_list* args) {
//   printf("%s", buff);

//   char* ch = va_arg(*args, char*);
//   printf("\n\n%s", ch);
// }

// void handle_unsigned_int(char* buff, s21_size_t* j,
//                          struct s21_format_spec* spec, va_list* args) {
//   printf("%s", buff);
//   printf("%i", j);
//   unsigned int ch = va_arg(*args, unsigned int);
//   printf("\n\n%c", ch);
// }