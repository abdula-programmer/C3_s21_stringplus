#include "s21_string.h"

// Возвращает длину строки str

size_t s21_strlen(const char* str) {
  size_t len = 0;
  while (srt[len] != '\0') len++;
  return len;
}