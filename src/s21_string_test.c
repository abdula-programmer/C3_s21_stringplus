#include "s21_string.h"

#include <check.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// --- s21_to_upper --- //
START_TEST(TestS21ToUpper_BasicLower) {
  const char* input = "hello world";
  char* result = s21_to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  for (size_t i = 0; i < strlen(input); i++)
    ck_assert_int_eq(result[i], toupper((unsigned char)input[i]));
  free(result);
}
END_TEST

START_TEST(TestS21ToUpper_MixedCase) {
  const char* input = "HeLlO wOrLd 123";
  char* result = s21_to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  for (size_t i = 0; i < strlen(input); i++)
    ck_assert_int_eq(result[i], toupper((unsigned char)input[i]));
  free(result);
}
END_TEST

START_TEST(TestS21ToUpper_Empty) {
  const char* input = "";
  char* result = s21_to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(TestS21ToUpper_Null) {
  char* result = s21_to_upper(NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

// --- s21_to_lower ---
START_TEST(TestS21ToLower_BasicUpper) {
  const char* input = "HELLO WORLD";
  char* result = s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  for (size_t i = 0; i < strlen(input); i++)
    ck_assert_int_eq(result[i], tolower((unsigned char)input[i]));
  free(result);
}
END_TEST

START_TEST(TestS21ToLower_MixedCase) {
  const char* input = "HeLlO wOrLd 123";
  char* result = s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  for (size_t i = 0; i < strlen(input); i++)
    ck_assert_int_eq(result[i], tolower((unsigned char)input[i]));
  free(result);
}
END_TEST

START_TEST(TestS21ToLower_Empty) {
  const char* input = "";
  char* result = s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(TestS21ToLower_Null) {
  char* result = s21_to_lower(NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

// --- s21_insert ---
START_TEST(TestS21Insert_InMiddle) {
  const char* src = "Hello World";
  const char* str = ", amazing";
  char* result = s21_insert(src, str, 5);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello, amazing World");
  free(result);
}
END_TEST

START_TEST(TestS21Insert_AtStart) {
  const char* src = "World";
  const char* str = "Hello ";
  char* result = s21_insert(src, str, 0);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(TestS21Insert_AtEnd) {
  const char* src = "Hello";
  const char* str = " World";
  char* result = s21_insert(src, str, strlen(src));
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(TestS21Insert_EmptySrc) {
  const char* src = "";
  const char* str = "Test";
  char* result = s21_insert(src, str, 0);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Test");
  free(result);
}
END_TEST

START_TEST(TestS21Insert_EmptyStr) {
  const char* src = "Test";
  const char* str = "";
  char* result = s21_insert(src, str, 2);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Test");
  free(result);
}
END_TEST

START_TEST(TestS21Insert_InvalidIndex) {
  char* result = s21_insert("Test", "Fail", 100);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(TestS21Insert_NullSrc) {
  char* result = s21_insert(NULL, "Test", 0);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(TestS21Insert_NullStr) {
  char* result = s21_insert("Test", NULL, 0);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

// --- s21_trim ---
START_TEST(TestS21Trim_DefaultWhitespaceFull) {
  const char* src = " \t\nHello World \r\n ";
  char* result = s21_trim(src, NULL);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_int_eq(isspace(result[0]), 0);
  ck_assert_int_eq(isspace(result[strlen(result) - 1]), 0);
  free(result);
}
END_TEST

START_TEST(TestS21Trim_DefaultWhitespaceNone) {
  const char* src = "Hello World";
  char* result = s21_trim(src, NULL);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(TestS21Trim_CustomCharsBothSides) {
  const char* src = "-+_Hello World_+-";
  const char* trim_chars = "-+_";
  char* result = s21_trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_ptr_eq(strchr(trim_chars, result[0]), NULL);
  ck_assert_ptr_eq(strchr(trim_chars, result[strlen(result) - 1]), NULL);
  free(result);
}
END_TEST

START_TEST(TestS21Trim_StringIsOnlyTrimChars) {
  const char* src = "+++++";
  const char* trim_chars = "+";
  char* result = s21_trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(TestS21Trim_NullSrc) {
  char* result = s21_trim(NULL, " ");
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite* s21_string_suite(void) {
  Suite* suite = suite_create("S21_String");
  TCase* tcase_core = tcase_create("Core");

  // --- s21_to_upper ---
  tcase_add_test(tcase_core, TestS21ToUpper_BasicLower);
  tcase_add_test(tcase_core, TestS21ToUpper_MixedCase);
  tcase_add_test(tcase_core, TestS21ToUpper_Empty);
  tcase_add_test(tcase_core, TestS21ToUpper_Null);

  // --- s21_to_lower ---
  tcase_add_test(tcase_core, TestS21ToLower_BasicUpper);
  tcase_add_test(tcase_core, TestS21ToLower_MixedCase);
  tcase_add_test(tcase_core, TestS21ToLower_Empty);
  tcase_add_test(tcase_core, TestS21ToLower_Null);

  // --- s21_insert ---
  tcase_add_test(tcase_core, TestS21Insert_InMiddle);
  tcase_add_test(tcase_core, TestS21Insert_AtStart);
  tcase_add_test(tcase_core, TestS21Insert_AtEnd);
  tcase_add_test(tcase_core, TestS21Insert_EmptySrc);
  tcase_add_test(tcase_core, TestS21Insert_EmptyStr);
  tcase_add_test(tcase_core, TestS21Insert_InvalidIndex);
  tcase_add_test(tcase_core, TestS21Insert_NullSrc);
  tcase_add_test(tcase_core, TestS21Insert_NullStr);

  // --- s21_trim ---
  tcase_add_test(tcase_core, TestS21Trim_DefaultWhitespaceFull);
  tcase_add_test(tcase_core, TestS21Trim_DefaultWhitespaceNone);
  tcase_add_test(tcase_core, TestS21Trim_CustomCharsBothSides);
  tcase_add_test(tcase_core, TestS21Trim_StringIsOnlyTrimChars);
  tcase_add_test(tcase_core, TestS21Trim_NullSrc);

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
