/*
 * Program: Longest Consecutive Sequence Finder
 
 * Description:
 * This program determines the length of the longest consecutive sequence of integers 
 * in an unsorted array. It utilizes a hash table to efficiently track the presence 
 * of elements, allowing the sequence calculation to run in O(n) time on average.
 *
 * Features:
 * - Supports test cases with predefined or randomly generated inputs.
 * - Handles both positive and negative integers in the array.
 * - Implements proper memory management to prevent memory leaks.
 * Usage:
 * - Define one of the `TEST_CASE` macros to run a specific test case.
 * - The program will compute and display the length of the longest consecutive sequence.
 *
 * Example:
 * Input: {100, 4, 200, 1, 3, 2}
 * Output: Length of the Consecutive sequence is: 4
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 6         // Size of the array
#define DEBUG 0        // Debugging toggle
#define UPPER 10000    // Upper bound for random number generation
#define LOWER -10000   // Lower bound for random number generation

// Define test cases (uncomment to test specific cases)
#define TEST_CASE_1
// #define TEST_CASE_2
// #define TEST_CASE_3
// #define TEST_CASE_4
// #define TEST_CASE_5
//  #define TEST_CASE_RANDOM

// Node structure for linked lists in hash table buckets
struct node {
    int keys;           // The value of the element
    struct node* next;  // Pointer to the next node
};

// Hash table structure
struct hashtable {
    struct node** buckets; // Array of pointers to linked lists
    int size;              // Number of buckets
};

typedef struct node Node;
typedef struct hashtable HashTable;

// Function to initialize the hash table
HashTable* initializeHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        printf("\n(ERROR) Memory allocation failed for HashTable\n");
        return NULL;
    }

    // Allocate memory for the array of buckets
    table->buckets = (Node**)malloc(size * sizeof(Node*));
    if (table->buckets == NULL) {
        printf("\n(ERROR) Memory allocation failed for buckets\n");
        free(table);
        return NULL;
    }

    // Initialize all buckets to NULL
    memset(table->buckets, 0, size * sizeof(Node*));
    table->size = size;

    return table;
}

// Hash function to map keys to bucket indices
int hash(int key, int size) {
    return (key >= 0 ? key : -key) % size; // Handles negative keys
}

// Function to find the length of the longest consecutive sequence
int findLength(int *array, int size) {
    if (array == NULL) {
        printf("\nNo Sequence. Array is empty\n");
        return 0;
    }
    if (size == 0) {
        printf("\nArray size not initialized\n");
        return 0;
    }

    int current_length = 0, max_length = 0;

    // Initialize the hash table
    HashTable* hashSet = initializeHashTable(size);
    if (hashSet == NULL) {
        printf("\n(ERROR) HashTable initialization failed\n");
        return 0;
    }

    // Add all elements to the hash table
    for (int i = 0; i < size; i++) {
        int index = hash(array[i], hashSet->size);

        // Insert the element into the hash table
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("\n(ERROR) Memory allocation for new node failed\n");
            return 0;
        }
        newNode->keys = array[i];
        newNode->next = hashSet->buckets[index];
        hashSet->buckets[index] = newNode;
    }

    // Calculate the longest consecutive sequence
    for (int i = 0; i < size; i++) {
        int num = array[i];

        // Check if num is the start of a sequence
        int index = hash(num - 1, hashSet->size);
        Node* current = hashSet->buckets[index];
        int isStart = 1;

        while (current != NULL) {
            if (current->keys == num - 1) {
                isStart = 0;
                break;
            }
            current = current->next;
        }

        // If num is the start of a sequence, calculate its length
        if (isStart) {
            int current_num = num;
            current_length = 1;

            while (1) {
                index = hash(current_num + 1, hashSet->size);
                current = hashSet->buckets[index];
                int found = 0;

                while (current != NULL) {
                    if (current->keys == current_num + 1) {
                        found = 1;
                        break;
                    }
                    current = current->next;
                }

                if (found) {
                    current_num++;
                    current_length++;
                } else {
                    break;
                }
            }

            // Update max_length if the current sequence is longer
            if (current_length > max_length) {
                max_length = current_length;
            }
        }
    }

    // Free the memory allocated for the hash table
    for (int i = 0; i < hashSet->size; i++) {
        Node* current = hashSet->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashSet->buckets);
    free(hashSet);

    return max_length;
}
int main(void) {
    srand(time(NULL));

    
    int *arrayOfInts =NULL;
    arrayOfInts = (int *)malloc(SIZE * sizeof(int));
    
    #ifdef TEST_CASE_1
    int arrayOfInts1[] = {1, 2, 0, 1, -1, -2}; // Sequence: [-2, -1, 0, 1, 2]
    arrayOfInts = arrayOfInts1;
    printf("Test Case 1: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arrayOfInts[i]);
    printf("\n");
    #endif

    #ifdef TEST_CASE_2
    int arrayOfInts2[] = {100, 4, 200, 1, 3, 2}; // Sequence: [1, 2, 3, 4]
    arrayOfInts = arrayOfInts2;
    printf("Test Case 2: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arrayOfInts[i]);
    printf("\n");
    #endif

    #ifdef TEST_CASE_3
    int arrayOfInts3[] = {5, 7, 6, 10, 8, 9}; // Sequence: [5, 6, 7, 8, 9, 10]
    arrayOfInts = arrayOfInts3;
    printf("Test Case 3: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arrayOfInts[i]);
    printf("\n");
    #endif

    #ifdef TEST_CASE_4
    int arrayOfInts4[] = {-5, -3, -2, -1, 0, 1}; // Sequence: [-5, -3, -2, -1, 0, 1]
    arrayOfInts = arrayOfInts4;
    printf("Test Case 4: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arrayOfInts[i]);
    printf("\n");
    #endif

    #ifdef TEST_CASE_5
    int arrayOfInts5[] = {10, 20, 30, 40, 50, 60}; // No consecutive sequence
    arrayOfInts = arrayOfInts5;
    printf("Test Case 5: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arrayOfInts[i]);
    printf("\n");
    #endif

    #ifdef TEST_CASE_RANDOM
    printf("Generated random array is: \n");
    for (int i = 0; i < SIZE; i++) {
        *(arrayOfInts + i) = (rand() % (UPPER - LOWER + 1)) + LOWER;
        printf("%d ", *(arrayOfInts + i));
    }
    printf("\n");
    #endif

    int lengthOfConsecutiveSequence;
    lengthOfConsecutiveSequence = findLength(arrayOfInts, SIZE);

    printf("\nLength of the Consecutive sequence is: %d",lengthOfConsecutiveSequence );


    
    free(arrayOfInts); // Free allocated memory 
    
    
    return 0;
}
