#include "s21_string.h"

#include <check.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// --- s21_memchr --- //
START_TEST(TestS21Memchr_Found) {
  const char* input = "hello world";
  int c = 'o';
  size_t n = strlen(input);
  void* result = s21_memchr(input, c, n);
  void* expected = memchr(input, c, n);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(TestS21Memchr_NotFound) {
  const char* input = "hello world";
  int c = 'z';
  size_t n = strlen(input);
  void* result = s21_memchr(input, c, n);
  void* expected = memchr(input, c, n);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(TestS21Memchr_FirstOccurrence) {
  const char* input = "hello world";
  int c = 'o';
  size_t n = strlen(input);
  void* result = s21_memchr(input, c, n);
  void* expected = memchr(input, c, n);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_eq(result, (void*)(input + 4));
}
END_TEST

START_TEST(TestS21Memchr_LimitedSearch) {
  const char* input = "hello world";
  int c = 'w';
  size_t n = 5;
  void* result = s21_memchr(input, c, n);
  void* expected = memchr(input, c, n);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(TestS21Memchr_EmptyString) {
  const char* input = "";
  int c = 'o';
  size_t n = 0;
  void* result = s21_memchr(input, c, n);
  void* expected = memchr(input, c, n);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(TestS21Memchr_ZeroByte) {
  const char input[] = "hello\0world";
  int c = '\0';
  size_t n = 11;
  void* result = s21_memchr(input, c, n);
  void* expected = memchr(input, c, n);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

// --- s21_memcmp --- //
START_TEST(TestS21Memcmp_Equal) {
  const char* str1 = "hello world";
  const char* str2 = "hello world";
  size_t n = strlen(str1);
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(TestS21Memcmp_FirstGreater) {
  const char* str1 = "hello world";
  const char* str2 = "hello World";
  size_t n = strlen(str1);
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result > 0, expected > 0);
}
END_TEST

START_TEST(TestS21Memcmp_SecondGreater) {
  const char* str1 = "hello World";
  const char* str2 = "hello world";
  size_t n = strlen(str1);
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result < 0, expected < 0);
}
END_TEST

START_TEST(TestS21Memcmp_PartialEqual) {
  const char* str1 = "hello world";
  const char* str2 = "hello kitty";
  size_t n = 6;
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(TestS21Memcmp_DifferentLength) {
  const char* str1 = "abc";
  const char* str2 = "abcd";
  size_t n = 3;
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(TestS21Memcmp_EmptyStrings) {
  const char* str1 = "";
  const char* str2 = "";
  size_t n = 0;
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(TestS21Memcmp_WithZeroByte) {
  const char* str1 = "hello\0world";
  const char* str2 = "hello\0kitty";
  size_t n = 11;
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result > 0, expected > 0);
}
END_TEST

// --- s21_memcpy --- //
START_TEST(TestS21Memcpy_BasicCopy) {
  const char* src = "hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 11;
  
  void* result = s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  
  ck_assert_ptr_eq(result, dest1);
  ck_assert_mem_eq(dest1, dest2, n);
  ck_assert_str_eq(dest1, "hello world");
}
END_TEST

START_TEST(TestS21Memcpy_PartialCopy) {
  const char* src = "hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 5;
  
  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  
  ck_assert_mem_eq(dest1, dest2, n);
  ck_assert_mem_eq(dest1, "hello", n);
}
END_TEST

START_TEST(TestS21Memcpy_WithZeroByte) {
  const char src[] = "hello\0world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 11;
  
  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  
  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(TestS21Memcpy_ZeroBytes) {
  const char* src = "hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 0;
  
  void* result = s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  
  ck_assert_ptr_eq(result, dest1);
  ck_assert_mem_eq(dest1, dest2, 20);
}
END_TEST

START_TEST(TestS21Memcpy_BinaryData) {
  unsigned char src[] = {0x01, 0x02, 0x03, 0xFF, 0x00, 0xAB};
  unsigned char dest1[6] = {0};
  unsigned char dest2[6] = {0};
  size_t n = 6;
  
  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  
  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

// --- s21_memset --- //
START_TEST(TestS21Memset_BasicFill) {
  char buffer1[20] = "hello world";
  char buffer2[20] = "hello world";
  int c = 'X';
  size_t n = 5;
  
  void* result = s21_memset(buffer1, c, n);
  memset(buffer2, c, n);
  
  ck_assert_ptr_eq(result, buffer1);
  ck_assert_mem_eq(buffer1, buffer2, 20);
  ck_assert_str_eq(buffer1, "XXXXX world");
}
END_TEST

START_TEST(TestS21Memset_ZeroFill) {
  char buffer1[20] = "hello world";
  char buffer2[20] = "hello world";
  int c = 0;
  size_t n = 11;
  
  s21_memset(buffer1, c, n);
  memset(buffer2, c, n);
  
  ck_assert_mem_eq(buffer1, buffer2, 20);
}
END_TEST

START_TEST(TestS21Memset_FullBuffer) {
  char buffer1[10];
  char buffer2[10];
  int c = 'A';
  size_t n = 10;
  
  s21_memset(buffer1, c, n);
  memset(buffer2, c, n);
  
  ck_assert_mem_eq(buffer1, buffer2, n);
}
END_TEST

START_TEST(TestS21Memset_ZeroBytes) {
  char buffer1[10] = "test";
  char buffer2[10] = "test";
  int c = 'X';
  size_t n = 0;
  
  void* result = s21_memset(buffer1, c, n);
  memset(buffer2, c, n);
  
  ck_assert_ptr_eq(result, buffer1);
  ck_assert_mem_eq(buffer1, buffer2, 10);
  ck_assert_str_eq(buffer1, "test");
}
END_TEST

START_TEST(TestS21Memset_BinaryValue) {
  unsigned char buffer1[10];
  unsigned char buffer2[10];
  int c = 0xFF;
  size_t n = 10;
  
  s21_memset(buffer1, c, n);
  memset(buffer2, c, n);
  
  ck_assert_mem_eq(buffer1, buffer2, n);
  for (size_t i = 0; i < n; i++) {
    ck_assert_int_eq(buffer1[i], 0xFF);
  }
}
END_TEST

// --- s21_strncat --- //
START_TEST(TestS21Strncat_BasicConcat) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char* src = " World";
  size_t n = 6;
  
  char* result = s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  
  ck_assert_ptr_eq(result, dest1);
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest1, "Hello World");
}
END_TEST

START_TEST(TestS21Strncat_PartialConcat) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char* src = " World";
  size_t n = 3;
  
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest1, "Hello Wo");
}
END_TEST

START_TEST(TestS21Strncat_EmptySource) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char* src = "";
  size_t n = 10;
  
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest1, "Hello");
}
END_TEST

START_TEST(TestS21Strncat_EmptyDest) {
  char dest1[50] = "";
  char dest2[50] = "";
  const char* src = "World";
  size_t n = 5;
  
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest1, "World");
}
END_TEST

START_TEST(TestS21Strncat_ZeroN) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char* src = " World";
  size_t n = 0;
  
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest1, "Hello");
}
END_TEST

