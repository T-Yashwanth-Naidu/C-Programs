#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
// Function definition
unsigned int* createArray(unsigned int Range) {
    if (Range == 0) {
        fprintf(stderr, "Range cannot be zero\n");
        return NULL;
    }

    unsigned int* array = malloc(Range * sizeof(unsigned int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    unsigned int i = 0;
    while (i < Range) {
        array[i] = i++;
    }

    return array;
}

// Test cases for createArray
int main() {
    unsigned int Range;
    unsigned int* array;

    // Test Case 1: Normal case
    Range = 10;
    printf("Test Case 1: Normal Case (Range = %u)\n", Range);
    array = createArray(Range);
    if (array != NULL) {
        for (unsigned int i = 0; i < Range; i++) {
            printf("%u ", array[i]);
        }
        printf("\n");
        free(array);
    } else {
        printf("Memory allocation failed for Test Case 1\n");
    }

    // Test Case 2: Range = 0
    Range = 0;
    printf("\nTest Case 2: Edge Case (Range = %u)\n", Range);
    array = createArray(Range);
    if (array == NULL) {
        printf("Memory allocation correctly failed for Range = 0\n");
    }

    // Test Case 3: Very large Range (potential overflow)
    Range = UINT_MAX / 2;  // Adjust depending on system limits
    printf("\nTest Case 3: Large Range (Range = %u)\n", Range);
    array = createArray(Range);
    if (array == NULL) {
        printf("Memory allocation failed as expected for large Range\n");
    } else {
        printf("Memory allocation succeeded (unexpected for this test case)\n");
        free(array);
    }

    // Test Case 4: Medium Range (boundary test)
    Range = 100000;  // A value that doesn't overflow but is still significant
    printf("\nTest Case 4: Medium Range (Range = %u)\n", Range);
    array = createArray(Range);
    if (array != NULL) {
        printf("Memory allocation succeeded for medium range (printing first 10 elements):\n");
        for (unsigned int i = 0; i < 10; i++) {  // Print only the first 10 elements for sanity
            printf("%u ", array[i]);
        }
        printf("\n");
        free(array);
    } else {
        printf("Memory allocation failed for Test Case 4\n");
    }

    return 0;
}
