#include "operations.h"
#include "matrixSize.h"

// Returns 1 if successful, 0 if division by zero occurred
int matrixDivision(int** matrix1, int** matrix2, int** result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(  (matrix2[i][j])  == 0) {
                return 0;  // Division by zero is not allowed
            }
            result[i][j] = matrix1[i][j] / matrix2[i][j];
        }
    }
    return 1;
}

