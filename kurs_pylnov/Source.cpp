#include "Header.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Graph g = { NULL, 0 };
    int choice, vertices, max_weight = 100;
    char filename[100];
    printf("Курсовая работа\nПо дисциплине: \"Логика и основы алгоритмизации в инженерных задачах\"\nНа тему: \"Реализация алгоритма раскрашивания графа\"\n\nВыполнил студент группы 23ВВВ1: Пыльнов Никита Николаевич\nПринял: к.т.н. доцент Юрова О.В.\n\n");
    system("PAUSE");
    system("cls");
    do
    {
        printf("Меню:\n");
        printf("1. Создать случайный граф\n");
        printf("2. Ввести граф вручную\n");
        printf("3. Импортировать граф из файла\n");
        printf("4. Сохранить граф в файл\n");
        printf("5. Просмотреть граф\n");
        printf("6. Найти критические пути (Флойд-Уоршелл)\n");
        printf("7. Выход\n");
        printf("Введите ваш выбор: ");
        choice = inputNumber();

        switch (choice) {
        case 1:
            printf("Введите количество вершин: ");
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
            printf("Введите имя файла: ");
            scanf("%s", filename);
            if (g.matrix) free_matrix(g.matrix, g.vertices);
            g = import_graph(filename);
            break;
        case 4:
            printf("Введите имя файла: ");
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
            printf("До свидания!");
            break;
        default:
            printf("Неверный выбор. Повторите попытку.\n");
            break;
        }
    } 
    while (choice != 7);

    return 0;
}
