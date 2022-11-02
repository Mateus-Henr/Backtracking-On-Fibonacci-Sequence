#ifndef BACKTRACKING_ON_FIBONACCI_SEQUENCE_F_H
#define BACKTRACKING_ON_FIBONACCI_SEQUENCE_F_H
#endif

#include <stdbool.h>

int **initializeMatrix(int rows, int cols);

bool move(int currLine, int currCol, int rows, int cols, int **matrix, int **flag, int n);

void printFlagMatrix(int **matrix, int rows, int cols);

void printMatrix(int **matrix, int rows, int cols);

void printPath(int **flagMatrix, int rows, int cols);
