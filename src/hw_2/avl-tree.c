#include "avl-tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tree* createTree(void)
{
    Tree* tree = malloc(sizeof(Tree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

Node* createNode(char* code, char* name)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    strncpy(node->code, code, sizeof(node->code) - 1);
    node->code[sizeof(node->code) - 1] = '\0';

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* insertRecursive(Node* node, char* code, char* name)
{
    if (node == NULL) {
        return createNode(code, name);
    }

    if (strcmp(code, node->code) > 0) {
        node->right = insertRecursive(node->right, code, name);
    } else if (strcmp(code, node->code) < 0) {
        node->left = insertRecursive(node->left, code, name);
    } else if (strcmp(code, node->code) == 0) {
        return node;
    }

    updateHeight(node);
    if (getBalance(node) > 1 && getBalance(node->left) >= 0) {
        node = smallRotateRight(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) <= 0) {
        node = smallRotateLeft(node);
    } else if (getBalance(node) > 1 && getBalance(node->left) < 0) {
        node = bigRotateRight(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) > 0) {
        node = bigRotateLeft(node);
    }
    return node;
}

Node* nodeDelete(Node* node, char* value)
{
    if (node == NULL)
        return NULL;

    if (strcmp(value, node->code) < 0) {
        node->left = nodeDelete(node->left, value);
    } else if (strcmp(value, node->code) > 0) {
        node->right = nodeDelete(node->right, value);
    } else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        } else if (node->left == NULL) {
            Node* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            Node* temp = node->left;
            free(node);
            return temp;
        } else {
            Node* parent = node;
            Node* minRight = node->right;

            while (minRight->left != NULL) {
                parent = minRight;
                minRight = minRight->left;
            }

            strncpy(node->code, minRight->code, sizeof(node->code) - 1);
            node->code[sizeof(node->code) - 1] = '\0';

            strncpy(node->name, minRight->name, sizeof(node->name) - 1);
            node->name[sizeof(node->name) - 1] = '\0';

            if (parent == node) {
                parent->right = nodeDelete(parent->right, minRight->code);
            } else {
                parent->left = nodeDelete(parent->left, minRight->code);
            }
        }
    }
    updateHeight(node);
    if (getBalance(node) > 1 && getBalance(node->left) >= 0) {
        node = smallRotateRight(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) <= 0) {
        node = smallRotateLeft(node);
    } else if (getBalance(node) > 1 && getBalance(node->left) < 0) {
        node = bigRotateRight(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) > 0) {
        node = bigRotateLeft(node);
    }
    return node;
}

void treeDelete(Tree* tree, char* value)
{
    if (tree == NULL || tree->root == NULL)
        return;

    Node* existing = treeFind(tree, value);
    if (existing == NULL)
        return;

    tree->root = nodeDelete(tree->root, value);
    tree->size--;
}

void treeInsert(Tree* tree, char* code, char* name)
{
    if (tree == NULL)
        return;

    Node* existing = treeFind(tree, code);

    tree->root = insertRecursive(tree->root, code, name);

    if (existing == NULL) {
        tree->size++;
    }
}

char* getName(Tree* tree, char* code)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    Node* t = treeFind(tree, code);
    if (t == NULL) {
        return NULL;
    }
    return t->name;
}

Node* treeFind(Tree* tree, char* code)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }
    Node* current = tree->root;
    while (current != NULL) {
        int cmp = strcmp(code, current->code);
        if (cmp == 0) {
            return current;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void nodeFree(Node* node)
{
    if (node == NULL) {
        return;
    }

    nodeFree(node->right);
    nodeFree(node->left);
    free(node);
}

void treeFree(Tree* tree)
{
    if (tree == NULL) {
        return;
    }
    nodeFree(tree->root);
    free(tree);
}

void updateHeight(Node* node)
{
    if (node == NULL) {
        return;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    if (leftHeight > rightHeight) {
        node->height = leftHeight + 1;
    } else {
        node->height = rightHeight + 1;
    }
}

int getHeight(Node* node)
{
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(Node* node)
{
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* smallRotateRight(Node* node)
{
    if (node == NULL) {
        return NULL;
    }
    Node* result = node->left;
    node->left = result->right;
    result->right = node;
    updateHeight(node);
    updateHeight(result);
    return result;
}

Node* smallRotateLeft(Node* node)
{
    if (node == NULL) {
        return NULL;
    }
    Node* result = node->right;
    node->right = result->left;
    result->left = node;
    updateHeight(node);
    updateHeight(result);
    return result;
}

Node* bigRotateRight(Node* node)
{
    node->left = smallRotateLeft(node->left);
    return (smallRotateRight(node));
}

Node* bigRotateLeft(Node* node)
{
    node->right = smallRotateRight(node->right);
    return (smallRotateLeft(node));
}