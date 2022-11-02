#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "file.h"
#include "matrix.h"
#include "fibonacci.h"




int main()
{
    
    // Main program
    char filename[CHAR_MAX];
    int rows, cols , option = 0;
    system("clear");
    printf("Welcome to the route calculator!\n");

    do{
        printf("Choose an option:\n");
        printf("1 - Calculate route from file.\n");
        printf("2 - Generate random file and calculate route.\n");
        printf("3 - Exit.\n");
        printf("Option: ");
        int option = 0;
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
                    getchar(); system("clear");
                    break;
                    
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

            if (found)
            {
                printf("\n\nPath has been found!\n");
                printf("Path: \n");
                printPath(flagMatrix, rows, cols);  
                printf("\n\nFlag matrix:\n\n");
                printFlagMatrix(flagMatrix, rows, cols);
            }
            else
            {
                printf("\n\nImpossible to find a path!");
            }
            printf("\nPress ENTER to continue...");
            getchar();
            system("clear");

        break;
        case 2:
            generateFile();
            printf("Press ENTER to continue...");
            getchar();
            system("clear");
            break;
        case 3:
            printf("Exiting... \n");
            printf("Bye!\n");
            exit(0);
        default:
            system("clear");
            break;
        }
    }while(option != 3);
    return 0;
}
