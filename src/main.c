#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "file.h"
#include "matrix.h"
#include "fibonacci.h"

int main()
{
    // Testing stuff
    printf("Testing out real fibonacci sequence\n");

    for (int i = 0; i < 20; ++i)
    {
        printf("%d = %d\n", i + 1, realFibonacciSequence(i));
    }

    printf("\n\n");


    // Main program
    char filename[CHAR_MAX];
    int rows, cols = 0;

    printf("Type the filename: ");
    scanf("%s", filename);

    int **matrix = readFileIntoMatrix(filename, &rows, &cols);

    if (!matrix)
    {
        return -1;
    }

    int **flagMatrix = initializeMatrix(rows, cols);

    if (!flagMatrix)
    {
        return -1;
    }

    bool found = false;

    for (int i = 0; i < cols; i++)
    {
        if (matrix[0][i] == 1)
        {
            printf("Found element 1 at position %d \n", i);
            if (move(0, i, rows, cols, matrix, flagMatrix, 1))
            {
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        printf("Impossible to find optimal path.\n");
    }
    else
    {
        printf("Path has been found!\n");
    }

    printf("\n\nFlag matrix\n");
    printMatrix(flagMatrix, rows, cols);

    return 0;
}