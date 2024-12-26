#include "Header.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Graph g = { NULL, 0 };
    int choice, vertices, max_weight = 100;
    char filename[100];
    printf("�������� ������\n�� ����������: \"������ � ������ �������������� � ���������� �������\"\n�� ����: \"���������� ��������� ������������� �����\"\n\n�������� ������� ������ 23���1: ������� ������ ����������\n������: �.�.�. ������ ����� �.�.\n\n");
    system("PAUSE");
    system("cls");
    do
    {
        printf("����:\n");
        printf("1. ������� ��������� ����\n");
        printf("2. ������ ���� �������\n");
        printf("3. ������������� ���� �� �����\n");
        printf("4. ��������� ���� � ����\n");
        printf("5. ����������� ����\n");
        printf("6. ����� ����������� ���� (�����-�������)\n");
        printf("7. �����\n");
        printf("������� ��� �����: ");
        choice = inputNumber();

        switch (choice) {
        case 1:
            printf("������� ���������� ������: ");
            vertices = inputNumber();
            if (g.matrix) free_matrix(g.matrix, g.vertices);
            g = create_random_graph(vertices, max_weight, 1);
            display_graph(g);
            break;
        case 2:
            if (g.matrix) free_matrix(g.matrix, g.vertices);
            g = input_graph();
            break;
        case 3:
            printf("������� ��� �����: ");
            scanf("%s", filename);
            if (g.matrix) free_matrix(g.matrix, g.vertices);
            g = import_graph(filename);
            break;
        case 4:
            printf("������� ��� �����: ");
            scanf("%s", filename);
            export_graph(g, filename);
            break;
        case 5:
            display_graph(g);
            break;
        case 6:
            floyd_warshall(g);
            break;
        case 7:
            if (g.matrix) free_matrix(g.matrix, g.vertices);
            printf("�� ��������!");
            break;
        default:
            printf("�������� �����. ��������� �������.\n");
            break;
        }
    } 
    while (choice != 7);

    return 0;
}
