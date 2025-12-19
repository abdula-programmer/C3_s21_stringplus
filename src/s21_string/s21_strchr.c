// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке,
// на которую указывает аргумент str.

#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;

  if (str != s21_NULL) {
    int i = 0;
    while (str[i] != '\0' && str[i] != c)
      i++;
    if (str[i] == c)
      result = (char *)str + i;
  }

  return result;
}