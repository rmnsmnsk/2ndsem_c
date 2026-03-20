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
    treeFree(tree);
}

void test_insert()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);
    assert(tree->root != NULL);
    assert(strcmp(tree->root->code, "SVO") == 0);

    treeInsert(tree, "LED", "Pulkovo");
    assert(tree->size == 2);

    treeInsert(tree, "JFK", "Kennedy");
    assert(tree->size == 3);

    tests_passed++;
    treeFree(tree);
}

void test_find()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    treeInsert(tree, "LED", "Pulkovo");
    treeInsert(tree, "JFK", "Kennedy");

    char* name = getName(tree, "SVO");
    assert(name != NULL);
    assert(strcmp(name, "Sheremetyevo") == 0);

    name = getName(tree, "LED");
    assert(name != NULL);
    assert(strcmp(name, "Pulkovo") == 0);

    name = getName(tree, "XXX");
    assert(name == NULL);

    tests_passed++;
    treeFree(tree);
}

void test_delete()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    treeInsert(tree, "LED", "Pulkovo");
    treeInsert(tree, "JFK", "Kennedy");
    assert(tree->size == 3);

    treeDelete(tree, "LED");
    assert(tree->size == 2);

    char* name = getName(tree, "LED");
    assert(name == NULL);

    name = getName(tree, "SVO");
    assert(name != NULL);

    treeDelete(tree, "SVO");
    assert(tree->size == 1);

    treeDelete(tree, "JFK");
    assert(tree->size == 0);
    assert(tree->root == NULL);

    tests_passed++;
    treeFree(tree);
}

void test_insert_duplicate()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);

    treeInsert(tree, "SVO", "Moscow");
    assert(tree->size == 1);

    char* name = getName(tree, "SVO");
    assert(strcmp(name, "Sheremetyevo") == 0);

    tests_passed++;
    treeFree(tree);
}

void test_delete_nonexistent()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);

    treeDelete(tree, "XXX");
    assert(tree->size == 1);

    tests_passed++;
    treeFree(tree);
}

void testBalance()
{
    Tree* tree = createTree();

    treeInsert(tree, "AAA", "Airport A");
    treeInsert(tree, "BBB", "Airport B");
    treeInsert(tree, "CCC", "Airport C");
    treeInsert(tree, "DDD", "Airport D");
    treeInsert(tree, "EEE", "Airport E");

    int balance = getBalance(tree->root);
    assert(balance >= -1 && balance <= 1);

    tests_passed++;
    treeFree(tree);
}

void testMultipleOperations()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    treeInsert(tree, "LED", "Pulkovo");
    treeInsert(tree, "JFK", "Kennedy");
    treeInsert(tree, "CDG", "Charles de Gaulle");
    treeInsert(tree, "FRA", "Frankfurt");

    assert(tree->size == 5);

    assert(getName(tree, "SVO") != NULL);
    assert(getName(tree, "LED") != NULL);
    assert(getName(tree, "JFK") != NULL);
    assert(getName(tree, "CDG") != NULL);
    assert(getName(tree, "FRA") != NULL);

    treeDelete(tree, "LED");
    treeDelete(tree, "JFK");
    assert(tree->size == 3);

    assert(getName(tree, "SVO") != NULL);
    assert(getName(tree, "CDG") != NULL);
    assert(getName(tree, "FRA") != NULL);
    assert(getName(tree, "LED") == NULL);
    assert(getName(tree, "JFK") == NULL);

    tests_passed++;
    treeFree(tree);
}

int main()
{
    test_createTree();
    test_insert();
    test_find();
    test_delete();
    test_insert_duplicate();
    test_delete_nonexistent();
    testBalance();
    testMultipleOperations();

    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);

    if (tests_failed > 0) {
        return 1;
    }
    return 0;
}