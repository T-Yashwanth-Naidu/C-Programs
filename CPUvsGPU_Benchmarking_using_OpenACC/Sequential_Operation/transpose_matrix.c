#include "operations.h"
#include "matrixSize.h"

void matrixTranspose(int** matrix, int** result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}
