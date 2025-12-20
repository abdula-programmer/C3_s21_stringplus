#include "s21_string.h"

// Ищет в строке str1 первое вхождение любого символа из строки str2. Возвращает
// указатель на этот символ в str1 или NULL, если ничего не найдено.

char* s21_strpbrk(const char* str1, const char* str2) {
  for (int i = 0; str1[i] != '\0'; i++)
    for (int y = 0; str2[y] != '\0'; y++)
      if (str1[i] == str2[y]) return (char*)(str1 + i);

  return NULL;
}