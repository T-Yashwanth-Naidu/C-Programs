#include <stdio.h>
#include <time.h>
#include "operations.h"
#include "matrixSize.h"

// Uncomment the following to print the matrices

// #define DEBUG_PROG


// Function to print an integer matrix
void printIntMatrix(int **matrix) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

// For Timing Calculation
double timespec_diff(struct timespec *start, struct timespec *end) {
    struct timespec temp;
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        temp.tv_sec = end->tv_sec - start->tv_sec - 1;
        temp.tv_nsec = 1e9 + end->tv_nsec - start->tv_nsec;
    } else {
        temp.tv_sec = end->tv_sec - start->tv_sec;
        temp.tv_nsec = end->tv_nsec - start->tv_nsec;
    }
    return (double)temp.tv_sec + (double)temp.tv_nsec / 1e9;
}


int main() {

	
	struct timespec start_time, end_time;
	double time_taken_to_execute;
	srand(time(NULL));



	printf("Matrix Operations that are performed in this Matrix Calculator\n");
	printf("1. Addition\n");
	printf("2. Subtraction\n");
	printf("3. Multiplication\n");
	printf("4. Division\n");
	printf("5. Transpose of Matrix 1\n");
	printf("6. Rotate Matrix 1 (90-degree clockwise)\n");
	printf("7. Raise elements of Matrix 1 to power n\n");


	// Memory allocation for the matrices
	int** matrix1 = (int**) malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++) {
		matrix1[i] = (int*) malloc(M * sizeof(int));
	}

	int** matrix2 = (int**) malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++) {
		matrix2[i] = (int*) malloc(M * sizeof(int));
	}

	int** intResult = (int**) malloc(N * sizeof(int*));
	for (int i = 0; i < M; i++) {
		intResult[i] = (int*) malloc(M * sizeof(int));
	}

	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MATRIX GENERATION START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	// Generate two random matrices with values between 1 and 25
	clock_gettime(CLOCK_MONOTONIC, &start_time);

	generateRandomMatrix(matrix1, 1, 9);
	generateRandomMatrix(matrix2, 1, 9);	

	printf("\nMatrix 1 and Matrix 2 are Generated:\n");



#ifdef DEBUG_PROG
	printf("\nMatrix 1:\n");
	printIntMatrix(matrix1);
    printf("\nMatrix 2:\n");
    printIntMatrix(matrix2);
    printf("\n\n");
#endif

	clock_gettime(CLOCK_MONOTONIC, &end_time);
	time_taken_to_execute = timespec_diff(&start_time, &end_time);	
	printf("Time taken to Generate the Matrices: %lf\n", time_taken_to_execute);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MATRIX GENERATION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

 //#pragma acc data copy(matrix1[0:N][0:M], matrix2[0:N][0:M], intResult[0:N][0:M])
   {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADDITION START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Perform matrix Addition
	clock_gettime(CLOCK_MONOTONIC, &start_time);

	matrixAddition(matrix1, matrix2, intResult);
	clock_gettime(CLOCK_MONOTONIC, &end_time);


	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nTime taken for Addition: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
	printIntMatrix(intResult);
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADDITION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SUBTRACTION START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Perform matrix subtraction
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	
	matrixSubtraction(matrix1, matrix2, intResult);
	
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	
	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nTime taken to Subtraction: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
	printIntMatrix(intResult);
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SUBTRACTION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MULTIPLICATION START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Perform matrix multiplication
	
	clock_gettime(CLOCK_MONOTONIC, &start_time);	

	matrixMultiplication(matrix1, matrix2, intResult);

	clock_gettime(CLOCK_MONOTONIC, &end_time);
	

	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nTime taken for Multiplication: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
	printIntMatrix(intResult);
	printf("\n");
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MULTIPLICATION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//#pragma acc data copy(matrix1[0:N][0:M], matrix2[0:N][0:M], intResult[0:N][0:M])
   {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DIVISION START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Perform matrix division
	
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	
	if(matrixDivision(matrix1, matrix2, intResult)) {
	} 
	else {
		printf("\nDivision by zero detected. Operation not performed.\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	
	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nTime taken for Division: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
		printIntMatrix(intResult);
#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DIVISION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TRANSPOSE START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Perform matrix transpose on matrix1

	int** transposedMatrix = (int**) malloc(M * sizeof(int*));
	
	for (int i = 0; i <M; i++) {
		transposedMatrix[i] = (int*) malloc(N * sizeof(int));
	}

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	
	matrixTranspose(matrix1,transposedMatrix);
	
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	
	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nTime taken For Transpose: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
	printIntMatrix(transposedMatrix);
#endif

	for (int i = 0; i < M; i++) {
		free(transposedMatrix[i]);
	}
	free(transposedMatrix); 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TRANSPOSE END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ROTATION START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Perform matrix rotation on matrix1
	
	clock_gettime(CLOCK_MONOTONIC, &start_time);

	rotateMatrix(matrix1, intResult);
	
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	
	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nRotated Matrix 1 (90-degree clockwise)\n");
	printf("\nTime taken to Rotate: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
	printIntMatrix(intResult);
#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ROTATION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ POWER START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Raise each element of matrix1 to a power n
	int n_power = 2;

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	
	powerMatrix(matrix1, n_power, intResult);

	clock_gettime(CLOCK_MONOTONIC, &end_time);
	
	time_taken_to_execute = timespec_diff(&start_time, &end_time);
	printf("\nTime taken for Power: %lf\n", time_taken_to_execute);

#ifdef DEBUG_PROG
	printIntMatrix(intResult);
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ POWER END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	for (int i = 0; i < N; i++) {
		free(matrix1[i]);
	}
	free(matrix1);

	for (int i = 0; i < N; i++) {
		free(matrix2[i]);
	}
	free(matrix2);

	for (int i = 0; i < M; i++) {
		free(intResult[i]);
	}
	free(intResult);




	return 0;
}

