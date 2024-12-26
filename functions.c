#include "functions.h"

int** createGOW(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            G[i][j] = (rand() % 2) ? rand() % 10 : 0;
            G[j][i] = (i == j) ? 0 : G[j][i];
        }
    }
    return G;
}

int** createGO(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[j][i];
        }
    }
    return G;
}

void mirG(int** G, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            G[j][i] = G[i][j];
        }
    }
}

void printG(int** G, int size) {
    system("cls");
    printf("  ");
    for (int i = 0; i < size; ++i) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int compare(const void* a, const void* b) {
    return ((Vertex*)a)->distance - ((Vertex*)b)->distance;
}

void dijkstra(int** G, int size, Vertex* dist, int s) {
    for (int i = 0; i < size; ++i) {
        dist[i].distance = INT_MAX;
        dist[i].vertex = i;
        dist[i].visited = 0;
    }
    dist[s].distance = 0;

    Vertex* pq = (Vertex*)malloc(size * sizeof(Vertex));
    int pq_size = 0;

    pq[pq_size++] = dist[s];

    while (pq_size > 0) {
        qsort(pq, pq_size, sizeof(Vertex), compare);
        Vertex current = pq[0];
        for (int i = 1; i < pq_size; ++i) {
            pq[i - 1] = pq[i];
        }
        pq_size--;

        int u = current.vertex;

        if (dist[u].visited) continue;
        dist[u].visited = 1;

        for (int v = 0; v < size; ++v) {
            if (G[u][v] > 0 && !dist[v].visited) {
                if (dist[u].distance + G[u][v] < dist[v].distance) {
                    dist[v].distance = dist[u].distance + G[u][v];
                    pq[pq_size++] = dist[v];
                }
            }
        }
    }

    free(pq);
}

void clearb() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void save_to_file(int** G, int size, const char* filename) {
    char fullFilename[128];
    if (strlen(filename) >= 4 && strcmp(filename + strlen(filename) - 4, ".csv") == 0) {
        snprintf(fullFilename, sizeof(fullFilename), "files/%s", filename);
    }
    else {
        snprintf(fullFilename, sizeof(fullFilename), "files/%s.csv", filename);
    }
    FILE* file = fopen(fullFilename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        getchar();
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(file, "%d", G[i][j]);
            if (j < size - 1) {
                fprintf(file, ";");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Матрица успешно сохранена в файл %s\n", fullFilename);
    getchar();
}

int** open_from_file(const char* filename, int* size) {
    char fullFilename[128];
    const char* dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".csv") == 0) {
        snprintf(fullFilename, sizeof(fullFilename), "files/%s", filename);
    }
    else {
        dot = strrchr(filename, '.');
        if (dot) {
            printf("Ошибка: файл должен иметь расширение .csv!\n");
            return NULL;
        }
        else {
            snprintf(fullFilename, sizeof(fullFilename), "files/%s.csv", filename);
        }
    }

    FILE* file = fopen(fullFilename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s для чтения!\n", fullFilename);
        getchar();
        return NULL;
    }

    int rowCount = 0;
    int colCount = 0;
    char line[1024];

    if (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        while (token) {
            colCount++;
            token = strtok(NULL, ";");
        }
        rowCount++;
    }

    while (fgets(line, sizeof(line), file)) {
        rowCount++;
    }

    if (rowCount != colCount) {
        printf("Ошибка: матрица в файле не квадратная!\n");
        fclose(file);
        getchar();
        return NULL;
    }

    rewind(file);

    int** matrix = (int**)malloc(rowCount * sizeof(int*));
    for (int i = 0; i < rowCount; ++i) {
        matrix[i] = (int*)malloc(rowCount * sizeof(int));
    }

    for (int i = 0; i < rowCount; ++i) {
        if (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ";");
            for (int j = 0; j < rowCount; ++j) {
                if (token) {
                    matrix[i][j] = atoi(token);
                    token = strtok(NULL, ";");
                }
                else {
                    printf("Ошибка: недостаточно данных в строке %d!\n", i + 1);
                    fclose(file);
                    getchar();
                    return NULL;
                }
            }
        }
        else {
            printf("Ошибка: недостаточно строк в файле!\n");
            fclose(file);
            getchar();
            return NULL;
        }
    }

    fclose(file);
    *size = rowCount;
    printf("Матрица успешно загружена из файла %s\n", fullFilename);
    getchar();
    return matrix;
}
