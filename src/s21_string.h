#ifndef S21_STRING_H
#define S21_STRING_H

// #include "stdlib.h"
#include <stdarg.h>

#include "stdio.h"

// #define _POSIX_C_SOURCE 201710L;

#define S21_NULL ((void*)0)

typedef unsigned long s21_size_t;

// void *memchr(const void *str, int c, size_t n)
// int memcmp(const void *str1, const void *str2, size_t n)
// void *memcpy(void *dest, const void *src, size_t n)
// void *memset(void *str, int c, size_t n)
// char *strncat(char *dest, const char *src, size_t n)
// char* strchr(const char* str, int c);
// int strncmp(const char* str1, const char* str2, s21_size_t n);
// char* strncpy(char* dest, const char* src, s21_size_t n);
// s21_size_t strcspn(const char* str1, const char* str2);
// char* strerror(int errnum);
// s21_size_t strlen(const char* str);
// char* strpbrk(const char* str1, const char* str2);
// char* strrchr(const char* str, int c);
// char* strstr(const char* haystack, const char* needle);
// char* strtok(char* str, const char* delim);

// // Дополнительные функции

// void* to_upper(const char* str);
// void* to_lower(const char* str);

// void* insert(const char* src, const char* str, s21_size_t start_index);
// void* trim(const char* src, const char* trim_chars)

// s21_sprintf declaration
struct s21_format_spec {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_zero;
  int flag_hash;
  int width;
  int precision;
  char length;
  char specifier;
};

int s21_sprintf(char* buff, const char* format, ...);
void s21_sprintf_parser(const char* format, s21_size_t* i,
                        struct s21_format_spec* spec);
void choose_spacifer(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                     va_list* args);
void handle_char(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                 va_list* args);

void handle_int(char* buff, s21_size_t* j, struct s21_format_spec* spec,
                va_list* args);
// void handle_float(char* buff, s21_size_t* j, struct s21_format_spec* spec,
//                   va_list* args);
// void handle_string(char* buff, s21_size_t* j, struct s21_format_spec* spec,
//                    va_list* args);
// void handle_unsigned_int(char* buff, s21_size_t* j,
//                          struct s21_format_spec* spec, va_list* args);

void reverse(char* str, int length);
char* s21_itoa(int num, char* str, int base);
#endif
