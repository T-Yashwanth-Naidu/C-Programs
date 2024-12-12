/*
Aim is to create a custom circular buffer which will be used in another project.

The circular buffer is commonly also known as a Ring Buffer. We will be creating
a fixed-sized buffer that will be used in a producer-consumer problem.

Its functionalities should include:
- Fixed-size buffer.
- Maintains a continuous loop of indices that can be manipulated using
arithmetic.
- Indices (in and out) should wrap around to the beginning when they reach the
buffer's end, utilizing modular arithmetic (index = index % buffer_size).

Behavior:
- Items are added in FIFO order at the producer end.
- Items are consumed in the same (FIFO) order at the consumer end.

- Multiple producers and consumers should be able to access the data without
data corruption.
- We will be using Mutex to achieve the above.

Thread-Safe Design:

Enqueue:
- The Producer should:
    - Wait if the buffer is full.
    - Add an item to the next available slot.
    - Update the `in` pointer to the next position.

Dequeue:
- The Consumer should:
    - Wait if the buffer is empty.
    - Retrieve an item from the buffer.
    - Update the `out` pointer to the next position.

Synchronization with Semaphores:

    - Empty semaphore: Tracks available empty slots for producers.
    - Full semaphore: Tracks filled slots available for consumers.

Blocking:

- Producers:
    - Block (wait) when the buffer is full until a consumer removes an item.

- Consumers:
    - Block (wait) when the buffer is empty until a producer adds an item.

Debugging:
- Add LOG statements wrapped in the DEBUG macro.

The Complete Workflow:

Initialization:
- Define the buffer as an array and initialize the `in` and `out` indices to 0.
- Set up mutex locks and semaphores with appropriate initial values.

Add Item (Producer):
- Wait on the empty semaphore.
- Lock the mutex to ensure exclusive access.
- Add the item at the `in` index.
- Increment `in` using modular arithmetic.
- Unlock the mutex and signal the full semaphore.

Remove Item (Consumer):
- Wait on the full semaphore.
- Lock the mutex to ensure exclusive access.
- Remove the item at the `out` index.
- Increment `out` using modular arithmetic.
- Unlock the mutex and signal the empty semaphore.

Example Buffer States:
- Initial State: Empty buffer, `in = 0`, `out = 0`.
- After Enqueue: Buffer contains one or more items, `in` moves forward.
- After Dequeue: Buffer empties progressively, `out` moves forward.
*/

#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
Step 1: What do I need?

- A buffer storage to store the values.
- Since buffers are of limited size, let us consider the page size of the
system: 256 bytes.
- Each element in the array should store one item.
- The size of the buffer is fixed.
- Since we need to read and write, we will use 2 pointers:
    - A `read` variable - Tracks the position where the next item will be added.
    - A `write` variable - Tracks the position where the next item will be
removed.
- Track the total number of items in the buffer.
- A mutex so that only one thread accesses the buffer at a time.
- 2 semaphores:
    - 1 to track empty slots.
    - 1 to track filled slots.
- Create a structure that has all of the above attributes.
*/

#define DEBUG

#define BUFFER_SIZE 256

struct circularBuffer {
  int buffer[BUFFER_SIZE]; // Fixed-size buffer (size aligns with page size)
  int in;                  // Pointer to the current write position
  int out;                 // Pointer to the current read position
  int bufferSize;          // Stores the total buffer size
  pthread_mutex_t mutex;   // Mutex for synchronization
  sem_t semFull;           // Semaphore for tracking filled slots
  sem_t semEmpty;          // Semaphore for tracking empty slots
};

typedef struct circularBuffer circularBuffer; // To Ease readability.

/*
Step 2: Initialize the structure
- I need to call this function in `main` to initialize the structure with
default values.
- I don’t need to return anything, but I need to pass the structure object from
`main` whose values are to be initialized.
*/

