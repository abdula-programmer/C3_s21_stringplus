#include "s21_string.h"

//Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = (const unsigned char *)str;
  unsigned char target = (unsigned char)c;
  void *res = S21_NULL;
  for (s21_size_t i = 0; i < n && res == S21_NULL; i++) {
    if (p[i] == target) res = (void *)(p + i);
  }
  return res;
}
