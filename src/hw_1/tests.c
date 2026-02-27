#include "func.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool if_same(char* x, char* y, int n)
{
    if (x == NULL || y == NULL)
        return false;
    for (int i = 0; i < n; i++) {
        if (x[i] != y[i]) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    bool failed = 0;

    printf("Tests for is_number\n");

    if (is_number("123") != 1) {
        printf("Test for 123 was failed\n");
        failed = 1;
    }

    if (is_number("abs") != 0) {
        printf("Test for abs was failed\n");
        failed = 1;
    }

    if (is_number("-5") != 1) {
        printf("Test for -5 was failed\n");
        failed = 1;
    }

    if (is_number("12.3") != 1) {
        printf("Test for 12.3 was failed\n");
        failed = 1;
    }

    if (is_number("-13.2") != 1) {
        printf("Test for -13.2 was failed\n");
        failed = 1;
    }

    if (is_number("ASJNSAK!") != 0) {
        printf("Test for ASJNSAK! was failed\n");
        failed = 1;
    }

    if (is_number("123..2") != 0) {
        printf("Test for 123..2 was failed\n");
        failed = 1;
    }

    if (is_number("-123..2") != 0) {
        printf("Test for -123..2 was failed\n");
        failed = 1;
    }

    printf("Tests for get_word\n");

    char str[] = "one,two,three";
    char* word;

    word = get_word(str, 1);
    if (!if_same(word, "one", sizeof("one") - 1)) { // -1 чтобы убрать \0'
        printf("Test for one was failed\n");
        failed = 1;
    } else {
        printf("Test for one passed: '%s'\n", word);
    }
    free(word);

    word = get_word(str, 2);
    if (!if_same(word, "two", sizeof("two") - 1)) {
        printf("Test for two was failed\n");
        failed = 1;
    } else {
        printf("Test for two passed: '%s'\n", word);
    }
    free(word);

    word = get_word(str, 3);
    if (!if_same(word, "three", sizeof("three") - 1)) {
        printf("Test for three was failed\n");
        failed = 1;
    } else {
        printf("Test for three passed: '%s'\n", word);
    }
    free(word);

    word = get_word(str, 4);
    if (word != NULL) {
        printf("Test for out of range was failed (should be NULL)\n");
        failed = 1;
        free(word);
    } else {
        printf("Test for out of range passed\n");
    }

    printf("Tests for clean_str\n");

    char s1[] = "hello\n";
    if (clean_str(s1) != 5) {
        printf("Test for 'hello\\n' was failed\n");
        failed = 1;
    } else {
        printf("Test for 'hello\\n' passed\n");
    }

    char s2[] = "world";
    if (clean_str(s2) != 5) {
        printf("Test for 'world' was failed\n");
        failed = 1;
    } else {
        printf("Test for 'world' passed\n");
    }

    char s3[] = "test\nstring";
    if (clean_str(s3) != 4) {
        printf("Test for 'test\\nstring' was failed\n");
        failed = 1;
    } else {
        printf("Test for 'test\\nstring' passed\n");
    }

    char s4[] = "";
    if (clean_str(s4) != 0) {
        printf("Test for empty string was failed\n");
        failed = 1;
    } else {
        printf("Test for empty string passed\n");
    }

    printf("Tests for copy_str\n");

    char original[] = "hello";
    char* copy = copy_str(original, 5);

    if (!if_same(copy, original, 5)) {
        printf("Test for copy_str was failed\n");
        failed = 1;
    } else {
        printf("Test for copy_str passed: '%s'\n", copy);
    }
    free(copy);

    char empty[] = "";
    copy = copy_str(empty, 0);
    if (copy == NULL || copy[0] != '\0') {
        printf("Test for copy_str empty was failed\n");
        failed = 1;
    } else {
        printf("Test for copy_str empty passed\n");
    }
    free(copy);

    printf("Tests for get_line\n");

    int widths[] = { 3, 5, 4 };
    char* line = get_line('-', 16, widths, 3);

    if (if_same(line, "+---+-----+----+", 16) == 1) {
        printf("Test for get_line (3 columns) passed \n");
    } else {
        printf("Test for get_line (3 columns) failed \n");
        printf("Expected: +---+-----+----+\n");
        printf("Got:%s\n", line);
        failed = 1;
    }
    free(line);

    int widths2[] = { 2, 2 };
    line = get_line('=', 7, widths2, 2);

    if (if_same(line, "+==+==+", 7) == 1) {
        printf("Test for get_line (2 columns) passed \n");
    } else {
        printf("Test for get_line (2 columns) failed \n");
        printf("Expected: +==+==+\n");
        printf("Got:%s\n", line);
        failed = 1;
    }
    free(line);

    printf("Final results\n");
    if (failed == 0) {
        printf("All tests passed\n");
    } else {
        printf("Some tests failed \n");
    }

    return failed;
}