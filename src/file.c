#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "matrix.h"
#include "fibonacci.h"
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

/*
 * Generate a random File for testing.
 * Numbers of rows, columns and the aij element of the matrix is ​​generated randomly.
 */

int generateFile()
{
    bool found = false;
    srand(time(NULL));

    int rows = rand() % 8 + 1;
    int cols = rand() % 25 + 1;

    printf("\nNumber of rows: %d\n", rows);
    printf("Number of columns: %d\n", cols);

    char filename[CHAR_MAX];
    char folder[CHAR_MAX] = "tests/";
    
    sprintf(filename, "test-%d-%d.txt", rows, cols);

    strcat(folder, filename);

    FILE *file = fopen(folder, "w");

    fprintf(file, "%d %d \n", rows, cols);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int probability = rand() % 100 + 1;

            if(probability <= 30){
                fprintf(file, "%d ", getNthTermFromFibonacci(rand() % 2 + 1));
            }

            else if (probability <= 50){
                fprintf(file, "%d ", getNthTermFromFibonacci(rand() % 5 + 1));
            }

            else if (probability <= 70){
                fprintf(file, "%d ", getNthTermFromFibonacci( rand () % 6 + 1));
            }

            else{
                fprintf(file, "%d ", getNthTermFromFibonacci(rand () % 8 + 1));
            }

        }
        fprintf(file, "\n");
    }
    fclose(file);

    int **matrix = readFileIntoMatrix( folder, &rows, &cols);

    if (!matrix) return -1;
    

    int **flagMatrix = initializeMatrix(rows, cols);

    if (!flagMatrix) return -1;

    for (int i = 0; i < cols; i++)
    {
        if (matrix[0][i] == 1)
        {
            flagMatrix[0][i] = 1;
            if (move(0, i, rows, cols, matrix, flagMatrix, 1))
            {
                found = true;
                break;
            }
        }
    }
            
    printf("\nMatrix:\n");
    printMatrix(matrix, rows, cols);
    printf("\nPress ENTER to continue..."); getchar();
            
    if (found)
        {
        printf("\n\nPath has been found!\n");
        printf("Path: \n");
        printPath(flagMatrix, rows, cols);   
        printf("\n\nFlag matrix:\n");
        printFlagMatrix(flagMatrix, rows, cols);
    }
    else
    {
        printf("\n\nImpossible to find a path!\n");
    }
    return 0;
}

/*
 * Clears the input buffer
 */

void flush_in() { 
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}