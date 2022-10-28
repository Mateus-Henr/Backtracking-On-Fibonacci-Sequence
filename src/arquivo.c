#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

int fibonacci(int n)
{
    // i couldnt find out why, but for some reason this formula is returning 0 for n = 2, probably something with how those math functions work in c, lets let it as it is for now, its working nevertheless
    if (n == 2) return 1;
    else return (int) (((1 / sqrt(5)) * (pow(((1 + sqrt(5)) / 2), n))) - ((1 / sqrt(5)) * (pow(((1 - sqrt(5)) / 2), n))));
}

int triangular(int n)
{
    return (n * (n + 1)) / 2;
}

int fibSequence(int n)
{
    int k = 0;
    while (n > triangular(k)) k++;
    return fibonacci(n - triangular(k - 1));
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

void movimentar (int x, int y, int rows, int cols, int** matrix, int** flag, int n)
{
    bool possibleMove = false;
    if(x > 0)
    {
        if(matrix[x - 1][y] == fibSequence(n + 1) && flag[x - 1][y] == 0)
        {
            possibleMove = true;
            flag[x - 1][y] = 1;
            movimentar(x - 1, y, rows, cols, matrix, flag, n + 1);
        }
    }
    if(x < rows - 1)
    {
        if(matrix[x + 1][y] == fibSequence(n + 1) && flag[x + 1][y] == 0)
        {
            possibleMove = true;
            flag[x + 1][y] = 1;
            movimentar(x + 1, y, rows, cols, matrix, n);
        }
    }
    if(y > 0)
    {
        if(matrix[x][y - 1] == fibSequence(n + 1) && flag[x][y - 1] == 0)
        {
            possibleMove = true;
            flag[x][y - 1] = 1;
            movimentar(x, y - 1, rows, cols, matrix, n);
        }
    }
    if(y < cols - 1)
    {
        if(matrix[x][y + 1] == fibSequence(n + 1) && flag[x][y + 1] == 0)
        {
            possibleMove = true;
            flag[x][y + 1] = 1;
            movimentar(x, y + 1, rows, cols, matrix, n);
        }
    }
}

int main()
{
    for (int i = 1; i < 22; i++) printf("%d\n", fibSequence(i));

    char filename[CHAR_MAX];

    printf("Type the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("ERROR: Couldn't open the file.\n");
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

    //maybe thats a dumb way to check if this part of the crop has already been visited, but i couldnt come up with anything else, i guess that if we made a data structure for the crops, this would be better
    bool **flagMatrix = initializeMatrix(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            flagMatrix[i][j] = 0;
        }
    }

    /*int number = 0;

    printf("\nType a number: ");
    scanf("%d", &number);

    printf("\nElement %d: %d", number, fibonacci(number));
    printf("\nSequence of fibonacci, from 0 to %d: ", number);
    for (int i = 0; i <= number; i++)
    {
        printf("%d ", fibonacci(i));
    }

    printf("\nPrinting out the matrix\n");
    printMatrix(matrix, rows, cols);*/

    // finds somewhere to start the harvest in the borders of the crops
    bool found = false;
    for(int i = 0; i < rows; i++)
    {
        if(i == 0 || i == rows - 1)
        {
            for(int j = 0; j < cols; j++)
            {
                if(matrix[i][j] == 1)
                {
                    movimentar(i, j, rows, cols, matrix, flagMatrix, 1);
                    found = true;
                }
            }
        }
        else
        {
            for(int j = 0; j < cols; j += cols - 1)
            {
                if(matrix[i][j] == 1)
                {
                    movimentar(i, j, rows, cols, matrix, flagMatrix, 1);
                    found = true;
                }
            }
        }
    }
    if(!found) printf("Impossible to find optmal path\n");

    return 0;
}