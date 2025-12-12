#include "s21_string.h"

char *strncat(char *dest, const char *src, s21_size_t n) {
  char *end = dest + strlen(dest);
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    end[i] = src[i];
  }
  end[i] = '\0';
  return dest;
}
