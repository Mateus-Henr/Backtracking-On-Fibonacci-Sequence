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
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option.\n\n\n");
            system("clear");
            break;
        }
    }while(option != 3);
    return 0;
}
