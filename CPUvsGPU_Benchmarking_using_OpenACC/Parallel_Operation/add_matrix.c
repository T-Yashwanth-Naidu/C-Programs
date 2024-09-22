#include "operations.h"

#include "matrixSize.h"

// Matrix addition function
void matrixAddition(int** matrix1, int** matrix2, int** result) {
    #pragma acc parallel loop
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

