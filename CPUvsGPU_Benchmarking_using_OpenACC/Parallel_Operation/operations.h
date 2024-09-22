#ifndef OPERATIONS_H
#define OPERATIONS_H

#include<stdlib.h> // usage of stdandrd library
#include<openacc.h>

#include "matrixSize.h" // define the size of matrix

// Function prototypes
void matrixAddition(int** matrix1, int** matrix2, int** result);			// ADDITION
void matrixMultiplication(int** matrix1, int** matrix2, int** result);		// MULTIPLICATION
void matrixSubtraction(int** matrix1, int** matrix2, int** result);			// SUBTRACTION														
int matrixDivision(int** matrix1, int** matrix2, int** result);		        // DIVISION
void matrixTranspose(int** matrix, int** result);							// TRANSPOSE
void rotateMatrix(int** matrix, int** result);								// ROTATE
void powerMatrix(int** matrix, int n, int **result);						// POWER

void generateRandomMatrix(int** matrix, int lower_bound, int upper_bound);	// Generate Random Matrices

#endif

