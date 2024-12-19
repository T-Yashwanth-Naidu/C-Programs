/*
  Hash Table Implementation Using Chaining

  This program implements a hash table data structure in C using chaining.
  Chaining is used to handle collisions by storing multiple key-value pairs
  in a single bucket through a linked list.

  Key Components:p
  - `Node`: Represents each key-value pair, storing the key, value, and a pointer to the next node in the chain.
  - `HashTable`: The hash table containing an array of buckets. Each bucket is a pointer to the head of a linked list.

  Operations:
  - `init_hash_table`: Initializes the hash table, setting all buckets to NULL.
  - `hash_function`: Maps a string key to an integer index for the array.
  - `insert`: Adds a key-value pair to the table or updates the value if the key exists.
  - `search`: Retrieves the value associated with a given key.
  - `delete`: Removes a key-value pair from the table.
  - `free_hash_table`: Frees all allocated memory associated with the hash table.

  Usage Example:
  The `main` function demonstrates the use of hash table operations:
  - Initializes the hash table.
  - Inserts key-value pairs into the hash table.
  - Searches for keys and prints the associated values.
  - Deletes a key from the hash table.
  - Frees the hash table when no longer in use.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TABLE_SIZE 10 // The number of buckets in the hash table

// Node structure for storing a single key-value pair in the hash table
typedef struct Node {
    char *key;         // Pointer to the key string
    int value;         // Associated value for the key
    struct Node *next; // Pointer to the next node in the chain (for collisions)
} Node;

// Hash table structure containing an array of buckets
typedef struct {
    Node *buckets[TABLE_SIZE]; // Array of pointers to the heads of linked lists
} HashTable;

/*
  Initializes the hash table.

  Input:
  - table: Pointer to the HashTable structure to initialize.

  Operation:
  - Sets all bucket pointers to NULL, indicating an empty table.

  Returns: None.
 */
void init_hash_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL; // Initialize each bucket to NULL
    }
}

/*
  Hash function to map a string key to a bucket index.

  Input:
  - key: The string key to hash.
  - table_size: The number of buckets in the hash table.

  Operation:
  - Iterates through the characters in the key, using a simple hash calculation.

  Returns:
  - An integer representing the index of the bucket.
 */
int hash_function(const char *key, int table_size) {
    unsigned long hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % table_size; // Compute hash with a prime multiplier
        key++;
    }
    return hash % table_size; // Ensure the index is within table bounds
}

/*
  Inserts a key-value pair into the hash table.

  Input:
  - table: Pointer to the HashTable structure.
  - key: Pointer to the string key to insert.
  - value: Integer value associated with the key.

  Operation:
  - Computes the bucket index using the hash function.
  - If the key already exists in the table, updates the value.
  - Otherwise, creates a new node and inserts it at the head of the linked list.

  Returns: None.
 */
void insert(HashTable *table, const char *key, int value) {
    int index = hash_function(key, TABLE_SIZE); // Compute the bucket index

    // Traverse the chain to check if the key already exists
    Node *current = table->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) { // Key found
            current->value = value; // Update the value
            return;
        }
        current = current->next;
    }

    // Key not found; create a new node
    Node *new_node = (Node *)malloc(sizeof(Node));
    assert(new_node != NULL && "Memory allocation failed."); // Ensure memory allocation succeeded

    new_node->key = strdup(key); // Copy the key string
    new_node->value = value;     // Assign the value
    new_node->next = table->buckets[index]; // Link the new node to the head of the chain
    table->buckets[index] = new_node; // Update the bucket pointer to the new node
}

/*
  Searches for a key in the hash table.

  Input:
  - table: Pointer to the HashTable structure.
  - key: Pointer to the string key to search for.

  Operation:
  - Computes the bucket index using the hash function.
  - Traverses the linked list at the bucket to find the key.

  Returns:
  - Pointer to the associated value if the key is found, or NULL if not found.
 */
int *search(HashTable *table, const char *key) {
    int index = hash_function(key, TABLE_SIZE); // Compute the bucket index

    Node *current = table->buckets[index]; // Start at the head of the chain
    while (current) {
        if (strcmp(current->key, key) == 0) { // Key found
            return &current->value; // Return a pointer to the value
        }
        current = current->next; // Move to the next node in the chain
    }
    return NULL; // Key not found
}

/*
  Deletes a key-value pair from the hash table.

  Input:
  - table: Pointer to the HashTable structure.
  - key: Pointer to the string key to delete.

  Operation:
  - Computes the bucket index using the hash function.
  - Traverses the linked list to find and remove the node with the matching key.

  Returns:
  - 1 if the key was successfully deleted, or 0 if the key was not found.
 */
int delete(HashTable *table, const char *key) {
    int index = hash_function(key, TABLE_SIZE); // Compute the bucket index

    Node *current = table->buckets[index]; // Start at the head of the chain
    Node *prev = NULL; // Pointer to the previous node (for re-linking)

    while (current) {
        if (strcmp(current->key, key) == 0) { // Key found
            if (prev) {
                prev->next = current->next; // Remove the node from the chain
            } else {
                table->buckets[index] = current->next; // Update the bucket pointer
            }
            free(current->key); // Free the key string
            free(current); // Free the node
            return 1; // Indicate successful deletion
        }
        prev = current; // Move to the next node
        current = current->next;
    }
    return 0; // Key not found
}

/*
  Frees all memory allocated for the hash table.

  Input:
  - table: Pointer to the HashTable structure.

  Operation:
  - Traverses each bucket and frees all nodes in the linked list.

  Returns: None.
 */
void free_hash_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table->buckets[i]; // Start at the head of the chain
        while (current) {
            Node *temp = current; // Temporarily store the current node
            current = current->next; // Move to the next node
            free(temp->key); // Free the key string
            free(temp); // Free the node
        }
        table->buckets[i] = NULL; // Reset the bucket pointer
    }
}

int main() {
    HashTable table;
    init_hash_table(&table); // Initialize the hash table

    // Insert key-value pairs
    insert(&table, "Alice", 25);
    insert(&table, "Bob", 30);
    insert(&table, "Charlie", 35);

    // Search for a key
    int *value = search(&table, "Alice");
    if (value) {
        printf("Alice's value: %d\n", *value);
    } else {
        printf("Alice not found.\n");
    }

    // Delete a key
    if (delete(&table, "Bob")) {
        printf("Bob deleted.\n");
    } else {
        printf("Bob not found.\n");
    }

    // Free the hash table
    free_hash_table(&table);

    return 0;
}