#include "s21_string.h"

void* s21_to_upper(const char* str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }

  s21_size_t size_of_block = (len + 1) * sizeof(char);
  char* dynamic_array = malloc(size_of_block);

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      dynamic_array[i] = (str[i] - 32);
    } else {
      dynamic_array[i] = str[i];
    }
  }
  dynamic_array[len] = '\0';
  return dynamic_array;
}
