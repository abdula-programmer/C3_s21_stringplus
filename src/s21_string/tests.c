#include <check.h>
#include <string.h>
#include "s21_string.h"


START_TEST(s21_strchr_test) {
  const char* str = "Abcdefg";
  const char* str2 = "Test string";
  const char* str3 = "";
  
  int c1 = 'd';
  int c2 = 'A';
  int c3 = 'g';
  int c4 = 'z';
  int c5 = '\0';
  int c6 = 's';
  int c7 = 'a';
  int c8 = '\0';
  
  ck_assert_ptr_eq(s21_strchr(str, c1), strchr(str, c1));
  ck_assert_ptr_eq(s21_strchr(str, c2), strchr(str, c2));
  ck_assert_ptr_eq(s21_strchr(str, c3), strchr(str, c3));
  ck_assert_ptr_eq(s21_strchr(str, c4), strchr(str, c4));
  ck_assert_ptr_eq(s21_strchr(str, c5), strchr(str, c5));
  ck_assert_ptr_eq(s21_strchr(str2, c6), strchr(str2, c6));
  ck_assert_ptr_eq(s21_strchr(str3, c7), strchr(str3, c7));
  ck_assert_ptr_eq(s21_strchr(str3, c8), strchr(str3, c8));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char test1[] = "123456";
  char test2[] = "12345";
  char test3[] = "123";
  char test4[] = "1234567890";
  char test5[] = "0/";
  char test6[] = "%%\\#";
  char test7[] = "234567";
  char test8[] = "1234567890";
  ck_assert_uint_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(s21_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_uint_eq(s21_strcspn(test3, test5), strcspn(test3, test5));
  ck_assert_uint_eq(s21_strcspn(test3, test6), strcspn(test3, test6));
  ck_assert_uint_eq(s21_strcspn(test3, test7), strcspn(test3, test7));
  ck_assert_uint_eq(s21_strcspn(test4, test8), strcspn(test4, test8));
  ck_assert_uint_eq(s21_strcspn(test2, test7), strcspn(test2, test7));
}
END_TEST

START_TEST(s21_strncpy_test) {
char str1[] = "ABC";
char dest1[10] = "";
char str2[] = "test of string";
char dest2[15] = "";
char str3[] = "test\0";
char dest3[5] = "";
ck_assert_str_eq(s21_strncpy(dest1, str1, 5), strncpy(dest1, str1, 5));
ck_assert_str_eq(s21_strncpy(dest2, str2, 5), strncpy(dest2, str2, 5));
ck_assert_str_eq(s21_strncpy(dest3, str3, 4), strncpy(dest3, str3, 4));
}
END_TEST

START_TEST(s21_strncmp_test) {
  char str1[] = "hella 1";
  char str2[] = "hello 3";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5) < 0, strncmp(str1, str2, 5) < 0);
  ck_assert_int_eq(s21_strncmp(str1, str2, 3) == 0, strncmp(str1, str2, 3) == 0);
}
END_TEST

START_TEST(s21_strerror_test) {
  // Тест 1: Базовые известные ошибки
  int test_errors[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (size_t i = 0; i < sizeof(test_errors) / sizeof(test_errors[0]); i++) {
    const char* s21_result = s21_strerror(test_errors[i]);
    ck_assert_ptr_nonnull(s21_result);
    ck_assert_int_ne(strlen(s21_result), 0);
  }
  
  // Тест 2: Крайние значения
  #ifdef __APPLE__
    const int max_err = 106;
  #elif __linux__
    const int max_err = 133;
  #endif

  // Минимальная ошибка (0)
  const char* min_result = s21_strerror(0);
  ck_assert_ptr_nonnull(min_result);
  ck_assert_int_ne(strlen(min_result), 0);

  // Максимальная известная ошибка
  const char* max_result = s21_strerror(max_err);
  ck_assert_ptr_nonnull(max_result);
  ck_assert_int_ne(strlen(max_result), 0);

  // Одна перед максимальной
  if (max_err > 0) {
    const char* before_max = s21_strerror(max_err - 1);
    ck_assert_ptr_nonnull(before_max);
    ck_assert_int_ne(strlen(before_max), 0);
  }
  
  // Тест 3: Последовательные вызовы
  const char* result1 = s21_strerror(1);
  const char* result2 = s21_strerror(2);
  const char* result3 = s21_strerror(3);
  const char* result_back_to_1 = s21_strerror(1);

  ck_assert_ptr_nonnull(result1);
  ck_assert_ptr_nonnull(result2);
  ck_assert_ptr_nonnull(result3);
  ck_assert_ptr_nonnull(result_back_to_1);

  ck_assert_int_ne(strlen(result1), 0);
  ck_assert_int_ne(strlen(result2), 0);
  ck_assert_int_ne(strlen(result3), 0);
  ck_assert_int_ne(strlen(result_back_to_1), 0);

  ck_assert_ptr_eq(result1, result_back_to_1);
  
  // Тест 4: Проверка диапазона ошибок
  // Тестируем диапазон от -10 до 150
  for (int errnum = -10; errnum <= 150; errnum++) {
    const char* result = s21_strerror(errnum);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_ne(strlen(result), 0);
  }
}
END_TEST


int main(void) {
  Suite *s1 = suite_create("s21_string");
  TCase *tc1_1 = tcase_create("s21_string");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, s21_strchr_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strerror_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}