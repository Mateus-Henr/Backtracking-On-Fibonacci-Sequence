#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

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
    int probability = 0;
    srand(time(NULL));

    int rows = rand() % 15 + 1;
    int cols = rand() % 15 + 1;

    printf("\nNumber of rows: %d\n", rows);
    printf("Number of columns: %d\n", cols);

    char filename[CHAR_MAX];

    sprintf(filename, "test-%d-%d.txt", rows, cols);

    printf("Generated file %s\n ", filename);
    

    FILE *file = fopen(filename, "w");

    fprintf(file, "%d %d \n", rows, cols);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            probability = rand() % 100 + 1;
            if(probability <= 30){
                fprintf(file, "%d ", getNthTermFromFibonacci(1));
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
    printf("\nPress any key to continue...");
    getchar();
            
    if (found)
        {
        printf("\n\nPath has been found!\n");
        printf("Path: \n");

        int path = 0, x = 0, y = 0;
        for (int i = 0; i < cols; i++)
        {
            y = i;
            if (flagMatrix[x][i] != 0)
                {
                    printf("[%d %d] \n", x+1, y+1);
                    path++;
                    break;
                }
        }
                
        do{
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
        }while (x != rows - 1);    
        printf("\n\nFlag matrix:\n");
        printFlagMatrix(flagMatrix, rows, cols);
    }
    else
    {
        printf("\n\nImpossible to find a path!\n");
    }
}
/*
* Free buffer
*/

void flush_in() { 
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}