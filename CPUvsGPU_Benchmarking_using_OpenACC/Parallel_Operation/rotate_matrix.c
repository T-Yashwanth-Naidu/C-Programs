#include "operations.h"
#include "matrixSize.h"

void rotateMatrix(int** matrix, int** result) {
    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result[j][N - 1 - i] = matrix[i][j];
        }
    }
    
}

