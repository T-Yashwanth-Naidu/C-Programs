#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to pass arguments to threads
typedef struct {
  int *arr;               // Pointer to the array
  uint64_t size;          // Size of the array
  int start;              // Start index for the thread
  int end;                // End index for the thread
  int *writeIndex;        // Pointer to the write index (shared among threads)
  pthread_mutex_t *mutex; // Pointer to a mutex to ensure thread safety
} ThreadArgs;

/*
 * Thread function to move non-zero elements to the end of the array.
 * Input:
 *   - args: A pointer to a ThreadArgs structure containing thread-specific
 * data.
 */
void *moveNonZeroToEnd(void *args) {
  ThreadArgs *data = (ThreadArgs *)args;

  for (int i = data->start; i <= data->end; i++) {
    if (data->arr[i] != 0) {
      pthread_mutex_lock(data->mutex);
      data->arr[*(data->writeIndex)] = data->arr[i];
      (*(data->writeIndex))--;
      pthread_mutex_unlock(data->mutex);
    }
  }

  pthread_exit(NULL);
}

/*
 * Main function to move zeros to the left using multithreading.
 */
void moveZerosToLeftMultithreaded(int *arr, uint64_t size, int num_threads) {
  if (arr == NULL || size == 0)
    return;

  int writeIndex = size - 1; // Shared write index for non-zero elements
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_t threads[num_threads];
  ThreadArgs thread_args[num_threads];

  int chunk_size = size / num_threads;
  int start = 0;

  // Create threads for parallel processing
  for (int i = 0; i < num_threads; i++) {
    int end = (i == num_threads - 1) ? size - 1 : start + chunk_size - 1;

    thread_args[i] = (ThreadArgs){arr, size, start, end, &writeIndex, &mutex};

    if (pthread_create(&threads[i], NULL, moveNonZeroToEnd, &thread_args[i]) !=
        0) {
      perror("Thread creation failed");
      pthread_mutex_destroy(&mutex);
      return;
    }

    start = end + 1;
  }

  // Wait for all threads to complete
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  // Fill the remaining positions on the left with zeros
  while (writeIndex >= 0) {
    arr[writeIndex--] = 0;
  }

  pthread_mutex_destroy(&mutex);
}

int main(void) {
  uint64_t size;
  int num_threads;

  // Input: Array size and number of threads
  printf("Enter the size of the array: ");
  if (scanf("%lu", &size) != 1 || size <= 0) {
    fprintf(stderr, "Invalid size entered. Exiting.\n");
    return EXIT_FAILURE;
  }

  printf("Enter the number of threads: ");
  if (scanf("%d", &num_threads) != 1 || num_threads <= 0) {
    fprintf(stderr, "Invalid number of threads entered. Exiting.\n");
    return EXIT_FAILURE;
  }

  // Dynamically allocate memory for the array
  int *arr = (int *)malloc(size * sizeof(int));
  if (!arr) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }

  // Seed the random number generator and fill the array with random values
  srand(time(NULL));
  for (uint64_t i = 0; i < size; i++) {
    arr[i] = rand() % 10; // Random values between 0 and 9
  }

  // Print the original array
  printf("Original array:\n");
  for (uint64_t i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Move zeros to the left using multithreading
  moveZerosToLeftMultithreaded(arr, size, num_threads);

  // Print the modified array
  printf("Array after moving zeros to the left:\n");
  for (uint64_t i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Free dynamically allocated memory
  free(arr);

  return EXIT_SUCCESS;
}
