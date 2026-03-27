#include "func.h"
#include "stdio.h"
#include "stdlib.h"

AdjacencyList** createGraph(int n)
{
    AdjacencyList** graph = malloc(sizeof(AdjacencyList*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
    }
    return graph;
}
void addEdge(AdjacencyList** list, int from, int to, int len)
{

    AdjacencyList* current = malloc(sizeof(AdjacencyList));
    current->len = len;
    current->where = to;
    if (list[from - 1] == NULL) {
        list[from - 1] = current;
        current->next = NULL;
    } else {
        current->next = list[from - 1];
        list[from - 1] = current;
    }
}

void freeEdge(AdjacencyList* edge)
{
    AdjacencyList* current = edge;
    while (current != NULL) {
        AdjacencyList* tempCurrent = current;
        current = current->next;
        free(tempCurrent);
    }
}

void freeGraph(AdjacencyList** list, int n)
{
    for (int i = 0; i < n; ++i) {
        freeEdge(list[i]);
    }
    free(list);
}

Heap* heapCreate(int capacity)
{
    Candidate* y = malloc(sizeof(Candidate) * capacity);
    Heap* result = malloc(sizeof(Heap));
    result->arr = y;
    result->size = 0;
    result->capacity = capacity;
    return result;
}
void heapPush(Heap* h, Candidate c)
{
    if (h == NULL) {
        return;
    }
    if (h->size >= h->capacity) {
        h->capacity = (h->capacity) * 2;
        h->arr = realloc(h->arr, h->capacity * sizeof(Candidate));
    }
    h->arr[h->size] = c;
    int j = h->size;
    h->size++;
    while (j > 0) {
        int parent = (j - 1) / 2;
        if (h->arr[parent].distance <= h->arr[j].distance) {
            break;
        }
        Candidate temp = h->arr[j];
        h->arr[j] = h->arr[parent];
        h->arr[parent] = temp;

        j = parent;
    }
}
Candidate heapPop(Heap* h)
{
    if (h == NULL || h->size == 0) {
        Candidate empty = { -1, -1, -1 };
        return empty;
    }

    Candidate min = h->arr[0];
    h->size--;

    if (h->size > 0) {
        h->arr[0] = h->arr[h->size];

        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < h->size && h->arr[left].distance < h->arr[smallest].distance) {
                smallest = left;
            }
            if (right < h->size && h->arr[right].distance < h->arr[smallest].distance) {
                smallest = right;
            }

            if (smallest == i) {
                break;
            }

            Candidate temp = h->arr[i];
            h->arr[i] = h->arr[smallest];
            h->arr[smallest] = temp;
            i = smallest;
        }
    }

    return min;
}

int heapEmpty(Heap* h)
{
    return (h == NULL || h->size == 0);
}

// Государство
void stateAddCity(State* s, int city)
{
    if (s == NULL) {
        return;
    }
    if (s->citiesCount >= s->citiesCapacity) {
        s->citiesCapacity *= 2;
        s->cities = realloc(s->cities, s->citiesCapacity * sizeof(int));
    }
    s->cities[s->citiesCount] = city;
    s->citiesCount++;
}

void stateAddCandidate(State* s, Candidate c)
{
    heapPush(s->candidates, c);
}
Candidate stateGetBestCandidate(State* s)
{
    return heapPop(s->candidates);
}
// Основные
InputData* readFromFile(char* file)
{
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        return NULL;
    }
    InputData* result = malloc(sizeof(InputData));
    if (result == NULL) {
        fclose(f);
        return NULL;
    }
    fscanf(f, "%d %d", &result->n, &result->m);
    AdjacencyList** new = createGraph(result->n);
    for (int t = 0; t < result->m; t++) {
        int i, j, len;
        fscanf(f, "%d %d %d", &i, &j, &len);
        addEdge(new, i, j, len);
        addEdge(new, j, i, len);
    }
    result->graph = new;
    int h;
    fscanf(f, "%d", &h);
    result->k = h;
    int* capitals = malloc(h * sizeof(int));

    for (int i = 0; i < h; i++) {
        fscanf(f, "%d", &capitals[i]);
    }
    result->capitals = capitals;
    result->states = malloc((result->k + 1) * sizeof(State));
    for (int i = 1; i <= result->k; i++) {
        result->states[i].cities = malloc(10 * sizeof(int));
        result->states[i].citiesCount = 0;
        result->states[i].citiesCapacity = 10;
        result->states[i].candidates = heapCreate(100);
    }
    fclose(f);
    return result;
}

void freeInputData(InputData* data)
{
    if (data == NULL)
        return;

    if (data->graph != NULL) {
        freeGraph(data->graph, data->n);
    }

    if (data->capitals != NULL) {
        free(data->capitals);
    }

    if (data->states != NULL) {
        for (int i = 1; i <= data->k; i++) {
            if (data->states[i].cities != NULL) {
                free(data->states[i].cities);
            }
            if (data->states[i].candidates != NULL) {
                if (data->states[i].candidates->arr != NULL) {
                    free(data->states[i].candidates->arr);
                }
                free(data->states[i].candidates);
            }
        }
        free(data->states);
    }

    free(data);
}

void algorithm(InputData* data)
{
    if (data == NULL) {
        return;
    }

    int* owner = calloc(data->n + 1, sizeof(int));

    for (int stateNum = 1; stateNum <= data->k; stateNum++) {
        int capital = data->capitals[stateNum - 1];
        owner[capital] = stateNum;
        stateAddCity(&data->states[stateNum], capital);
    }

    for (int stateNum = 1; stateNum <= data->k; stateNum++) {
        int capital = data->capitals[stateNum - 1];
        AdjacencyList* edge = data->graph[capital - 1];

        while (edge != NULL) {
            int neighbor = edge->where;
            if (owner[neighbor] == 0) {
                Candidate candidate = { neighbor, edge->len, capital };
                stateAddCandidate(&data->states[stateNum], candidate);
            }
            edge = edge->next;
        }
    }

    int assignedCities = data->k;

    while (assignedCities < data->n) {
        for (int stateNum = 1; stateNum <= data->k; stateNum++) {
            State* currentState = &data->states[stateNum];

            while (!heapEmpty(currentState->candidates)) {
                Candidate best = heapPop(currentState->candidates);

                if (best.city == -1) {
                    break;
                }

                if (owner[best.city] == 0) {
                    owner[best.city] = stateNum;
                    stateAddCity(currentState, best.city);
                    assignedCities++;

                    AdjacencyList* edge = data->graph[best.city - 1];
                    while (edge != NULL) {
                        int neighbor = edge->where;
                        if (owner[neighbor] == 0) {
                            Candidate newCandidate = { neighbor, edge->len, best.city };
                            heapPush(currentState->candidates, newCandidate);
                        }
                        edge = edge->next;
                    }
                    break;
                }
            }

            if (assignedCities >= data->n) {
                break;
            }
        }
    }

    free(owner);
}
void printResults(InputData* data)
{
    if (data == NULL) {
        return;
    }
    for (int i = 1; i <= data->k; i++) {
        printf("%d: ", i);
        State* s = &data->states[i];
        for (int j = 0; j < s->citiesCount; j++) {
            printf("%d ", s->cities[j]);
        }
        printf("\n");
    }
}
