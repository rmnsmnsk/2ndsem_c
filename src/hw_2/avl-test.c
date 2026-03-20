#include "avl-tree.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int tests_passed = 0;
int tests_failed = 0;

void test_createTree()
{
    Tree* tree = createTree();
    assert(tree != NULL);
    assert(tree->root == NULL);
    assert(tree->size == 0);

    tests_passed++;
    TreeFree(tree);
}

void test_insert()
{
    Tree* tree = createTree();

    TreeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);
    assert(tree->root != NULL);
    assert(strcmp(tree->root->code, "SVO") == 0);

    TreeInsert(tree, "LED", "Pulkovo");
    assert(tree->size == 2);

    TreeInsert(tree, "JFK", "Kennedy");
    assert(tree->size == 3);

    tests_passed++;
    TreeFree(tree);
}

void test_find()
{
    Tree* tree = createTree();

    TreeInsert(tree, "SVO", "Sheremetyevo");
    TreeInsert(tree, "LED", "Pulkovo");
    TreeInsert(tree, "JFK", "Kennedy");

    char* name = get_name(tree, "SVO");
    assert(name != NULL);
    assert(strcmp(name, "Sheremetyevo") == 0);

    name = get_name(tree, "LED");
    assert(name != NULL);
    assert(strcmp(name, "Pulkovo") == 0);

    name = get_name(tree, "XXX");
    assert(name == NULL);

    tests_passed++;
    TreeFree(tree);
}

void test_delete()
{
    Tree* tree = createTree();

    TreeInsert(tree, "SVO", "Sheremetyevo");
    TreeInsert(tree, "LED", "Pulkovo");
    TreeInsert(tree, "JFK", "Kennedy");
    assert(tree->size == 3);

    TreeDelete(tree, "LED");
    assert(tree->size == 2);

    char* name = get_name(tree, "LED");
    assert(name == NULL);

    name = get_name(tree, "SVO");
    assert(name != NULL);

    TreeDelete(tree, "SVO");
    assert(tree->size == 1);

    TreeDelete(tree, "JFK");
    assert(tree->size == 0);
    assert(tree->root == NULL);

    tests_passed++;
    TreeFree(tree);
}

void test_insert_duplicate()
{
    Tree* tree = createTree();

    TreeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);

    TreeInsert(tree, "SVO", "Moscow");
    assert(tree->size == 1);

    char* name = get_name(tree, "SVO");
    assert(strcmp(name, "Sheremetyevo") == 0);

    tests_passed++;
    TreeFree(tree);
}

void test_delete_nonexistent()
{
    Tree* tree = createTree();

    TreeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);

    TreeDelete(tree, "XXX");
    assert(tree->size == 1);

    tests_passed++;
    TreeFree(tree);
}

void test_balance()
{
    Tree* tree = createTree();

    TreeInsert(tree, "AAA", "Airport A");
    TreeInsert(tree, "BBB", "Airport B");
    TreeInsert(tree, "CCC", "Airport C");
    TreeInsert(tree, "DDD", "Airport D");
    TreeInsert(tree, "EEE", "Airport E");

    int balance = getBalance(tree->root);
    assert(balance >= -1 && balance <= 1);

    tests_passed++;
    TreeFree(tree);
}

void test_multiple_operations()
{
    Tree* tree = createTree();

    TreeInsert(tree, "SVO", "Sheremetyevo");
    TreeInsert(tree, "LED", "Pulkovo");
    TreeInsert(tree, "JFK", "Kennedy");
    TreeInsert(tree, "CDG", "Charles de Gaulle");
    TreeInsert(tree, "FRA", "Frankfurt");

    assert(tree->size == 5);

    assert(get_name(tree, "SVO") != NULL);
    assert(get_name(tree, "LED") != NULL);
    assert(get_name(tree, "JFK") != NULL);
    assert(get_name(tree, "CDG") != NULL);
    assert(get_name(tree, "FRA") != NULL);

    TreeDelete(tree, "LED");
    TreeDelete(tree, "JFK");
    assert(tree->size == 3);

    assert(get_name(tree, "SVO") != NULL);
    assert(get_name(tree, "CDG") != NULL);
    assert(get_name(tree, "FRA") != NULL);
    assert(get_name(tree, "LED") == NULL);
    assert(get_name(tree, "JFK") == NULL);

    tests_passed++;
    TreeFree(tree);
}

int main()
{
    test_createTree();
    test_insert();
    test_find();
    test_delete();
    test_insert_duplicate();
    test_delete_nonexistent();
    test_balance();
    test_multiple_operations();

    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);

    if (tests_failed > 0) {
        return 1;
    }
    return 0;
}