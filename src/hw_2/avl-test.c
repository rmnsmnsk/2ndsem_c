#include "avl-tree.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int testsPassed = 0;
int testsFailed = 0;

void testCreateTree()
{
    Tree* tree = createTree();
    assert(tree != NULL);
    assert(tree->root == NULL);
    assert(tree->size == 0);

    testsPassed++;
    treeFree(tree);
}

void testInsert()
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

    testsPassed++;
    treeFree(tree);
}

void testFind()
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

    testsPassed++;
    treeFree(tree);
}

void testDelete()
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

    testsPassed++;
    treeFree(tree);
}

void testInsertDuplicate()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);

    treeInsert(tree, "SVO", "Moscow");
    assert(tree->size == 1);

    char* name = getName(tree, "SVO");
    assert(strcmp(name, "Sheremetyevo") == 0);

    testsPassed++;
    treeFree(tree);
}

void testDeleteNonexistent()
{
    Tree* tree = createTree();

    treeInsert(tree, "SVO", "Sheremetyevo");
    assert(tree->size == 1);

    treeDelete(tree, "XXX");
    assert(tree->size == 1);

    testsPassed++;
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

    testsPassed++;
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

    testsPassed++;
    treeFree(tree);
}

int main()
{
    testCreateTree();
    testInsert();
    testFind();
    testDelete();
    testInsertDuplicate();
    testDeleteNonexistent();
    testBalance();
    testMultipleOperations();

    printf("Tests passed: %d\n", testsPassed);
    printf("Tests failed: %d\n", testsFailed);

    if (testsFailed > 0) {
        return 1;
    }
    return 0;
}