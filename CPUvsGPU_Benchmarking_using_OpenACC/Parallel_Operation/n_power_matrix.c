#include "operations.h"
#include <math.h>

#include "matrixSize.h"
void powerMatrix(int** matrix, int n, int** result) {
    // Parallelize the outer loop
    #pragma acc parallel loop
    for (int i = 0; i < N; i++) {
        // Parallelize the inner loop
        #pragma acc loop
        for (int j = 0; j < M; j++) {
            result[i][j] = pow(matrix[i][j], n);
        }
    }
}

