/*
Given an array of integers A and an integer B. Find the total number of
subarrays having bitwise XOR of all elements equal to K.

Detailed Explanation:
--------------------------------------
1. XOR is associative and commutative: A ^ B ^ C = C ^ B ^ A.
2. If the XOR of the first i elements is X and the XOR of the first j elements
   is Y (with j > i), then the XOR of the subarray A[i+1]...A[j] is X ^ Y.
3. If we need the XOR of a subarray to be K, the relationship can be written as:
   X ^ K = Y, or equivalently, Y ^ K = X.
4. Using this relationship, we maintain a running XOR of the array elements
   while storing the frequency of previously seen XOR values in a hashmap.
5. This enables efficient determination of the count of subarrays with XOR K.

Algorithm:
--------------------------------------
1. Traverse the array while maintaining a running XOR of elements.
2. For each element, calculate the target XOR (current XOR ^ K).
3. Use a hashmap to check if this target XOR exists in the previously seen XORs.
4. Increment the count for each occurrence of the target XOR in the hashmap.
5. Update the hashmap with the current XOR to include it in future calculations.

Complexity:
--------------------------------------
Time Complexity: O(N), where N is the size of the array, as each element is
processed once, and hashmap operations are O(1) on average.
Space Complexity: O(N), for storing the frequencies of XOR values in the
hashmap.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure for the hashmap to handle collisions
typedef struct HashNode {
  int xor_value;         // The XOR value
  int count;             // Frequency of the XOR value
  struct HashNode *next; // Pointer to the next node for collision resolution
} HashNode;

// Define the size of the hashmap (using a prime number for better distribution)
#define HASH_SIZE 101

// Global hashmap to store frequencies of XOR values
HashNode *hash_map[HASH_SIZE] = {NULL};

// Function to calculate the hash index for a given key
// Ensures non-negative indices even for negative keys
int hash_function(int key) { return (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE; }

// Function to insert a key into the hashmap or update its count
void insert_or_update(int key, int value) {
  int hash_index = hash_function(key); // Get the hash index
  HashNode *node = hash_map[hash_index];

  // Traverse the linked list to find the key
  while (node != NULL) {
    if (node->xor_value == key) { // Key found
      node->count += value;       // Update the count
      return;
    }
    node = node->next;
  }

  // Key not found, create a new node and insert it at the beginning
  HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
  new_node->xor_value = key;
  new_node->count = value;
  new_node->next = hash_map[hash_index];
  hash_map[hash_index] = new_node;
}

// Function to get the frequency of a key from the hashmap
// Returns 0 if the key is not found
int get_count(int key) {
  int hash_index = hash_function(key); // Get the hash index
  HashNode *node = hash_map[hash_index];

  // Traverse the linked list to find the key
  while (node != NULL) {
    if (node->xor_value == key) { // Key found
      return node->count;
    }
    node = node->next;
  }
  return 0; // Key not found
}

// Function to free the memory allocated for the hashmap
void free_hashmap() {
  for (int i = 0; i < HASH_SIZE; i++) {
    HashNode *node = hash_map[i];
    while (node != NULL) {
      HashNode *temp = node;
      node = node->next;
      free(temp); // Free each node in the linked list
    }
    hash_map[i] = NULL; // Reset the hashmap entry to NULL
  }
}

// Function to count subarrays with XOR equal to K and print them
int count_subarrays_with_xor(int *arr, int n, int k) {
  int current_xor = 0; // Running XOR of elements
  int count = 0;       // Count of subarrays with XOR equal to K

  // Insert the initial XOR value (0) into the hashmap
  insert_or_update(0, 1);

  printf("Subarrays with XOR %d:\n", k);

  // Traverse the array
  for (int i = 0; i < n; i++) {
    current_xor ^= arr[i]; // Update the running XOR

    // Calculate the target XOR
    int target_xor = current_xor ^ k;

    // Check if the target XOR exists in the hashmap
    count += get_count(target_xor);

    // Print the corresponding subarrays
    if (get_count(target_xor) > 0) {
      for (int j = 0; j <= i; j++) {
        int temp_xor = 0;
        for (int x = j; x <= i; x++) {
          temp_xor ^= arr[x];
        }
        if (temp_xor == k) {
          printf("[");
          for (int x = j; x <= i; x++) {
            printf("%d", arr[x]);
            if (x < i)
              printf(", ");
          }
          printf("], ");
        }
      }
    }

    // Update the hashmap with the current XOR
    insert_or_update(current_xor, 1);
  }

  printf("\n"); // End the subarray list output
  return count;
}

int main() {
  int n, k;

  // Input the size of the array and the target XOR value
  printf("Enter the size of the array: ");
  scanf("%d", &n);
  printf("Enter the value of K: ");
  scanf("%d", &k);

  // Seed the random number generator
  srand(time(NULL));

  // Dynamically allocate memory for the array
  int *arr = (int *)malloc(n * sizeof(int));
  if (!arr) {
    printf("Memory allocation failed!\n");
    return -1;
  }

  // Populate the array with random integers in the range [0, 9]
  printf("Generated Array: ");
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % 10;
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Calculate the result
  int result = count_subarrays_with_xor(arr, n, k);

  // Output the total count of subarrays
  printf("Total number of subarrays with XOR equal to %d: %d\n", k, result);

  // Free allocated memory
  free(arr);
  free_hashmap();

  return 0;
}
