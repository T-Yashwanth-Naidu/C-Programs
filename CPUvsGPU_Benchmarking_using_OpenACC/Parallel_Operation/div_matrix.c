#include "operations.h"
#include "matrixSize.h"

// Returns 1 if successful, 0 if division by zero occurred
int matrixDivision(int** matrix1, int** matrix2, int** result) {
    int errorFlag = 0;

    #pragma acc parallel loop private(errorFlag)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix2[i][j] == 0) {
                errorFlag = 1;
            } else {
                result[i][j] = matrix1[i][j] / matrix2[i][j];
            }
        }
    }

    // This check is not parallelized and may not reflect errors in all parallel threads
    // Return 0 if division by zero occurred in any thread
    return errorFlag == 0 ? 1 : 0;
}
