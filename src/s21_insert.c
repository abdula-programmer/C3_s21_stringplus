#include "s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t num_elements = 0;
  for (; src[num_elements] != '\0'; num_elements++);
  if (num_elements < start_index) {
    return S21_NULL;
  }

  s21_size_t num_elements_2 = 0;
  for (; str[num_elements_2] != '\0'; num_elements_2++);

  char* dynamic_array =
      malloc(((num_elements_2 + num_elements) + 1) * sizeof(char));

  s21_size_t sourse_size = 0;
  for (; sourse_size < start_index; sourse_size++) {
    dynamic_array[sourse_size] = src[sourse_size];
  }
  s21_size_t long_sting = 0;
  for (; long_sting < num_elements_2; long_sting++) {
    dynamic_array[sourse_size + long_sting] = str[long_sting];
  }
  for (; sourse_size < num_elements; sourse_size++) {
    dynamic_array[sourse_size + long_sting] = src[sourse_size];
  }
  dynamic_array[num_elements_2 + num_elements] = '\0';
  return dynamic_array;
}
