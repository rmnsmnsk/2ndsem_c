#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct adjacencyList {
    int len;
    int where;
    struct adjacencyList* next;
} adjacencyList;

typedef struct {
    int city;
    int distance;
    int from;
} Candidate;

typedef struct {
    Candidate* arr;
    int size;
    int capacity;
} Heap;

typedef struct {
    int* cities;
    int citiesCount;
    int citiesCapacity;
    Heap* candidates;
} State;

typedef struct {
    int n;
    int m;
    int k;
    adjacencyList** graph;
    int* capitals;
    State* states;
} InputData;

adjacencyList** createGraph(int n);
void addEdge(adjacencyList** list, int from, int to, int len);
void freeGraph(adjacencyList** list, int n);
void freeEdge(adjacencyList* edge);

Heap* heapCreate(int capacity);
void heapPush(Heap* h, Candidate c);
Candidate heapPop(Heap* h);
int heapEmpty(Heap* h);

void stateAddCity(State* s, int city);
void stateAddCandidate(State* s, Candidate c);
Candidate stateGetBestCandidate(State* s);

InputData* readFromFile(char* file);
void freeInputData(InputData* data);
void algorithm(InputData* data);
void printResults(InputData* data);