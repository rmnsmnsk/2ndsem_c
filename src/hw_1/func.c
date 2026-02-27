#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cleanStr(const char* q)
{
    int j = 0;
    while (q[j] != '\n' && q[j] != '\0') {
        ++j;
    }
    return j;
}

char* copyStr(const char* buffer, int j)
{
    char* copy = malloc(j + 1);
    for (int i = 0; i < j; i++) {
        copy[i] = buffer[i];
    }
    copy[j] = '\0';
    return copy;
}

char* getWord(const char* q, int n)
{
    int commaCount = 0;
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
        int y = cleanStr(word);
        char* cleanWord = copyStr(word, y);
        free(word);
        return cleanWord;
    }

    for (int i = 0; i < strlen(q); i++) {
        if (q[i] == ',') {
            commaCount++;
        }
        if (commaCount == n - 1) {
            i++;
            while (q[i] != ',' && i < strlen(q)) {
                word[len] = q[i];
                i++;
                ++len;
            }
            word[len] = '\0';
            int y = cleanStr(word);
            char* cleanWord = copyStr(word, y);
            free(word);
            return cleanWord;
        }
    }
    free(word);
    return NULL;
}

char* getLine(char symbol, int len, const int* maxColumns, int column)
{
    char* line = malloc(sizeof(char) * len);
    line[0] = '+';
    int j = 0;
    for (int u = 0; u < column; u++) {
        int sizeWord = maxColumns[u];
        while (sizeWord > 0) {
            j++;
            line[j] = symbol;
            sizeWord -= 1;
        }
        j++;
        line[j] = '+';
    }
    return line;
}

int isNumber(const char* str)
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