void cb_init(circularBuffer *initCircularBuffer) {

  int mutex_init_result;
  int sem_init_result_empty;
  int sem_init_result_full;
  int sem_value;

  initCircularBuffer->in = 0;  // Starts at Beginning
  initCircularBuffer->out = 0; // Starts at Beginning
  initCircularBuffer->bufferSize = BUFFER_SIZE;
  mutex_init_result =
      pthread_mutex_init(&initCircularBuffer->mutex, NULL); // Exclusive access
  sem_init_result_empty = sem_init(
      &initCircularBuffer->semEmpty, 0,
      BUFFER_SIZE); // The buffer should be empty. All the slots are available.
  sem_init_result_full =
      sem_init(&initCircularBuffer->semFull, 0, 0); // Contains no items yet.

#ifdef DEBUG
  printf("\ncb_init: Called cb_init function to Initialize the structure with "
         "follwing values\n");

  printf("cb_init: - Value of in: %d \n", initCircularBuffer->in);
  printf("cb_init: - Value of out: %d \n", initCircularBuffer->out);
  printf("cb_init: - Value of bufferSize: %d \n",
         initCircularBuffer->bufferSize);

  // Check Mutex Initialization
  if (mutex_init_result != 0) {
    fprintf(stderr, "cb_init: Error initializing mutex: %d\n",
            mutex_init_result);
  } else {
    printf("cb_init: Mutex initialized successfully.\n");
  }

  // Check Semaphore Initialization for semEmpty
  if (sem_init_result_empty != 0) {
    fprintf(stderr, "cb_init: Error initializing semEmpty: %d\n",
            sem_init_result_empty);
  } else {
    sem_getvalue(&initCircularBuffer->semEmpty, &sem_value);
    printf("cb_init: semEmpty initialized with value: %d\n", sem_value);
  }

  // Check Semaphore Initialization for semFull
  if (sem_init_result_full != 0) {
    fprintf(stderr, "cb_init: Error initializing semFull: %d\n",
            sem_init_result_full);
  } else {
    sem_getvalue(&initCircularBuffer->semFull, &sem_value);
    printf("cb_init: semFull initialized with value: %d\n", sem_value);
  }

#endif

  // In case the Mutex or Semaphore Initializations fail:
  if (mutex_init_result != 0) {
    fprintf(stderr,
            "cb_init: Critical Error: Mutex initialization failed with code "
            "%d. Exiting.\n",
            mutex_init_result);
    exit(EXIT_FAILURE);
  }

  if (sem_init_result_empty != 0) {
    fprintf(stderr,
            "cb_init: Critical Error: Empty Semaphore initialization failed "
            "with code %d. Exiting.\n",
            sem_init_result_empty);
    exit(EXIT_FAILURE);
  }

  if (sem_init_result_full != 0) {
    fprintf(stderr,
            "cb_init: Critical Error: Full Semaphore initialization failed "
            "with code %d. Exiting.\n",
            sem_init_result_full);
    exit(EXIT_FAILURE);
  }
}

/*
Step 3: We are done with initializations. Let’s start with the Producer
function, i.e., Enqueue.

The function’s functionality:

- This function should add items into the buffer in a thread-safe manner.

- Ensure that there is at least one empty slot.
- Block the producer if the buffer is full.
- If a slot is available, acquire the mutex and add the item to the buffer.
    - Place the item at the `in` index.
    - Update the `in`.
- Release the mutex after modifying the buffer.
- Increment the `semFull` to notify the consumer that an item is available.

- It should not return anything.
- It should take in the object (the buffer itself) and the item to add.
*/

