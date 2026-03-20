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
Node* insertrecursive(Node* node, char* code, char* name);
Node* NodeDelete(Node* node, char* value);
void TreeDelete(Tree* tree, char* value);
void TreeInsert(Tree* tree, char* code, char* name);
char* get_name(Tree* tree, char* code);
Node* TreeFind(Tree* tree, char* code);
void NodeFree(Node* node);
void TreeFree(Tree* tree);
void updateHeight(Node* node);
int getHeight(Node* node);
int getBalance(Node* node);
Node* small_rotate_right(Node* node);
Node* small_rotate_left(Node* node);
Node* big_rotate_right(Node* node);
Node* big_rotate_left(Node* node);
