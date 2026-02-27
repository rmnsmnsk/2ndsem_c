#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clean_str(char* q)
{
    int j = 0;
    while (q[j] != '\n' && q[j] != '\0') {
        ++j;
    }
    return j;
}

char* copy_str(char* buffer, int j)
{
    char* copy = malloc(j + 1);
    for (int i = 0; i < j; i++) {
        copy[i] = buffer[i];
    }
    copy[j] = '\0';
    return copy;
}

char* get_word(char* q, int n)
{
    int comma_count = 0;
    char* word = malloc(strlen(q) + 1);
    int len = 0;

    if (n == 1) {
        int i = 0;
        while (i < strlen(q) && q[i] != ',') {
            word[len] = q[i];
            i++;
            len++;
        }
        word[len] = '\0';
        int y = clean_str(word);
        char* clean_word = copy_str(word, y);
        free(word);
        return clean_word;
    }

    for (int i = 0; i < strlen(q); i++) {
        if (q[i] == ',') {
            comma_count++;
        }
        if (comma_count == n - 1) {
            i++;
            while (q[i] != ',' && i < strlen(q)) {
                word[len] = q[i];
                i++;
                ++len;
            }
            word[len] = '\0';
            int y = clean_str(word);
            char* clean_word = copy_str(word, y);
            free(word);
            return clean_word;
        }
    }
    free(word);
    return NULL;
}

char* get_line(char symbol, int len, int* max_columns, int column)
{
    char* line = malloc(sizeof(char) * len);
    line[0] = '+';
    int j = 0;
    for (int u = 0; u < column; u++) {
        int size_word = max_columns[u];
        while (size_word > 0) {
            j++;
            line[j] = symbol;
            size_word -= 1;
        }
        j++;
        line[j] = '+';
    }
    return line;
}

int is_number(char* str)
{
    if (str == NULL) {
        return 0;
    }
    int i = 0;
    if (str[0] == '-') {
        i++;
    }

    int dots = 0;
    while (str[i] != '\0') {
        if (str[i] == '.') {
            dots += 1;
            if (dots > 1) {
                return 0;
            }
        } else if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}
