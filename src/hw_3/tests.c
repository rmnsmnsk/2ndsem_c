#include "func.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void testCreateGraph(void)
{
    adjacencyList** graph = createGraph(5);
    assert(graph != NULL);
    for (int i = 0; i < 5; i++) {
        assert(graph[i] == NULL);
    }
    freeGraph(graph, 5);
}

void testAddEdge(void)
{
    adjacencyList** graph = createGraph(5);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 1, 10);
    assert(graph[0] != NULL);
    assert(graph[0]->where == 2);
    assert(graph[0]->len == 10);
    assert(graph[1] != NULL);
    assert(graph[1]->where == 1);
    assert(graph[1]->len == 10);
    freeGraph(graph, 5);
}

void testHeapCreate(void)
{
    Heap* h = heapCreate(10);
    assert(h != NULL);
    assert(h->size == 0);
    assert(h->capacity == 10);
    assert(h->arr != NULL);
    free(h->arr);
    free(h);
}

void testHeapPushPop(void)
{
    Heap* h = heapCreate(2);
    Candidate c1 = { 1, 10, 0 };
    Candidate c2 = { 2, 5, 0 };
    Candidate c3 = { 3, 8, 0 };
    heapPush(h, c1);
    heapPush(h, c2);
    heapPush(h, c3);
    Candidate min = heapPop(h);
    assert(min.city == 2);
    assert(min.distance == 5);
    min = heapPop(h);
    assert(min.city == 3);
    assert(min.distance == 8);
    min = heapPop(h);
    assert(min.city == 1);
    assert(min.distance == 10);
    free(h->arr);
    free(h);
}

void testHeapEmpty(void)
{
    Heap* h = heapCreate(5);
    assert(heapEmpty(h) == 1);
    Candidate c = { 1, 10, 0 };
    heapPush(h, c);
    assert(heapEmpty(h) == 0);
    heapPop(h);
    assert(heapEmpty(h) == 1);
    free(h->arr);
    free(h);
}

void testStateAddCity(void)
{
    State s;
    s.cities = malloc(2 * sizeof(int));
    s.citiesCount = 0;
    s.citiesCapacity = 2;
    s.candidates = heapCreate(10);
    stateAddCity(&s, 1);
    stateAddCity(&s, 2);
    assert(s.citiesCount == 2);
    assert(s.cities[0] == 1);
    assert(s.cities[1] == 2);
    stateAddCity(&s, 3);
    assert(s.citiesCount == 3);
    assert(s.citiesCapacity == 4);
    free(s.cities);
    free(s.candidates->arr);
    free(s.candidates);
}

void testStateAddCandidate(void)
{
    State s;
    s.candidates = heapCreate(10);
    Candidate c1 = { 1, 10, 0 };
    Candidate c2 = { 2, 5, 0 };
    stateAddCandidate(&s, c1);
    stateAddCandidate(&s, c2);
    assert(s.candidates->size == 2);
    Candidate best = stateGetBestCandidate(&s);
    assert(best.city == 2);
    assert(best.distance == 5);
    free(s.candidates->arr);
    free(s.candidates);
}

void testReadFromFile(void)
{
    FILE* f = fopen("test_input.txt", "w");
    fprintf(f, "5 4\n");
    fprintf(f, "1 2 10\n");
    fprintf(f, "2 3 5\n");
    fprintf(f, "3 4 8\n");
    fprintf(f, "4 5 3\n");
    fprintf(f, "2\n");
    fprintf(f, "1 5\n");
    fclose(f);

    InputData* data = readFromFile("test_input.txt");
    assert(data != NULL);
    assert(data->n == 5);
    assert(data->m == 4);
    assert(data->k == 2);
    assert(data->capitals[0] == 1);
    assert(data->capitals[1] == 5);
    assert(data->graph != NULL);
    assert(data->states != NULL);

    freeInputData(data);
    remove("test_input.txt");
}

int main(void)
{
    testCreateGraph();
    testAddEdge();
    testHeapCreate();
    testHeapPushPop();
    testHeapEmpty();
    testStateAddCity();
    testStateAddCandidate();
    testReadFromFile();

    printf("Всё ок\n");
    return 0;
}