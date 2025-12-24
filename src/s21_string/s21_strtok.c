#include "s21_string.h"

// Разбивает строку на части (токены), используя указанные разделители.

char *s21_strtok(char *str, const char *delim) {
    static char *next_token = NULL;
    char *token_start;
    
    if (str != NULL) {
        next_token = str;
    }
    
    if (next_token == NULL || *next_token == '\0') {
        return NULL;
    }
    
    while (*next_token != '\0') {
        const char *d = delim;
        int is_delim = 0;
        
        while (*d != '\0') {
            if (*next_token == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        
        if (!is_delim) {
            break;
        }
        next_token++;
    }

    if (*next_token == '\0') {
        next_token = NULL;
        return NULL;
    }
    
    token_start = next_token;
    while (*next_token != '\0') {
        const char *d = delim;
        int is_delim = 0;
        while (*d != '\0') {
            if (*next_token == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        
        if (is_delim) {
            *next_token = '\0';
            next_token++;
            return token_start;
        }
        
        next_token++;
    }
    
    next_token = NULL;
    return token_start;
}
