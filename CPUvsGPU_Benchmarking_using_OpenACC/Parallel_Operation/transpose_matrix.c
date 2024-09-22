#include "operations.h"
#include "matrixSize.h"

void matrixTranspose(int** matrix, int** result) {
     //#pragma acc data copyin(matrix[0:N][0:M]) copyout(result[0:M][0:N])
     //{
        #pragma acc parallel loop collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result[j][i] = matrix[i][j];
            }
        }
   // }
}