START_TEST(TestS21Strncat_MoreThanSource) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char* src = " Hi";
  size_t n = 100;
  
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest1, "Hello Hi");
}
END_TEST

Suite* s21_string_suite(void) {
  Suite* suite = suite_create("S21_String");
  TCase* tcase_core = tcase_create("Core");

  // --- s21_memchr ---
  tcase_add_test(tcase_core, TestS21Memchr_Found);
  tcase_add_test(tcase_core, TestS21Memchr_NotFound);
  tcase_add_test(tcase_core, TestS21Memchr_FirstOccurrence);
  tcase_add_test(tcase_core, TestS21Memchr_LimitedSearch);
  tcase_add_test(tcase_core, TestS21Memchr_EmptyString);
  tcase_add_test(tcase_core, TestS21Memchr_ZeroByte);

  // --- s21_memcmp ---
  tcase_add_test(tcase_core, TestS21Memcmp_Equal);
  tcase_add_test(tcase_core, TestS21Memcmp_FirstGreater);
  tcase_add_test(tcase_core, TestS21Memcmp_SecondGreater);
  tcase_add_test(tcase_core, TestS21Memcmp_PartialEqual);
  tcase_add_test(tcase_core, TestS21Memcmp_DifferentLength);
  tcase_add_test(tcase_core, TestS21Memcmp_EmptyStrings);
  tcase_add_test(tcase_core, TestS21Memcmp_WithZeroByte);

  // --- s21_memcpy ---
  tcase_add_test(tcase_core, TestS21Memcpy_BasicCopy);
  tcase_add_test(tcase_core, TestS21Memcpy_PartialCopy);
  tcase_add_test(tcase_core, TestS21Memcpy_WithZeroByte);
  tcase_add_test(tcase_core, TestS21Memcpy_ZeroBytes);
  tcase_add_test(tcase_core, TestS21Memcpy_BinaryData);

  // --- s21_memset ---
  tcase_add_test(tcase_core, TestS21Memset_BasicFill);
  tcase_add_test(tcase_core, TestS21Memset_ZeroFill);
  tcase_add_test(tcase_core, TestS21Memset_FullBuffer);
  tcase_add_test(tcase_core, TestS21Memset_ZeroBytes);
  tcase_add_test(tcase_core, TestS21Memset_BinaryValue);

  // --- s21_strncat ---
  tcase_add_test(tcase_core, TestS21Strncat_BasicConcat);
  tcase_add_test(tcase_core, TestS21Strncat_PartialConcat);
  tcase_add_test(tcase_core, TestS21Strncat_EmptySource);
  tcase_add_test(tcase_core, TestS21Strncat_EmptyDest);
  tcase_add_test(tcase_core, TestS21Strncat_ZeroN);
  tcase_add_test(tcase_core, TestS21Strncat_MoreThanSource);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite* suite = s21_string_suite();
  SRunner* runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int failed_tests = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed_tests == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
