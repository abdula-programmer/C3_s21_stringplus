// Копирует до n символов из строки, на которую указывает src, в dest. 

#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char *result = dest;
    int copying = 1;
    
    if (dest != NULL && src != NULL && n > 0) {
        s21_size_t i = 0;
        
        while (i < n) {
            if (copying && src[i] != '\0') {
                dest[i] = src[i];
            } else {
                copying = 0;
                dest[i] = '\0';
            }
            i++;
        }
    }
    
    return result;
}