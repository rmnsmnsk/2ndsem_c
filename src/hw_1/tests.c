#include "func.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ifSame(const char* x, const char* y, int n)
{
    if (x == NULL || y == NULL)
        return false;
    for (int i = 0; i < n; i++) {
        if (x[i] != y[i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    bool failed = false;

    printf("Tests for isNumber\n");

    if (isNumber("123") != 1) {
        printf("Test for 123 failed\n");
        failed = true;
    }

    if (isNumber("abs") != 0) {
        printf("Test for abs failed\n");
        failed = true;
    }

    if (isNumber("-5") != 1) {
        printf("Test for -5 failed\n");
        failed = true;
    }

    if (isNumber("12.3") != 1) {
        printf("Test for 12.3 failed\n");
        failed = true;
    }

    if (isNumber("-13.2") != 1) {
        printf("Test for -13.2 failed\n");
        failed = true;
    }

    if (isNumber("ASJNSAK!") != 0) {
        printf("Test for ASJNSAK! failed\n");
        failed = true;
    }

    if (isNumber("123..2") != 0) {
        printf("Test for 123..2 failed\n");
        failed = true;
    }

    if (isNumber("-123..2") != 0) {
        printf("Test for -123..2 failed\n");
        failed = true;
    }

    printf("Tests for getWord\n");

    char str[] = "one,two,three";
    char* word;

    word = getWord(str, 1);
    if (!ifSame(word, "one", sizeof("one") - 1)) {
        printf("Test for one failed\n");
        failed = true;
    } else {
        printf("Test for one passed: '%s'\n", word);
    }
    free(word);

    word = getWord(str, 2);
    if (!ifSame(word, "two", sizeof("two") - 1)) {
        printf("Test for two failed\n");
        failed = true;
    } else {
        printf("Test for two passed: '%s'\n", word);
    }
    free(word);

    word = getWord(str, 3);
    if (!ifSame(word, "three", sizeof("three") - 1)) {
        printf("Test for three failed\n");
        failed = true;
    } else {
        printf("Test for three passed: '%s'\n", word);
    }
    free(word);

    word = getWord(str, 4);
    if (word != NULL) {
        printf("Test for out of range failed (should be NULL)\n");
        failed = true;
        free(word);
    } else {
        printf("Test for out of range passed\n");
    }

    printf("Tests for cleanStr\n");

    char s1[] = "hello\n";
    if (cleanStr(s1) != 5) {
        printf("Test for 'hello\\n' failed\n");
        failed = true;
    } else {
        printf("Test for 'hello\\n' passed\n");
    }

    char s2[] = "world";
    if (cleanStr(s2) != 5) {
        printf("Test for 'world' failed\n");
        failed = true;
    } else {
        printf("Test for 'world' passed\n");
    }

    char s3[] = "test\nstring";
    if (cleanStr(s3) != 4) {
        printf("Test for 'test\\nstring' failed\n");
        failed = true;
    } else {
        printf("Test for 'test\\nstring' passed\n");
    }

    char s4[] = "";
    if (cleanStr(s4) != 0) {
        printf("Test for empty string failed\n");
        failed = true;
    } else {
        printf("Test for empty string passed\n");
    }

    printf("Tests for copyStr\n");

    char original[] = "hello";
    char* copy = copyStr(original, 5);

    if (!ifSame(copy, original, 5)) {
        printf("Test for copyStr failed\n");
        failed = true;
    } else {
        printf("Test for copyStr passed: '%s'\n", copy);
    }
    free(copy);

    char empty[] = "";
    copy = copyStr(empty, 0);
    if (copy == NULL || copy[0] != '\0') {
        printf("Test for copyStr empty failed\n");
        failed = true;
    } else {
        printf("Test for copyStr empty passed\n");
    }
    free(copy);

    printf("Tests for getLine\n");

    int widths[] = { 3, 5, 4 };
    char* line = getLine('-', 16, widths, 3);

    if (ifSame(line, "+---+-----+----+", 16)) {
        printf("Test for getLine (3 columns) passed\n");
    } else {
        printf("Test for getLine (3 columns) failed\n");
        printf("Expected: +---+-----+----+\n");
        printf("Got: %s\n", line);
        failed = true;
    }
    free(line);

    int widths2[] = { 2, 2 };
    line = getLine('=', 7, widths2, 2);

    if (ifSame(line, "+==+==+", 7)) {
        printf("Test for getLine (2 columns) passed\n");
    } else {
        printf("Test for getLine (2 columns) failed\n");
        printf("Expected: +==+==+\n");
        printf("Got: %s\n", line);
        failed = true;
    }
    free(line);

    printf("\nFinal results\n");
    if (!failed) {
        printf("All tests passed\n");
        return 0;
    } else {
        printf("Some tests failed\n");
        return 1;
    }
}