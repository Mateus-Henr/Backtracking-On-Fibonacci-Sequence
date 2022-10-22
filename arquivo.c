#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}


int **createMatrix(int rows, int cols, char *filename) {

    int **matrix = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }

    FILE *file = fopen(filename, "r");
    int m, n;
    fscanf(file, "%d %d", &m, &n);

    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

int main() {
    int cols, rows;
    char filename[100];
    FILE *file;

    printf("Digite o nome do arquivo: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf(file, "%d %d", &rows, &cols);
    fclose(file);
    

    int **matrix = createMatrix(rows, cols, filename);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    
    int x;
    printf("Type a number: ");
    scanf("%d", &x);
    printf("\nElement %d: %d", x, fibonacci(x));

    printf("\nSequence of fibonacci, from 0 to %d: ", x);
    for (int i = 0; i <= x; i++) {
        printf("%d ", fibonacci(i));
    }

    printf("\n");

    return 0;





    
 
}

