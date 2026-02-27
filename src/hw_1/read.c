#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* file = fopen("files/input3.csv", "r");
    if (file == NULL) {
        printf("File is not found\n");
        return -1;
    }

    char** data = NULL;
    char buffer[100];
    int column = 0;
    int rows = 0;
    int temp = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {

        rows++;

        int k = cleanStr(buffer);

        char* copy = copyStr(buffer, k);

        data = realloc(data, rows * sizeof(char*));
        if (data == NULL) {
            printf("Memory allocation failed\n");
            return -1;
        }
        data[rows - 1] = copy;

        for (int i = 0; i < k; i++) {
            if (buffer[i] == ',') {
                temp++;
            }
        }
        if (column < temp) {
            column = temp;
        }
        temp = 1;
    }

    if (rows == 0) {
        printf("File is empty\n");
        fclose(file);
        return 0;
    }

    int* maxColumns = calloc(column, sizeof(int));
    if (maxColumns == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    for (int u = 0; u < column; u++) {
        for (int t = 0; t < rows; t++) {
            char* newWord = getWord(data[t], u + 1);
            if (newWord != NULL) {
                int lenWord = strlen(newWord);
                if (lenWord > maxColumns[u]) {
                    maxColumns[u] = lenWord;
                }
                free(newWord);
            }
        }
    }

    int width = 0;
    for (int g = 0; g < column; g++) {
        width += maxColumns[g];
    }
    width += (column + 1);

    FILE* out = fopen("files/output.txt", "w");
    if (out == NULL) {
        printf("Output file error\n");
        free(data);
        free(maxColumns);
        fclose(file);
        return -1;
    }

    char* line = getLine('=', width, maxColumns, column);
    if (line != NULL) {
        fprintf(out, "%s\n", line);
    }

    fprintf(out, "|");
    for (int y = 0; y < column; y++) {
        char* word = getWord(data[0], y + 1);
        if (word != NULL) {
            fprintf(out, "%-*s|", maxColumns[y], word);
            free(word);
        }
    }
    fprintf(out, "\n");

    if (line != NULL) {
        fprintf(out, "%s", line);
        free(line);
    }

    char* line2 = getLine('-', width, maxColumns, column);
    fprintf(out, "\n");

    for (int t = 1; t < rows; t++) {
        fprintf(out, "|");
        for (int r = 0; r < column; r++) {
            char* word = getWord(data[t], r + 1);
            if (word != NULL) {
                if (isNumber(word)) {
                    fprintf(out, "%*s|", maxColumns[r], word);
                } else {
                    fprintf(out, "%-*s|", maxColumns[r], word);
                }
                free(word);
            } else {
                fprintf(out, "%*s|", maxColumns[r], "");
            }
        }
        fprintf(out, "\n");
        fprintf(out, "%s\n", line2);
    }

    free(line2);
    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);
    free(maxColumns);
    fclose(file);

    return 0;
}