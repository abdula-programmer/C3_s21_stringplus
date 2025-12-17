#include "s21_string.h"

// Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *end = dest;
  while (*end != '\0') {
    end++;
  }
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    end[i] = src[i];
  }
  end[i] = '\0';
  return dest;
}
