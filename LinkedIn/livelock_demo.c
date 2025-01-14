/*
 * Program to Demonstrate Livelock
 *
 * This program simulates a livelock scenario where two threads
 * repeatedly release and retry acquiring shared resources in response
 * to each other's actions. This creates an endless cycle of activity
 * without any progress.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

// Global mutex variables representing shared resources
pthread_mutex_t resource1;
pthread_mutex_t resource2;

// Shared flags to simulate livelock behavior
volatile int thread1_released = 0;
volatile int thread2_released = 0;

/**
 * Thread 1 function
 * Tries to acquire Resource 1 and Resource 2, but releases Resource 1
 * if it notices Thread 2 is also trying to proceed, creating livelock.
 */
void *thread1(void *arg) {
  while (1) {
    printf("Thread 1: Trying to lock Resource 1\n");
    pthread_mutex_lock(&resource1);
    printf("Thread 1: Locked Resource 1\n");

    // Simulate detection of Thread 2 trying to proceed
    if (thread2_released) {
      printf("Thread 1: Detected Thread 2 is waiting. Releasing Resource 1.\n");
      pthread_mutex_unlock(&resource1);
      thread1_released = 1; // Indicate that Thread 1 released the resource
      sleep(1);             // Simulate delay before retrying
      continue;
    }

    printf("Thread 1: Trying to lock Resource 2\n");
    pthread_mutex_lock(&resource2);
    printf("Thread 1: Locked Resource 2\n");

    // If both locks are acquired (unrealistic in livelock), release them
    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);
    printf("Thread 1: Successfully acquired both resources. Exiting.\n");
    break;
  }

  return NULL;
}

/**
 * Thread 2 function
 * Tries to acquire Resource 2 and Resource 1, but releases Resource 2
 * if it notices Thread 1 is also trying to proceed, creating livelock.
 */
void *thread2(void *arg) {
  while (1) {
    printf("Thread 2: Trying to lock Resource 2\n");
    pthread_mutex_lock(&resource2);
    printf("Thread 2: Locked Resource 2\n");

    // Simulate detection of Thread 1 trying to proceed
    if (thread1_released) {
      printf("Thread 2: Detected Thread 1 is waiting. Releasing Resource 2.\n");
      pthread_mutex_unlock(&resource2);
      thread2_released = 1; // Indicate that Thread 2 released the resource
      sleep(1);             // Simulate delay before retrying
      continue;
    }

    printf("Thread 2: Trying to lock Resource 1\n");
    pthread_mutex_lock(&resource1);
    printf("Thread 2: Locked Resource 1\n");

    // If both locks are acquired (unrealistic in livelock), release them
    pthread_mutex_unlock(&resource1);
    pthread_mutex_unlock(&resource2);
    printf("Thread 2: Successfully acquired both resources. Exiting.\n");
    break;
  }

  return NULL;
}

/**
 * Main function
 * Initializes mutexes, creates threads, and cleans up resources.
 */
int main(void) {
  pthread_t t1, t2;

  // Initialize mutexes
  printf("Initializing resources...\n");
  pthread_mutex_init(&resource1, NULL);
  pthread_mutex_init(&resource2, NULL);

  // Create threads
  printf("Creating threads...\n");
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);

  // Wait for threads to finish
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  // Destroy mutexes
  printf("Destroying resources...\n");
  pthread_mutex_destroy(&resource1);
  pthread_mutex_destroy(&resource2);

  printf("Program completed.\n");
  return 0;
}
