#include "main.h"

typedef struct Vertex {
    int distance;
    int vertex;
    int visited;
} Vertex;

int** createGOW(int size);

int** createGO(int size);

void mirG(int** G, int size);

void printG(int** G, int size);

int compare(const void* a, const void* b);

void dijkstra(int** G, int size, int* dist, int s);

void clearb();

void save_to_file(int** G, int size, const char* filename);

int** open_from_file(const char* filename, int* size);