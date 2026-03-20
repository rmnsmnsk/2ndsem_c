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
    strcpy(node->code, code);
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* insertrecursive(Node* node, char* code, char* name)
{
    if (node == NULL) {
        return createNode(code, name);
    }

    if (strcmp(code, node->code) > 0) {
        node->right = insertrecursive(node->right, code, name);
    } else if (strcmp(code, node->code) < 0) {
        node->left = insertrecursive(node->left, code, name);
    } else if (strcmp(code, node->code) == 0) {
        return node;
    }

    updateHeight(node);
    if (getBalance(node) > 1 && getBalance(node->left) >= 0) {
        node = small_rotate_right(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) <= 0) {
        node = small_rotate_left(node);
    } else if (getBalance(node) > 1 && getBalance(node->left) < 0) {
        node = big_rotate_right(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) > 0) {
        node = big_rotate_left(node);
    }
    return node;
}

Node* NodeDelete(Node* node, char* value)
{
    if (node == NULL)
        return NULL;

    if (strcmp(value, node->code) < 0) {
        node->left = NodeDelete(node->left, value);
    } else if (strcmp(value, node->code) > 0) {
        node->right = NodeDelete(node->right, value);
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

            strcpy(node->code, minRight->code);
            strcpy(node->name, minRight->name);

            if (parent == node) {
                parent->right = NodeDelete(parent->right, minRight->code);
            } else {
                parent->left = NodeDelete(parent->left, minRight->code);
            }
        }
    }
    updateHeight(node);
    if (getBalance(node) > 1 && getBalance(node->left) >= 0) {
        node = small_rotate_right(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) <= 0) {
        node = small_rotate_left(node);
    } else if (getBalance(node) > 1 && getBalance(node->left) < 0) {
        node = big_rotate_right(node);
    } else if (getBalance(node) < -1 && getBalance(node->right) > 0) {
        node = big_rotate_left(node);
    }
    return node;
}

void TreeDelete(Tree* tree, char* value)
{
    if (tree == NULL || tree->root == NULL)
        return;

    Node* existing = TreeFind(tree, value);
    if (existing == NULL)
        return;

    tree->root = NodeDelete(tree->root, value);
    tree->size--;
}

void TreeInsert(Tree* tree, char* code, char* name)
{
    if (tree == NULL)
        return;

    Node* existing = TreeFind(tree, code);

    tree->root = insertrecursive(tree->root, code, name);

    if (existing == NULL) {
        tree->size++;
    }
}

char* get_name(Tree* tree, char* code)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    Node* t = TreeFind(tree, code);
    if (t == NULL) {
        return NULL;
    }
    return t->name;
}

Node* TreeFind(Tree* tree, char* code)
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

void NodeFree(Node* node)
{
    if (node == NULL) {
        return;
    }

    NodeFree(node->right);
    NodeFree(node->left);
    free(node);
}

void TreeFree(Tree* tree)
{
    if (tree == NULL) {
        return;
    }
    NodeFree(tree->root);
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

Node* small_rotate_right(Node* node)
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

Node* small_rotate_left(Node* node)
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

Node* big_rotate_right(Node* node)
{
    node->left = small_rotate_left(node->left);
    return (small_rotate_right(node));
}

Node* big_rotate_left(Node* node)
{
    node->right = small_rotate_right(node->right);
    return (small_rotate_left(node));
}