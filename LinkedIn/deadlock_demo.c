/*
 * Program to Demonstrate Deadlock
 *
 * This program simulates a deadlock scenario where two threads
 * compete for two shared resources (represented as mutexes).
 * Each thread locks one resource and then tries to lock the other,
 * resulting in a circular wait and hence a deadlock.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

// Global mutex variables representing shared resources
pthread_mutex_t resource1;
pthread_mutex_t resource2;

/**
 * Thread 1 function
 * Locks Resource 1 first, then attempts to lock Resource 2.
 * This simulates one side of the circular wait condition for a deadlock.
 */
void *thread1(void *arg) {
  printf("Thread 1: Trying to lock Resource 1\n");
  pthread_mutex_lock(&resource1);
  printf("Thread 1: Locked Resource 1. Sleeping for 3 seconds.\n");
  sleep(3);

  printf("Thread 1: Trying to lock Resource 2\n");
  pthread_mutex_lock(&resource2);
  printf("Thread 1: Locked Resource 2\n");

  // Unlock resources after use (if deadlock doesn't occur)
  pthread_mutex_unlock(&resource2);
  printf("Thread 1: Unlocked Resource 2\n");

  pthread_mutex_unlock(&resource1);
  printf("Thread 1: Unlocked Resource 1\n");

  return NULL;
}

/**
 * Thread 2 function
 * Locks Resource 2 first, then attempts to lock Resource 1.
 * This simulates the other side of the circular wait condition for a deadlock.
 */
void *thread2(void *arg) {
  printf("Thread 2: Trying to lock Resource 2\n");
  pthread_mutex_lock(&resource2);
  printf("Thread 2: Locked Resource 2. Sleeping for 3 seconds.\n");
  sleep(3);

  printf("Thread 2: Trying to lock Resource 1\n");
  pthread_mutex_lock(&resource1);
  printf("Thread 2: Locked Resource 1\n");

  // Unlock resources after use (if deadlock doesn't occur)
  pthread_mutex_unlock(&resource1);
  printf("Thread 2: Unlocked Resource 1\n");

  pthread_mutex_unlock(&resource2);
  printf("Thread 2: Unlocked Resource 2\n");

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
