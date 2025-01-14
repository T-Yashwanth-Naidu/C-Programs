#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

/* Function to compare two integers for qsort */
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/*
This function generates an array with random values and sorts it.
Input:
- size: size of the array to generate
Return:
- int*: Pointer to the dynamically allocated and sorted array
*/
int *generate_and_sort_array(int size)
{
    if (size <= 0)
    {
        fprintf(stderr, "Error: Invalid size for array. Must be a positive integer.\n");
        return NULL;
    }

    // Dynamically allocate memory for the array
    int *array = (int *)malloc(size * sizeof(int));
    if (!array)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    // Fill the array with random values
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 100; // Random values between 0 and 99
    }

    // Sort the array using qsort
    qsort(array, size, sizeof(int), compare);

    return array;
}

/*
This function merges two sorted arrays into a third sorted array using pointers.
Input:
- arr1: pointer to the first sorted array
- size1: size of the first sorted array
- arr2: pointer to the second sorted array
- size2: size of the second sorted array
Output:
- Returns a pointer to the newly created merged sorted array
*/
int *merge_sorted_arrays(int *arr1, int size1, int *arr2, int size2, int *merged_size)
{
    // Allocate memory for the merged array
    int *merged_array = (int *)malloc((size1 + size2) * sizeof(int));
    if (!merged_array)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    int i = 0, j = 0, k = 0;

    // Traverse both arrays and pick the smaller element
    while (i < size1 && j < size2)
    {
        if (arr1[i] <= arr2[j])
        {
            merged_array[k++] = arr1[i++];
        }
        else
        {
            merged_array[k++] = arr2[j++];
        }
    }

    // Copy remaining elements from arr1, if any
    while (i < size1)
    {
        merged_array[k++] = arr1[i++];
    }

    // Copy remaining elements from arr2, if any
    while (j < size2)
    {
        merged_array[k++] = arr2[j++];
    }

    *merged_size = size1 + size2;
    return merged_array;
}

int main(int argc, char *argv[])
{
    // Validate the number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <size1> <size2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse array sizes from command-line arguments
    errno = 0;
    int size1 = strtol(argv[1], NULL, 10);
    int size2 = strtol(argv[2], NULL, 10);

    if (errno != 0 || size1 <= 0 || size2 <= 0)
    {
        fprintf(stderr, "Error: Array sizes must be positive integers.\n");
        return EXIT_FAILURE;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate and sort the arrays
    int *arr1 = generate_and_sort_array(size1);
    int *arr2 = generate_and_sort_array(size2);

    // Handle cases where arrays could not be created
    if (!arr1 || !arr2)
    {
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    // Print the generated arrays
    printf("Array 1: ");
    for (int i = 0; i < size1; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("Array 2: ");
    for (int i = 0; i < size2; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // Merge the arrays
    int merged_size = 0;
    int *merged_array = merge_sorted_arrays(arr1, size1, arr2, size2, &merged_size);

    if (!merged_array)
    {
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    // Print the merged array
    printf("Merged Array: ");
    for (int i = 0; i < merged_size; i++)
    {
        printf("%d ", merged_array[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(arr1);
    free(arr2);
    free(merged_array);

    return EXIT_SUCCESS;
}
