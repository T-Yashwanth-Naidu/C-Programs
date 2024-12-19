/*
  Queue Implementation Using a Linked List

  This program implements a queue data structure using a linked list.
  A queue is a First-In-First-Out (FIFO) data structure where elements are added to the "rear" of the queue and removed from the "front".

  The queue is implemented using two structures:
  1. `Node`: Represents each element in the queue, containing an integer data field and a pointer to the next node.
  2. `Queue`: Holds pointers to the front and rear nodes of the queue. If the queue is empty, both pointers are set to NULL.

  Key Operations:
  - `init_queue`: Initializes the queue by setting both front and rear pointers to NULL.
  - `is_empty`: Checks if the queue is empty by verifying if the front pointer is NULL.
  - `enqueue`: Adds an element to the rear of the queue. It creates a new node, assigns it the input data, and updates the rear pointer.
  - `dequeue`: Removes an element from the front of the queue. It checks if the queue is empty, retrieves the data from the front node, updates the front pointer, and frees the memory of the old front node.
  - `peek`: Returns the data at the front of the queue without removing it. It checks if the queue is empty before accessing the data.
  - `free_queue`: Frees all nodes in the queue by continuously dequeuing elements until the queue is empty, releasing allocated memory.

  Usage Example:
  The `main` function demonstrates the use of the queue operations:
  - Initializes the queue.
  - Enqueues elements into the queue.
  - Peeks at the front element.
  - Dequeues elements from the queue and prints them.
  - Frees the queue when no longer in use.

  This code also includes assertions to ensure that operations like `dequeue` and `peek` are only performed when the queue is not empty, preventing potential errors such as queue underflow.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Define the Node structure
typedef struct Node {
    int data;          // To store one element
    struct Node *next; // To store the address of the next node
} Node;

// The queue itself is represented by a structure with front and rear pointers
typedef struct {
    Node *front; // Pointer to the front of the queue
    Node *rear;  // Pointer to the rear of the queue
} Queue;

/*
This function initializes the queue.

Input parameters:
- queue: pointer to the Queue structure to initialize

Operation:
- Sets the front and rear pointers to NULL, indicating that the queue is initially empty.

Return: None
*/
void init_queue(Queue *queue) {
    queue->front = queue->rear = NULL;
}

/*
This function checks if the queue is empty.

Input parameters:
- queue: pointer to the Queue structure to check

Operation:
- Returns 1 if the front pointer is NULL (indicating the queue is empty), and 0 otherwise.

Return:
- int: 1 if queue is empty, 0 if not
*/
int is_empty(Queue *queue) {
    return queue->front == NULL;
}

/*
This function adds an element to the rear of the queue.

Input parameters:
- queue: pointer to the Queue structure where the element is to be enqueued
- value: the integer value to be enqueued

Operation:
- Allocates memory for a new node.
- Sets the node's data to the provided value.
- Links the new node to the current rear of the queue.
- Updates the rear pointer to the new node.

Return: None
*/
void enqueue(Queue *queue, int value) {
    Node *newnode = (Node *)malloc(sizeof(Node)); // Allocate memory for a new node
    assert(newnode != NULL && "Memory allocation failed.");

    newnode->data = value;
    newnode->next = NULL; // New node will be the last node, so next is set to NULL

    if (is_empty(queue)) {
        queue->front = queue->rear = newnode; // First element in queue
    } else {
        queue->rear->next = newnode; // Link the new node to the end of the queue
        queue->rear = newnode;       // Update the rear pointer
    }
}

/*
This function removes an element from the front of the queue.

Input parameters:
- queue: pointer to the Queue structure from which the element is to be dequeued

Operation:
- Checks if the queue is empty before proceeding.
- Stores the current front node in a temporary pointer.
- Retrieves the data from the front node.
- Updates the front pointer to the next node in the queue.
- Frees the memory of the old front node.

Return:
- int: the data from the dequeued node
*/
int dequeue(Queue *queue) {
    assert(!is_empty(queue) && "QUEUE IS EMPTY. CANNOT DEQUEUE");

    Node *tempNode = queue->front; // Store the current front node in a temporary pointer
    int data = tempNode->data;     // Retrieve the data from the front node
    queue->front = queue->front->next; // Update the front pointer to the next node

    if (queue->front == NULL) {
        queue->rear = NULL; // If the queue becomes empty, set rear to NULL
    }

    free(tempNode); // Free the memory allocated for the old front node

    return data; // Return the data from the dequeued node
}

/*
This function retrieves the data at the front of the queue without removing it.

Input parameters:
- queue: pointer to the Queue structure from which to peek the front element

Operation:
- Checks if the queue is empty before proceeding.
- Returns the data stored in the front node.

Return:
- int: the data at the front of the queue
*/
int peek(Queue *queue) {
    assert(!is_empty(queue) && "Cannot peek an empty queue.");
    return queue->front->data; // Return data at the front node
}

/*
This function frees the memory allocated for the queue.

Input parameters:
- queue: pointer to the Queue structure to be freed

Operation:
- Continuously dequeues elements from the queue until it is empty, freeing each node in the process.

Return: None
*/
void free_queue(Queue *queue) {
    while (!is_empty(queue)) {
        dequeue(queue); // Dequeue each element, which also frees the node
    }
}

int main() {
    Queue queue;
    init_queue(&queue);

    // Enqueue
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Front element after enqueues: %d\n", peek(&queue)); // Expected: 10

    // Dequeue
    printf("Dequeued element: %d\n", dequeue(&queue)); // Expected: 10
    printf("Dequeued element: %d\n", dequeue(&queue)); // Expected: 20

    printf("Front element after dequeues: %d\n", peek(&queue)); // Expected: 30

    // Free the queue
    free_queue(&queue);

    return 0;
}
