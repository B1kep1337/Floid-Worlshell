#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <Windows.h>
#define INF INT_MAX;
#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node** adj_list; // Списки смежности
    int** matrix; // Матрица смежности
    int vertices;
    int directed;
} Graph;

int** allocate_matrix(int vertices);
void free_matrix(int** matrix, int vertices);
Graph create_random_graph(int vertices, int max_weight, int directed);
Graph input_graph();
Graph import_graph(const char* filename);
void export_graph(Graph g, const char* filename);
void display_graph(Graph g);
void floyd_warshall(Graph g);
int inputNumber();