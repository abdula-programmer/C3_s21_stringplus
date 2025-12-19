#ifndef S21_STRING_H
#define S21_STRING_H

#define s21_size_t unsigned long long
#define s21_NULL (void*)0

#include <stdio.h>

char* s21_strchr(const char* str, int c);
int s21_strncmp(const char* str1, const char* str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
s21_size_t s21_strcspn(const char *str1, const char *str2);

#endif