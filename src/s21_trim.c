#include "s21_string.h"

void* s21_trim(const char* src, const char* trim_chars) {
  if (src == S21_NULL) {
    return S21_NULL;
  }
  const char* default_trim = " \t\n\v\f\r";
  if (trim_chars == S21_NULL) {
    trim_chars = default_trim;
  }
  s21_size_t src_len = 0;
  for (; src[src_len] != '\0'; src_len++);
  s21_size_t trim_len = 0;
  for (; trim_chars[trim_len] != '\0'; trim_len++);

  s21_size_t start_index = 0;
  for (; start_index < src_len;) {
    s21_size_t coincidence = 0;
    for (int i = 0; i < (int)trim_len; i++) {
      if (src[start_index] == trim_chars[i]) {
        coincidence++;
      }
    }
    if (coincidence == 0) {
      break;
    }
    start_index++;
  }

  s21_size_t end_index = src_len - 1;
  for (int s = src_len - 1; s >= 0; s--) {
    s21_size_t coincidence = 0;
    for (int i = 0; i < (int)trim_len; i++) {
      if (src[s] == trim_chars[i]) {
        coincidence++;
      }
    }
    if (coincidence == 0) {
      end_index = s;
      break;
    }
  }

  s21_size_t index_arr = 0;
  char* dynamic_array = S21_NULL;
  if (start_index > end_index) {
    dynamic_array = malloc(sizeof(char));
  } else {
    dynamic_array = malloc((end_index - start_index + 1) * sizeof(char));
  }
  if (start_index <= end_index) {
    for (int i = (int)start_index; i <= (int)end_index; i++) {
      dynamic_array[index_arr++] = src[i];
    }
  }
  dynamic_array[index_arr] = '\0';
  return dynamic_array;
}
