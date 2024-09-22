#include "operations.h"
#include "matrixSize.h"


void generateRandomMatrix(int** matrix, int lower_bound, int upper_bound) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
        }
    }
}

