// Сравнивает не более первых n байтов str1 и str2. 

#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int result = 0;
    int finished = 0;
    
    if (n > 0) {
        while (n > 0 && !finished) {
            unsigned char c1 = *str1;
            unsigned char c2 = *str2;
            
            if (c1 != c2) {
                result = c1 - c2;
                finished = 1;
            } else if (c1 == '\0') {
                result = 0;
                finished = 1;
            } else {
                str1++;
                str2++;
                n--;
            }
        }
    }
    
    return result;
}