#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <limits.h>

int fibonacci(int n)
{
    return (int) (pow(((1 + sqrt(5)) / 2), n) + pow(((1 - sqrt(5)) / 2), n));
}


int **initializeMatrix(int rows, int cols)
{
    int **matrix = (int **) malloc(rows * sizeof(int *));

    if (!matrix)
    {
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }

    return matrix;
}

void printMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("[%02d] ", matrix[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    char filename[CHAR_MAX];

    printf("Type the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("ERROR: Couldn't open the file.");
        return -1;
    }

    int cols, rows;
    fscanf(file, "%d %d", &rows, &cols);

    int **matrix = initializeMatrix(rows, cols);

    if (!matrix)
    {
        return -1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(file, "%d ", &matrix[i][j]);
        }
    }


    int number = 0;

    printf("\nType a number: ");
    scanf("%d", &number);

    printf("\nElement %d: %d", number, fibonacci(number));
    printf("\nSequence of fibonacci, from 0 to %d: ", number);
    for (int i = 0; i <= number; i++)
    {
        printf("%d ", fibonacci(i));
    }

    printf("\nPrinting out the matrix\n");
    printMatrix(matrix, rows, cols);

    return 0;
}

