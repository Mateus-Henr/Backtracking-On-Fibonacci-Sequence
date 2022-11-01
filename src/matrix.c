#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "fibonacci.h"

#include "matrix.h"


/*
 *  Initializes a matrix with a given number of columns and lines.
 *
 *  @param     rows       number of rows in the matrix.
 *  @param     cols       number of columns in the matrix.
 *  @return               pointer to initialized matrix.
 */
int **initializeMatrix(int rows, int cols)
{
    int **matrix = (int **) malloc(rows * sizeof(int *));

    if (!matrix)
    {
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *) calloc(cols, sizeof(int));
    }

    return matrix;
}


/*
 *  Searches for sequence.
 */
bool move(int currLine, int currCol, int rows, int cols, int **matrix, int **flag, int n)
{
    if (currLine == rows - 1) { return true; }
    else
    {
        bool found = false;

        if (matrix[currLine + 1][currCol] == realFibonacciSequence(n + 1) &&
            flag[currLine + 1][currCol] == 0)
        {
            printf("down\n");
            printf("currLine: %d, currCol: %d, n: %d\n", currLine, currCol, n);
            flag[currLine + 1][currCol] = n + 1;

            found = move(currLine + 1, currCol, rows, cols, matrix, flag, n + 1);
        }
        if (currCol > 0 && matrix[currLine][currCol - 1] == realFibonacciSequence(n + 1) &&
            flag[currLine][currCol - 1] == 0 && !found)
        {
            printf("left\n");
            printf("currLine: %d, currCol: %d, n: %d\n", currLine, currCol, n);
            flag[currLine][currCol - 1] = n + 1;
            found = move(currLine, currCol - 1, rows, cols, matrix, flag, n + 1);
        }
        if (currCol < cols - 1 && matrix[currLine][currCol + 1] == realFibonacciSequence(n + 1) &&
            flag[currLine][currCol + 1] == 0 && !found)
        {
            printf("right\n");
            printf("currLine: %d, currCol: %d, n: %d\n", currLine, currCol, n);
            flag[currLine][currCol + 1] = n + 1;
            found = move(currLine, currCol + 1, rows, cols, matrix, flag, n + 1);
        }
        if (currLine > 0 && matrix[currLine - 1][currCol] == realFibonacciSequence(n + 1) &&
            flag[currLine - 1][currCol] == 0 && !found)
        {
            printf("up\n");
            printf("currLine: %d, currCol: %d, n: %d\n", currLine, currCol, n);
            flag[currLine - 1][currCol] = n + 1;
            found = move(currLine - 1, currCol, rows, cols, matrix, flag, n + 1);
        }

        if (!found)
        {
            flag[currLine][currCol] = 0;
            return false;
        }

        return true;
    }
}


/*
 *  Prints matrix out.
 *
 *  @param     matrix     pointer to matrix.
 *  @param     rows       number of rows in the matrix.
 *  @param     cols       number of columns in the matrix.
 */
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
