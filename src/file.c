#include <stdio.h>
#include <stddef.h>
#include "matrix.h"

#include "file.h"


/*
 *  Reads file into matrix and returns initialized matrix.
 *
 *  @param     filename     name of the file.
 *  @param     rows         pointer to an integer that will store the number of rows in the matrix.
 *  @param     cols         pointer to an integer that will store the number of columns in the matrix.
 */
int **readFileIntoMatrix(char *filename, int *rows, int *cols)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("ERROR: Couldn't open the file.\n");
        return NULL;
    }

    fscanf(file, "%d %d", rows, cols);

    if (*rows == 0 || *cols == 0)
    {
        printf("ERROR: Invalid value of number of rows or columns.");
        return NULL;
    }

    int **matrix = initializeMatrix(*rows, *cols);

    if (!matrix)
    {
        printf("ERROR: Couldn't allocate memory for the matrix.");
        return NULL;
    }

    for (int i = 0; i < *rows; i++)
    {
        for (int j = 0; j < *cols; j++)
        {
            fscanf(file, "%d ", &matrix[i][j]);
        }
    }

    fclose(file);
    file = NULL;

    return matrix;
}