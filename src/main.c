#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "file.h"
#include "matrix.h"
#include "fibonacci.h"


// Function prototype.
void clearConsole();


/*
 *  Shows menu for operations.
 *
 *  @return             whether everything worked successfully.
 */
int main()
{
    char filename[CHAR_MAX];
    int rows, cols, option = 0;

    clearConsole();
    printf("Welcome to the route calculator!\n");

    do
    {
        printf("Choose an option:\n"
               "1 - Calculate route from file.\n"
               "2 - Generate random file and calculate route.\n"
               "3 - Exit.\n"
               "Option: ");

        option = 0;
        scanf("%d", &option);
        flush_in();

        switch (option)
        {
            case 1:
                printf("Type the filename: ");
                scanf("%s", filename);
                flush_in();

                int **matrix = readFileIntoMatrix(filename, &rows, &cols);

                if (!matrix)
                {
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;

                }

                int **flagMatrix = initializeMatrix(rows, cols);

                if (!flagMatrix)
                {
                    printf("\nPress ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
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

                if (found)
                {
                    printf("\n\nPath has been found!\n"
                           "Path: \n");
                    printPath(flagMatrix, rows, cols);

                    printf("\n\nFlag matrix:\n\n");
                    printFlagMatrix(flagMatrix, rows, cols);
                }
                else
                {
                    printf("\n\nImpossible to find a path!");
                }

                printf("\n\nPress ENTER to continue...");
                getchar();
                clearConsole();
                break;
            case 2:
                printf(" ");

                char *filepath = generateRandomFile(&rows, &cols);

                if (!filepath)
                {
                    printf("\nERROR: Couldn't generate the random file.");
                    continue;
                }

                int **randomMatrix = readFileIntoMatrix(filepath, &rows, &cols);

                if (!randomMatrix)
                {
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
                }

                int **flagRandomMatrix = initializeMatrix(rows, cols);

                if (!flagRandomMatrix)
                {
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
                }

                found = false;

                for (int i = 0; i < cols; i++)
                {
                    if (randomMatrix[0][i] == 1)
                    {
                        flagRandomMatrix[0][i] = 1;
                        if (move(0, i, rows, cols, randomMatrix, flagRandomMatrix, 1))
                        {
                            found = true;
                            break;
                        }
                    }
                }

                printf("\nMatrix:\n");
                printMatrix(randomMatrix, rows, cols);

                printf("\nPress ENTER to continue...");
                getchar();

                if (found)
                {
                    printf("\n\nPath has been found!\n");
                    printf("\nPath: \n");
                    printPath(flagRandomMatrix, rows, cols);
                    printf("\n\nFlag matrix:\n");
                    printFlagMatrix(flagRandomMatrix, rows, cols);
                }
                else
                {
                    printf("\n\nImpossible to find a path!\n\n");
                }

                printf("\nPress ENTER to continue...");
                getchar();
                clearConsole();
                break;
            case 3:
                printf("Exiting... \n");
                printf("Bye!\n");
                exit(0);

            default:
                clearConsole();
                break;
        }
    } while (option != 3);

    return 0;
}


/*
 *  Clears console based on user's OS.
 */
void clearConsole()
{
#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif
}