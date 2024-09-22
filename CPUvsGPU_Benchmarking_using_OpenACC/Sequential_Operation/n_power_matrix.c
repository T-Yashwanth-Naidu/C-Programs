#include "operations.h"
#include <math.h>

#include "matrixSize.h"
void powerMatrix(int** matrix, int n, int** result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result[i][j] = pow(matrix[i][j], n);
        }
    }
}

