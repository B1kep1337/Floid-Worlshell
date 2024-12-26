#include "Header.h"


// ������� ��� ��������� ������ ��� ������� ���������
int** allocate_matrix(int vertices) {
    int** matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = INT_MAX; // �������������: 0 �� ���������, INF - �����
        }
    }
    return matrix;
}

// ������������ ������
void free_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// �������� ������ ���������
Node** allocate_adj_list(int vertices) {
    Node** list = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        list[i] = NULL;
    }
    return list;
}

// ������������ ������ ��� ������ ���������
void free_adj_list(Node** list, int vertices) {
    for (int i = 0; i < vertices; i++) {
        Node* current = list[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(list);
}

// ���������� ����� � ������ ���������
void add_edge_to_adj_list(Node** list, int src, int dest, int weight) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = dest;
    new_node->weight = weight;
    new_node->next = list[src];
    list[src] = new_node;
}

// �������������� ������� ��������� � ������ ���������
Node** matrix_to_adj_list(int** matrix, int vertices, int directed) {
    Node** adj_list = allocate_adj_list(vertices);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] != INT_MAX) {
                add_edge_to_adj_list(adj_list, i, j, matrix[i][j]);
                if (!directed) {
                    add_edge_to_adj_list(adj_list, j, i, matrix[i][j]);
                }
            }
        }
    }
    return adj_list;
}

// �������������� ������� ��������� � ������� ���������
int** adj_list_to_matrix(Node** list, int vertices) {
    int** matrix = allocate_matrix(vertices);
    for (int i = 0; i < vertices; i++) {
        Node* current = list[i];
        while (current) {
            matrix[i][current->vertex] = current->weight;
            current = current->next;
        }
    }
    return matrix;
}

// ����� ������� ���������
void display_adj_list(Node** list, int vertices) {
    printf("������ ���������:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        Node* current = list[i];
        while (current) {
            printf("-> %d(%d) ", current->vertex, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

// �������� ���������� �����
Graph create_random_graph(int vertices, int max_weight, int directed) {
    Graph g;
    g.vertices = vertices;
    g.directed = directed;
    g.matrix = allocate_matrix(vertices);
    srand(time(NULL));
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j && rand() % 2) {
                int weight = rand() % 10 + 1;
                g.matrix[i][j] = weight;
                if (!directed) {
                    g.matrix[j][i] = weight; // �������� ����� ��� ������������������ �����
                }
            }
        }
    }
    g.adj_list = matrix_to_adj_list(g.matrix, vertices, directed);
    return g;
}

// ���� ����� �������
Graph input_graph() {
    Graph g;
    printf("������� ���������� ������: ");
    scanf("%d", &g.vertices);
    g.directed = 1;
    g.matrix = allocate_matrix(g.vertices);
    printf("������� ������� ���������:\n");
    for (int i = 0; i < g.vertices; i++) {
        for (int j = 0; j < g.vertices; j++) {
            printf("������� ����� ��� �������� [%d][%d]: ", i, j);
            g.matrix[i][j] = inputNumber();
        }
    }
    g.adj_list = matrix_to_adj_list(g.matrix, g.vertices, g.directed);
    return g;
}

// ������ ����� �� �����
Graph import_graph(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("������ �������� �����");
        exit(EXIT_FAILURE);
    }
    Graph g;
    fscanf(file, "%d", &g.vertices);
    g.matrix = allocate_matrix(g.vertices);
    for (int i = 0; i < g.vertices; i++) {
        for (int j = 0; j < g.vertices; j++) {
            fscanf(file, "%d", &g.matrix[i][j]);
        }
    }
    g.adj_list = matrix_to_adj_list(g.matrix, g.vertices, 1);
    fclose(file);
    return g;
}

// ������� ����� � ����
void export_graph(Graph g, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("������ �������� �����");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", g.vertices);
    for (int i = 0; i < g.vertices; i++) {
        for (int j = 0; j < g.vertices; j++) {
            fprintf(file, "%d ", g.matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// �������� ����� (������� ���������)
void display_graph(Graph g) {
    printf("������� ���������:\n");
    for (int i = 0; i < g.vertices; i++) {
        for (int j = 0; j < g.vertices; j++) {
            if (g.matrix[i][j] == INT_MAX) {
                printf("INF ");
            }
            else {
                printf("%3d ", g.matrix[i][j]);
            }
        }
        printf("\n");
    }
    display_adj_list(g.adj_list, g.vertices);
}

// �������� ������-��������
void floyd_warshall(Graph g) {
    int** dist = allocate_matrix(g.vertices);

    // ������������� ������� ����������
    for (int i = 0; i < g.vertices; i++) {
        for (int j = 0; j < g.vertices; j++) {
            if (i == j) {
                dist[i][j] = 0; // ���������� �� ������� � ����� ���� ����� 0
            }
            else if (g.matrix[i][j] == INT_MAX) {
                dist[i][j] = INT_MAX; // ������������� ����� - ��� INF (��� INT_MAX)
            }
            else {
                dist[i][j] = g.matrix[i][j]; // �������� ���� �����
            }
        }
    }

    // ���������� ��������� ������-��������
    for (int k = 0; k < g.vertices; k++) {
        for (int i = 0; i < g.vertices; i++) {
            for (int j = 0; j < g.vertices; j++) {
                // �������� ������������: dist[i][k] ��� dist[k][j] �� ������ ���� INT_MAX
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    printf("���������� ���� ����� ����� ������ ������:\n");
    Graph result;
    result.matrix = dist;
    result.vertices = g.vertices;
    result.adj_list = matrix_to_adj_list(result.matrix, result.vertices, 1);
    display_graph(result);
    free_matrix(dist, g.vertices);
}

int inputNumber() {
    char input[255];
    int number;
    int isValidInput = 0;

    do {
        isValidInput = 1; // ������������, ��� ���� ���������
        scanf("%s", input);

        // ��������� ������ ������ � ������
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                isValidInput = 0; // ������������ ����, ���� ������ �� �����
                printf("������! ������� ������ �����.\n");
                break;
            }
        }

        // ������� �����
        while (getchar() != '\n');

    } while (!isValidInput);

    // ����������� ������ � �����
    sscanf(input, "%d", &number);

    return number;
}