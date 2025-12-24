#include "s21_string.h"

// Ищет первое вхождение подстроки needle в строке haystack. Возвращает
// указатель на начало найденной подстроки или NULL

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = NULL;
  size_t len1 = s21_strlen(haystack), len2 = s21_strlen(needle);
  if (!(haystack == NULL || needle == NULL))
    for (int i = 0; haystack[i] != '\0' && result == NULL; i++) {
      if (haystack[i] == needle[0] && len1 - i >= len2) {
        int flag = 1;
        for (int y = 1; needle[y] != '\0' && result == NULL; y++)
          if (haystack[i + y] != needle[y]) flag = 0;
        if (flag) result = (char*)haystack + i;
      }
    }

  if (haystack == NULL || needle == NULL) result = NULL;
  if (needle[0] == '\0') result = (char*)haystack;
  return result;
}
