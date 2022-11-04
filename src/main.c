#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "file.h"
#include "matrix.h"
#include "fibonacci.h"

#define INC(x) CAT(INC_, x)


// Function prototype.

void clearConsole();


/*
 *  Shows menu for operations.
 *
 *  @return             whether everything worked successfully.
 */
int main()
{
    clearConsole();
    printf("Welcome to the path finder!\n");

    while (true)
    {
        char userFilepath[CHAR_MAX];
        int rows = 0, cols = 0, option = 0, maxRec = 0, totalRec = 0, choice = 0;
        int **matrix = NULL, **flagMatrix = NULL;

        printf("\nMenu\n"
               "1 - Calculate path from file.\n"
               "2 - Generate random file and calculate path.\n"
               "3 - Exit.\n"
               "Choose an option:\n");
        scanf("%d", &option);
        flushIn();

        switch (option)
        {
            case 1:
                printf("Type the filepath: ");
                scanf("%s", userFilepath);
                flushIn();

                matrix = readFileIntoMatrix(userFilepath, &rows, &cols);

                if (!matrix)
                {
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
                }

                flagMatrix = initializeMatrix(rows, cols);

                if (!flagMatrix)
                {
                    printf("\nPress ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
                }

                printf("\nMatrix:\n");
                printMatrix(matrix, rows, cols);

                printf("\nPress ENTER to continue...");
                getchar();

                if (isThereAPath(matrix, flagMatrix, rows, cols, &totalRec, &maxRec))
                {
                    printf("\n\nPath has been found!\n\nPath: \n");
                    printPath(flagMatrix, rows, cols);

                    printf("\n\nFlag matrix:\n\n");
                    printFlagMatrix(flagMatrix, rows, cols);
                }
                else
                {
                    printf("\n\nImpossible to find a path!");
                }

                printf("\n\nWould you like to know the recursion analysis?\n"
                       "1 - Yes\n"
                       "Any other key - No\n");
                scanf("%d", &choice);
                flushIn();

                if (choice == 1)
                {
                    printf("\nTotal recursions: %d\nMax recursion: %d\n", totalRec, maxRec);
                }

                
                printf("\n\nPress ENTER to continue...");
                getchar();
                clearConsole();
                break;
            case 2:
                printf("Generating random file.");

                char *filepath = generateRandomFile(&rows, &cols);

                if (!filepath)
                {
                    printf("\nERROR: Couldn't generate the random file.");
                    break;
                }

                matrix = readFileIntoMatrix(filepath, &rows, &cols);

                if (!matrix)
                {
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
                }

                flagMatrix = initializeMatrix(rows, cols);

                if (!flagMatrix)
                {
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearConsole();
                    break;
                }

                printf("\nMatrix:\n");
                printMatrix(matrix, rows, cols);

                printf("\nPress ENTER to continue...");
                getchar();

                if (isThereAPath(matrix, flagMatrix, rows, cols, &totalRec, &maxRec))
                {
                    printf("\n\nPath has been found!\n\nPath: \n");
                    printPath(flagMatrix, rows, cols);
                    printf("\n\nFlag matrix:\n");
                    printFlagMatrix(flagMatrix, rows, cols);
                }
                else
                {
                    printf("\n\nImpossible to find a path!\n\n");
                }

                printf("\n\nWould you like to know the recursion analysis?\n"
                       "1 - Yes\n"
                       "Any other key - No\n");
                scanf("%d", &choice);
                flushIn();

                if (choice == 1)
                {
                    printf("\nTotal recursions: %d\nMax recursion: %d\n", totalRec, maxRec);
                }

                printf("\nPress ENTER to continue...");
                getchar();
                clearConsole();
                break;
            case 3:
                printf("Exiting... \nBye!\n");
                return 0;

            default:
                clearConsole();
                break;
        }
    }
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