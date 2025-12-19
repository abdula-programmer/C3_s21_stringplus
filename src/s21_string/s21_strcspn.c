// Вычисляет длину начального сегмента str1, который полностью состоит из символов, 
// не входящих в str2.

#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t count = 0;
    int found = 0;

    while (*str1 != '\0' && !found) {
        const char *check = str2;
        found = 0;
        
        while (*check != '\0' && !found) {
            if (*str1 == *check) {
                found = 1;
            } else {
                check++;
            }
        }
        
        if (!found) {
            str1++;
            count++;
        }
    }
    
    return count;
}