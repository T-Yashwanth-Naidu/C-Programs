#include "operations.h"
#include "matrixSize.h"

void matrixMultiplication(int** matrix1, int** matrix2, int **result) {
    // Parallelize the outer two loops
    //#pragma acc parallel loop collapse(2)
    #pragma acc parallel loop
    for (int i = 0; i < N; i++) {
        #pragma acc loop
        for (int j = 0; j < M; j++) {
            int sum = 0;  // Use a local variable to accumulate the sum

            // Innermost loop - not parallelized, but vectorized
            #pragma acc loop reduction(+:sum)
            for (int k = 0; k < M; k++) { // Assuming square matrices, so we can use M here
                sum += matrix1[i][k] * matrix2[k][j];
            }

            result[i][j] = sum;
        }
    }
}

