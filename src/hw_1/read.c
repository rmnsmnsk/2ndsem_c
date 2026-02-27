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

    char** data = NULL; // массив указателей
    char buffer[100];
    int column = 0;
    int rows = 0;
    int temp = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {

        rows++;

        int k = clean_str(buffer);

        char* copy = copy_str(buffer, k); // копирую т.к переменная buffer постоянно меняется

        data = realloc(data, rows * sizeof(char*));
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

    int* max_columns = calloc(column, sizeof(int));

    for (int u = 0; u < column; u++) { // цикл для max_columns
        for (int t = 0; t < rows; t++) {
            char* new_word = get_word(data[t], u + 1);
            if (new_word != NULL) {
                int len_word = strlen(new_word);
                if (len_word > max_columns[u]) {
                    max_columns[u] = len_word;
                }
                free(new_word);
            }
        }
    }
    int width = 0;
    for (int g = 0; g < column; g++) {
        width += max_columns[g];
    }
    width += (column + 1);

    // запись в файл
    FILE* out = fopen("files/output.txt", "w");
    char* line = get_line('=', width, max_columns, column);

    if (out == NULL) {
        return -1;
    }
    if (line != NULL) { // верхняя линия
        fprintf(out, "%s\n", line);
    }
    fprintf(out, "%s", "|"); // заголовок

    for (int y = 0; y < column; y++) {
        char* word = get_word(data[0], y + 1);
        if (word != NULL) {
            fprintf(out, "%-*s|", max_columns[y], word);
            free(word);
        }
    }
    fprintf(out, "\n");
    // после заголвока
    if (line != NULL) {
        fprintf(out, "%s", line);
        free(line);
    }
    char* line_2 = get_line('-', width, max_columns, column);
    // уже остальные данные
    fprintf(out, "\n");
    for (int t = 1; t < rows; ++t) {
        fprintf(out, "|");
        for (int r = 0; r < column; r++) {
            char* word = get_word(data[t], r + 1);
            if (word != NULL) {
                if (is_number(word)) {
                    fprintf(out, "%*s|", max_columns[r], word);
                    free(word);
                } else {
                    fprintf(out, "%-*s|", max_columns[r], word);
                    free(word);
                }
            } else {
                fprintf(out, "%*s|", max_columns[r], "");
            }
        }
        fprintf(out, "\n");
        fprintf(out, "%s\n", line_2);
    }
    free(line_2);
    free(data);
    free(max_columns);
    fclose(file);

    return 0;
}