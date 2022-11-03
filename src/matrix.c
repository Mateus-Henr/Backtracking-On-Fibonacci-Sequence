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
 *  Moves through matrix looking for a path that follows the real Fibonacci sequence.
 *
 *  @param      currLine      current line in the matrix.
 *  @param      currCol       current column in the matrix.
 *  @param      rows          total number of rows in the matrix.
 *  @param      cols          total number of columns in the matrix.
 *  @param      matrix        pointer to a matrix.
 *  @param      flag          pointer to a flag matrix.
 *  @param      matrix        term position in the real Fibonacci sequence.
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
            flag[currLine + 1][currCol] = n + 1;
            found = move(currLine + 1, currCol, rows, cols, matrix, flag, n + 1);
        }
        if (currCol > 0 && matrix[currLine][currCol - 1] == realFibonacciSequence(n + 1) &&
            flag[currLine][currCol - 1] == 0 && !found)
        {
            flag[currLine][currCol - 1] = n + 1;
            found = move(currLine, currCol - 1, rows, cols, matrix, flag, n + 1);
        }
        if (currCol < cols - 1 && matrix[currLine][currCol + 1] == realFibonacciSequence(n + 1) &&
            flag[currLine][currCol + 1] == 0 && !found)
        {
            flag[currLine][currCol + 1] = n + 1;
            found = move(currLine, currCol + 1, rows, cols, matrix, flag, n + 1);
        }
        if (currLine > 0 && matrix[currLine - 1][currCol] == realFibonacciSequence(n + 1) &&
            flag[currLine - 1][currCol] == 0 && !found)
        {
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
 *  Prints flag matrix out.
 *
 *  @param     matrix     pointer to matrix.
 *  @param     rows       number of rows in the matrix.
 *  @param     cols       number of columns in the matrix.
 */
void printFlagMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 0)
            {
                printf("\033[1;31m");
                printf("%02d  ", matrix[i][j]);
                printf("\033[0m");
            }
            else
            {
                printf("\033[1;32m");
                printf("%02d  ", matrix[i][j]);
                printf("\033[0m");
            }
        }

        printf("\n");
    }
}


/*
 *  Prints matrix out.
 *   
 *   @param     matrix     pointer to matrix.
 *   @param     rows       number of rows in the matrix.
 *   @param     cols       number of columns in the matrix.
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


/*
 *  Prints path.
 *
 *  @param     flagMatrix     pointer to flag matrix.
 *  @param     rows           number of rows in the matrix.
 *  @param     cols           number of columns in the matrix.
 */
void printPath(int **flagMatrix, int rows, int cols)
{
    int path = 0, x = 0, y = 0;
    for (int i = 0; i < cols; i++)
    {
        y = i;
        if (flagMatrix[x][i] == 1)
        {
            printf("[%d %d] \n", x + 1, y + 1);
            path++;
            break;
        }
    }

    do
    {
        if (x < rows - 1 && flagMatrix[x + 1][y] == path + 1)
        {
            printf("[%d %d]\n", x + 1 + 1, y + 1);
            x++;
            path++;
        }
        else if (y > 0 && flagMatrix[x][y - 1] == path + 1)
        {
            printf("[%d %d]\n", x + 1, y);
            y--;
            path++;
        }
        else if (y < cols - 1 && flagMatrix[x][y + 1] == path + 1)
        {
            printf("[%d %d]\n", x + 1, y + 1 + 1);
            y++;
            path++;
        }
        else if (x > 0 && flagMatrix[x - 1][y] == path + 1)
        {
            printf("[%d %d]\n", x, y + 1);
            x--;
            path++;
        }
    } while (x != rows - 1);
}