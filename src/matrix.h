#ifndef BACKTRACKING_ON_FIBONACCI_SEQUENCE_F_H
#define BACKTRACKING_ON_FIBONACCI_SEQUENCE_F_H
#endif

#include <stdbool.h>

int **initializeMatrix(int rows, int cols);

bool isThereAPath(int **matrix, int **flagMatrix, int rows, int cols, int *totalRec, int *maxRec);

void printFlagMatrix(int **matrix, int rows, int cols);

void printMatrix(int **matrix, int rows, int cols);

void printPath(int **flagMatrix, int rows, int cols);