void cb_enqueue(circularBuffer *cb, int item) {

  // Ensure the cb is not NULL.
  if (cb == NULL) {
    fprintf(stderr, "cb_enqueue: Error: Circular buffer is NULL.\n");
    return;
  }

#ifdef DEBUG
  // Recording the function entry.
  printf("cb_enqueue: cb_enqueue called with item: %d\n", item);

  int sem_value;
  sem_getvalue(&cb->semEmpty, &sem_value);
  printf("cb_enqueue: semEmpty value before wait: %d\n", sem_value);
#endif

  // Check if atleast one slot is empty.  Block until the slot is empty
  sem_wait(&cb->semEmpty); // sem_wait decrements the semEmpty by 1.

#ifdef DEBUG
  printf("cb_enqueue: Mutex locked. Adding item to buffer.\n");
#endif

  // Lock the mutex and add the item.
  pthread_mutex_lock(&cb->mutex);
  cb->buffer[cb->in] = item;

#ifdef DEBUG
  printf("cb_enqueue: Item %d added to buffer at position %d\n", item, cb->in);
#endif

  // Update the index
  /*
  cb_in should be increment to point to the next slot in the buffer.
  cb->bufferSize ensures that the index wraps around the start of the buffer
  when it reaches the end.
  */
  cb->in = (cb->in + 1) % cb->bufferSize;

#ifdef DEBUG
  printf("cb_enqueue: Updated in index to: %d\n", cb->in);
#endif

  // Release the mutex
  pthread_mutex_unlock(&cb->mutex);

#ifdef DEBUG
  printf("cb_enqueue: Mutex unlocked after adding item.\n");
#endif

  // Signal the consumer through semFull

  sem_post(&cb->semFull);

#ifdef DEBUG
  sem_getvalue(&cb->semFull, &sem_value);
  printf("cb_enqueue: semFull value after post: %d\n", sem_value);
  printf("-------------------------------------------\n");
#endif
}
/*
Step 4: Let’s start with the Consumer function, i.e., Dequeue.

The function’s functionality:

- This function should remove items from the buffer in a thread-safe manner.

- Check that there is at least one slot in the buffer. Block the consumer if the
buffer is empty.
- If an item is available in the buffer, acquire the mutex.
    - Access the item at the current `out` index in the buffer.
    - Update the `out` index.
- Release the mutex after safely removing the item.
- Notify the producer that a slot is now available using `semEmpty`.
- Pass the removed item back to the caller.

- The function returns the removed item, an integer.
- It should take in the object (the buffer itself).
*/

int cb_dequeue(circularBuffer *cb) {

  int returnVal;

  // Ensure the cb is not NULL.
  if (cb == NULL) {
    fprintf(stderr, "cb_dequeue: Error: Circular buffer is NULL.\n");
    return -1;
  }

#ifdef DEBUG
  printf("cb_dequeue called\n");
  int sem_value;
  sem_getvalue(&cb->semFull, &sem_value);
  printf("cb_dequeue: semFull value before wait: %d\n", sem_value);
#endif

  // wait on semFull and decrement the semFull if atleast one slot is availble.
  // Block if the buffer is empty.
  sem_wait(&cb->semFull);

#ifdef DEBUG
  printf("cb_dequeue: Mutex locked before retrieving item.\n");
#endif
  // Lock the Mutex and retreive the item.
  pthread_mutex_lock(&cb->mutex);

  returnVal = cb->buffer[cb->out];

#ifdef DEBUG
  printf("cb_dequeue: Item %d removed from buffer at position %d\n", returnVal,
         cb->out);
#endif

  //  Update the 'out' index
  cb->out = (cb->out + 1) % cb->bufferSize;

#ifdef DEBUG
  printf("cb_dequeue: Updated out index to: %d\n", cb->out);
#endif

  // Release the mutex
  pthread_mutex_unlock(&cb->mutex);

#ifdef DEBUG
  printf("cb_dequeue: Mutex unlocked after retrieving item.\n");
#endif

  // Notify the producer that a slot is empty by updating 'semEmpty' .
  sem_post(&cb->semEmpty);

#ifdef DEBUG
  sem_getvalue(&cb->semEmpty, &sem_value);
  printf("cb_dequeue: semEmpty value after post: %d\n", sem_value);
  printf("-------------------------------------------\n");
#endif

  return returnVal;
}

/*
Step 5: TIME TO TEST!

- Write a `main` function with proper initializations and test the `init`,
`enqueue`, and `dequeue` functions.

What should we check for?
    - Producers can add items to the buffer without overwriting existing items.
    - Consumers can remove items from the buffer in the correct order (FIFO).
    - The buffer behaves circularly.

What should the main block include?
    - Initialize the buffer.
    - Separate threads for producer and consumer.
    - Create multiple threads for producers and consumers.
    - In the Producer thread:
        - Generate a random number.
        - Call `cb_enqueue` with the number.
        - Log the item added to the buffer.

    - In the Consumer thread:
        - Call `cb_dequeue` to retrieve an item.
        - Log the item removed from the buffer.

Before we write the `main` function, we need to introduce 2 functions:
`producer` and `consumer`, where the buffer values are allocated.

Let’s do the following testing scenarios:

Single Producer, Single Consumer:
    - Simplest case to validate basic functionality.

Multiple Producers, Single Consumer:
    - Validate synchronization with multiple threads producing simultaneously.

Single Producer, Multiple Consumers:
    - Test consumer synchronization when multiple threads consume from the
buffer.

Multiple Producers, Multiple Consumers:
    - Comprehensive test to validate the system under heavy load.
*/

