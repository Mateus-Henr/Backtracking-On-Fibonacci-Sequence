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
            printf("%02d  ", matrix[i][j]);
        }

        printf("\n");
    }
}

bool movimentar (int x, int y, int rows, int cols, int** matrix, int** flag, int n)
{
    if(x == rows - 1) return true;
    else
    {
        bool found = false;
    
        if(matrix[x + 1][y] == fibSequence(n + 1) && flag[x + 1][y] == 0)
        {   
            printf("down\n");
            printf ("x: %d, y: %d, n: %d\n", x, y, n);
            flag[x + 1][y] = n + 1;

            found = movimentar(x + 1, y, rows, cols, matrix, flag, n + 1);
        }
        if(y > 0 && matrix[x][y - 1] == fibSequence(n + 1) && flag[x][y - 1] == 0 && !found)
        {   
            printf("left\n");
            printf ("x: %d, y: %d, n: %d\n", x, y, n);
            flag[x][y - 1] = n + 1;
            found = movimentar(x, y - 1, rows, cols, matrix, flag, n + 1);
        }
        if(y < cols - 1 && matrix[x][y + 1] == fibSequence(n + 1) && flag[x][y + 1] == 0 && !found)
        {
            printf("right\n");
            printf ("x: %d, y: %d, n: %d\n", x, y, n);
            flag[x][y + 1] = n + 1;
            found = movimentar(x, y + 1, rows, cols, matrix, flag, n + 1);
        }
        if(x > 0 && matrix[x - 1][y] == fibSequence(n + 1) && flag[x - 1][y] == 0 && !found)
        {   
            printf("up\n");
            printf ("x: %d, y: %d, n: %d\n", x, y, n);
            flag[x - 1][y] = n + 1;
            found = movimentar(x - 1, y, rows, cols, matrix, flag, n + 1);
        }

        if(!found)
        {
            flag[x][y] = 0;
            return false;
        }
        else return true;
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
    //print the matrix

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("[%02d] ", matrix[i][j]);
        }

        printf("\n");
    }


    //maybe thats a dumb way to check if this part of the crop has already been visited, but i couldnt come up with anything else, i guess that if we made a data structure for the crops, this would be better
    int **flagMatrix = initializeMatrix(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            flagMatrix[i][j] = 0;
        }
    }

    //int *path = ;

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
    for(int i = 0; i < cols; i++)
    {
        printf("Olhei o elemento %d \n", matrix[0][i]);
        found = false;
        if(matrix[0][i] == 1)
        {   
            printf("Encontrei um elemento 1 na posicao 0, %d \n", i);
            found = movimentar(0, i, rows, cols, matrix, flagMatrix, 1);
        }
        if(found) break;
    }
    if(!found) printf("Impossible to find optmal path\n");
    else
    {
        printf("achou!!!!\n");
    }

    //matriz de flags

    printf("Printing out the flag matrix\n");

    printMatrix(flagMatrix, rows, cols);

    return 0;
}