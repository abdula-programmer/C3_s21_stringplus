#include "s21_string.h"

// Ищет последнее вхождение символа c в строке str. Возвращает указатель на этот
// символ или NULL.

char* s21_strrchr(const char* str, int c) {
  size_t len = s21_strlen(str);
  for (int i = len; i >= 0; i--)
    if (str[i] == (char)c) return (char*)str + i;
  return NULL;
}