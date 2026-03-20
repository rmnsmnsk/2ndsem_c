#pragma once
#include <stdbool.h>

typedef struct Node {
    char code[4];
    char name[256];
    struct Node* left;
    struct Node* right;
    int height;
} Node;

typedef struct Tree {
    Node* root;
    int size;
} Tree;

Tree* createTree(void);
Node* createNode(char* code, char* name);
Node* insertRecursive(Node* node, char* code, char* name);
Node* nodeDelete(Node* node, char* value);
void treeDelete(Tree* tree, char* value);
void treeInsert(Tree* tree, char* code, char* name);
char* getName(Tree* tree, char* code);
Node* treeFind(Tree* tree, char* code);
void nodeFree(Node* node);
void treeFree(Tree* tree);
void updateHeight(Node* node);
int getHeight(Node* node);
int getBalance(Node* node);
Node* smallRotateRight(Node* node);
Node* smallRotateLeft(Node* node);
Node* bigRotateRight(Node* node);
Node* bigRotateLeft(Node* node);