void *producer(void *arg) {

  circularBuffer *cb = (circularBuffer *)arg;

  for (int i = 0; i < 10; ++i) { // Produce 10 items
    int item = rand() % 100;     // Random item
    cb_enqueue(cb, item);
#ifdef DEBUG
    pthread_t thread_id = pthread_self();
    printf("[Producer-%lu] Added item: %d\n", thread_id, item);
    printf("===========================================\n");
#endif
    sleep(1); // Simulate production time
  }
  return NULL;
}

void *consumer(void *arg) {
  circularBuffer *cb = (circularBuffer *)arg;
  for (int i = 0; i < 10; ++i) { // Consume 10 items
    int item = cb_dequeue(cb);
#ifdef DEBUG
    pthread_t thread_id = pthread_self();
    printf("[Consumer-%lu] Removed item: %d\n", thread_id, item);
    printf("===========================================\n");
#endif
    sleep(1); // Simulate consumption time
  }
  return NULL;
}

int main(void) {

  srand(time(NULL));

  // Create a buffer and initialize the circular buffer.
  circularBuffer cb;
  cb_init(&cb);

  int choice;
  printf("\n=== Select a Scenario to Test ===\n");
  printf("1. Single Producer, Single Consumer\n");
  printf("2. Multiple Producers, Single Consumer\n");
  printf("3. Single Producer, Multiple Consumers\n");
  printf("4. Multiple Producers, Multiple Consumers\n");
  printf("Enter your choice (1-4): ");
  scanf("%d", &choice);

  pthread_t producers[2], consumers[2];
  int i;
  printf("\n=== Running Test Case: ");

  switch (choice) {
  case 1: // Single Producer, Single Consumer
    printf("Running Single Producer, Single Consumer...\n");
    pthread_create(&producers[0], NULL, producer, &cb);
    pthread_create(&consumers[0], NULL, consumer, &cb);
    pthread_join(producers[0], NULL);
    pthread_join(consumers[0], NULL);
    break;

  case 2: // Multiple Producers, Single Consumer
    printf("Running Multiple Producers, Single Consumer...\n");
    for (i = 0; i < 2; ++i) {
      pthread_create(&producers[i], NULL, producer, &cb);
    }
    pthread_create(&consumers[0], NULL, consumer, &cb);
    for (i = 0; i < 2; ++i) {
      pthread_join(producers[i], NULL);
    }
    pthread_join(consumers[0], NULL);
    break;

  case 3: // Single Producer, Multiple Consumers
    printf("Running Single Producer, Multiple Consumers...\n");
    pthread_create(&producers[0], NULL, producer, &cb);
    for (i = 0; i < 2; ++i) {
      pthread_create(&consumers[i], NULL, consumer, &cb);
    }
    pthread_join(producers[0], NULL);
    for (i = 0; i < 2; ++i) {
      pthread_join(consumers[i], NULL);
    }
    break;

  case 4: // Multiple Producers, Multiple Consumers
    printf("Running Multiple Producers, Multiple Consumers...\n");
    for (i = 0; i < 2; ++i) {
      pthread_create(&producers[i], NULL, producer, &cb);
      pthread_create(&consumers[i], NULL, consumer, &cb);
    }
    for (i = 0; i < 2; ++i) {
      pthread_join(producers[i], NULL);
      pthread_join(consumers[i], NULL);
    }
    break;

  default:
    printf("Invalid choice! Exiting.\n");
    break;
  }

  // Free the resources
  pthread_mutex_destroy(&cb.mutex);
  sem_destroy(&cb.semEmpty);
  sem_destroy(&cb.semFull);

  printf("Test completed.\n");

  return 0;
}