#include "operations.h"
#include "matrixSize.h"

void matrixMultiplication(int** matrix1, int** matrix2, int **result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result[i][j] = 0;  // Initialize the result cell to 0
          for (int k = 0; k < M; k++) {  // Note: Assuming square matrices, so we can use M here
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

