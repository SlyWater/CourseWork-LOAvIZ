#include "functions.h"

int n = 4, o = 0, w = 0;
int** G = NULL;

void startDijkstra() {
    if (G) {
        int s;
        system("cls");
        printG(G, n);
        printf("Введите вершину входа (от 0 до %d): ", n - 1);
        scanf("%d", &s);
        while ((0 > s) || (s >= n)) {
            printf("от 0 до %d: ", n - 1);
            scanf("%d", &s);
        }

        Vertex* dist = (Vertex*)malloc(sizeof(Vertex) * n);
        dijkstra(G, n, dist, s);
        printf("  ");
        for (int i = 0; i < n; ++i) printf("%2d ", i);
        printf("\nS ");
        for (int i = 0; i < n; ++i) {
            if (dist[i].distance < INT_MAX) printf("%2d ", dist[i].distance);
            else printf(" - ");
        }
        printf("\n");
        free(dist);
        system("pause");
    }
    else {
        printf("Матрицы смежности нет\n");
    }
}

void changeGen() {
    int choice = 1;
    char ch;
    while (choice) {
        system("cls");
        printf("Граф ");
        (o) ? printf("ориентированный ") : printf("неориентированный ");
        (w) ? printf("и взвешенный\n") : printf("и невзвешенный\n");
        printf("Кол-во вершин графа: %d\n", n);

        printf("Выберите действие:\n");
        printf("1. Ориентированный %c\n", (o) ? '+' : '-');
        printf("2. Взвешенный %c\n", (w) ? '+' : '-');
        printf("3. Изменить размер\n");
        printf("0. Назад\n");
        printf("Введите номер действия: ");

        scanf("%d", &choice);
        switch (choice) {
        case 1:
            o = !o;
            break;
        case 2:
            w = !w;
            break;
        case 3:
            system("cls");
            printf("Введите количество вершин графа: ");
            scanf("%d", &n);
            break;
        }
    }
}

void createMatrix() {
    if (w) G = createGOW(n);
    else G = createGO(n);
    if (!o) mirG(G, n);
    printG(G, n);
}

void openFromFile() {
    char filename[128];
    printf("Введите название файла для открытия\nФайл должен быть в формате .csv: ");
    scanf("%s", filename);
    G = open_from_file(filename, &n);
}

void saveToFile() {
    if (G) {
        char filename[128];
        printf("Введите название файла для сохранения\nФайл будет сохранен в формате .csv: ");
        scanf("%s", filename);
        save_to_file(G, n, filename);
    }
    else {
        printf("Матрицы смежности нет\n");
    }
}

void printGraph() {
    if (G) {
        printG(G, n);
    }
    else {
        printf("Матрицы смежности нет\n");
    }
}

int get_choice() {
    void (*functions[])(void) = { createMatrix, changeGen, startDijkstra, openFromFile, saveToFile, printGraph };
    int choice;
    system("cls");
    printf("Выберите действие:\n");
    printf("1. Сгенерировать матрицу смежности\n");
    printf("2. Просмотреть и изменить параметры генерации\n");
    printf("3. Запустить алгоритм\n");
    printf("4. Открыть матрицу смежности из csv-файла\n");
    printf("5. Сохранить в csv-файл\n");
    printf("6. Вывести матрицу смежности\n");
    printf("0. Выход\n");

    printf("Введите номер действия: ");
    scanf("%d", &choice);
    clearb();

    if (choice >= 1 && choice <= sizeof(functions) / sizeof(functions[0])) {
        functions[choice - 1]();
        clearb();
    }
    else if (!choice) {
        system("cls");
        printf("Выход\n");
        return 0;
    }
    return 1;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    int choice = 1;
    while (choice) {
        choice = get_choice();
    }
    return 0;
}