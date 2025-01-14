/*
  Parallel Array Merge Using Multithreading

  This program merges two sorted arrays into a single sorted array using multithreading.
  Each element of the resulting merged array is computed by a separate thread, demonstrating
  fine-grained parallelism and thread-safe shared resource access.

  The program is implemented using the following concepts:
  1. Thread-Level Parallelism:
     - Each thread calculates one specific element in the merged array.
     - Threads work independently, distributing the workload across multiple threads.
  2. Dynamic Memory Management:
     - Arrays are dynamically allocated based on user-provided sizes via command-line arguments.
     - The merged array is also dynamically allocated.
  3. Thread Synchronization:
     - A mutex is used to ensure safe updates to the shared `merged_array` resource, 
       preventing race conditions even when multiple threads are working simultaneously.
  4. Sorting and Input Handling:
     - The input arrays are filled with random values, sorted using `qsort`, and printed before merging.

  Key Functions:
  - `compare`: Comparison function for `qsort`, used to sort the arrays in ascending order.
  - `merge_element`: Function executed by each thread to compute one element of the merged array.
     It uses mutex locks to ensure safe updates to the shared `merged_array`.

  Usage Example:
  The program takes two arguments as input:
  - `size1`: Size of the first array.
  - `size2`: Size of the second array.

  Example command-line usage:
./program 5 4
This generates two sorted arrays of sizes 5 and 4, respectively, and merges them using threads.

Output:
- Prints the two sorted arrays.
- Prints the final merged array.

Features Demonstrated:
- Multithreading and thread synchronization using pthreads and mutex.
- Dynamic memory management and safe resource cleanup.
- Parallel computation of individual elements in the merged array.

Limitations:
- Overhead of thread creation and synchronization might outweigh the benefits for small array sizes.
- Maximum number of threads is limited by system resources.

Notes:
- The program uses mutexes for thread safety, though the design ensures that threads operate
  on unique indices of the merged array. Mutex usage is a precaution for future modifications.
- The program requires `pthread` support for compilation and execution.
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to pass arguments to threads
typedef struct {
    int *arr1;            // Pointer to the first sorted array
    int size1;            // Size of the first sorted array
    int *arr2;            // Pointer to the second sorted array
    int size2;            // Size of the second sorted array
    int *merged_array;    // Pointer to the merged array where the result will be stored
    int index;            // Index of the element to compute in the merged array
    pthread_mutex_t *mutex; // Pointer to a mutex to ensure thread-safe access to the merged array
} ThreadArgs;

/*
 * This function is executed by each thread to compute one element of the merged array.
 * It determines which value should occupy the specified index in the merged array.
 * Input:
 *   - args: A pointer to a ThreadArgs structure containing the data required for computation
 */
void *merge_element(void *args) {
    ThreadArgs *data = (ThreadArgs *)args; // Cast the void pointer to ThreadArgs
    int i = 0, j = 0, k = 0; // i: index for arr1, j: index for arr2, k: current merged index

    // Traverse both arrays until we reach the specified index in the merged array
    while (k <= data->index) {
        // Compare elements from both arrays to decide which one goes into the merged array
        if (i < data->size1 && (j >= data->size2 || data->arr1[i] <= data->arr2[j])) {
            if (k == data->index) { // When we reach the target index
                pthread_mutex_lock(data->mutex); // Lock the mutex to ensure thread safety
                data->merged_array[data->index] = data->arr1[i]; // Assign the value from arr1
                pthread_mutex_unlock(data->mutex); // Unlock the mutex
                break;
            }
            i++; // Move to the next element in arr1
        } else {
            if (k == data->index) { // When we reach the target index
                pthread_mutex_lock(data->mutex); // Lock the mutex to ensure thread safety
                data->merged_array[data->index] = data->arr2[j]; // Assign the value from arr2
                pthread_mutex_unlock(data->mutex); // Unlock the mutex
                break;
            }
            j++; // Move to the next element in arr2
        }
        k++; // Increment the merged index
    }
    pthread_exit(NULL); // Exit the thread
}

/*
 * Comparison function for qsort, used to sort the arrays in ascending order.
 * Input:
 *   - a: Pointer to the first element
 *   - b: Pointer to the second element
 * Output:
 *   - Returns a negative value if a < b, 0 if a == b, positive if a > b
 */
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    // Validate command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <size1> <size2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse array sizes from the command-line arguments
    int size1 = atoi(argv[1]); // Size of the first array
    int size2 = atoi(argv[2]); // Size of the second array

    // Validate the parsed sizes
    if (size1 <= 0 || size2 <= 0) {
        fprintf(stderr, "Array sizes must be positive integers.\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL)); // Seed the random number generator for random array values

    // Dynamically allocate memory for the two arrays
    int *arr1 = (int *)malloc(size1 * sizeof(int));
    int *arr2 = (int *)malloc(size2 * sizeof(int));
    if (!arr1 || !arr2) { // Check if memory allocation succeeded
        perror("Memory allocation failed");
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    // Fill the arrays with random numbers and sort them using qsort
    for (int i = 0; i < size1; i++) arr1[i] = rand() % 1000; // Random values between 0 and 999
    for (int i = 0; i < size2; i++) arr2[i] = rand() % 1000;
    qsort(arr1, size1, sizeof(int), compare); // Sort the first array
    qsort(arr2, size2, sizeof(int), compare); // Sort the second array

    // Print the sorted arrays
    printf("Array 1: ");
    for (int i = 0; i < size1; i++) printf("%d ", arr1[i]);
    printf("\n");

    printf("Array 2: ");
    for (int i = 0; i < size2; i++) printf("%d ", arr2[i]);
    printf("\n");

    // Dynamically allocate memory for the merged array
    int merged_size = size1 + size2; // Size of the merged array
    int *merged_array = (int *)malloc(merged_size * sizeof(int));
    if (!merged_array) { // Check if memory allocation succeeded
        perror("Memory allocation failed");
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    // Initialize an array of threads and thread arguments
    pthread_t threads[merged_size]; // Array of thread handles
    ThreadArgs thread_args[merged_size]; // Array of argument structures for each thread
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Initialize the mutex

    // Create a thread for each element of the merged array
    for (int i = 0; i < merged_size; i++) {
        thread_args[i] = (ThreadArgs){arr1, size1, arr2, size2, merged_array, i, &mutex};
        if (pthread_create(&threads[i], NULL, merge_element, &thread_args[i]) != 0) {
            perror("Thread creation failed");
            free(arr1);
            free(arr2);
            free(merged_array);
            return EXIT_FAILURE;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < merged_size; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the merged array
    printf("Merged Array: ");
    for (int i = 0; i < merged_size; i++) printf("%d ", merged_array[i]);
    printf("\n");

    // Clean up dynamically allocated memory and destroy the mutex
    free(arr1);
    free(arr2);
    free(merged_array);
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS; // Indicate successful program termination
}
