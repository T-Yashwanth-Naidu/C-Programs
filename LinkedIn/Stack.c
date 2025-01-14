/*
  Stack Implementation Using a Linked List

  This program implements a stack data structure using a linked list.
  A stack is a Last-In-First-Out (LIFO) data structure where elements are added to and removed from the "top" of the stack.

  The stack is implemented using two structures:
  1. `Node`: Represents each element in the stack, containing an integer data field and a pointer to the next node.
  2. `Stack`: Holds a pointer to the top node in the stack. If the stack isempty, the top pointer is set to NULL.

  Key Operations:
  - `init_stack`: Initializes the stack by setting the top pointer to NULL.
  - `is_empty`: Checks if the stack is empty by verifying if the top pointer is NULL.
  - `push`: Adds an element to the top of the stack. It creates a new node, assigns it the input data, links it to the current top node, and updates the top pointer.
  - `pop`: Removes the top element from the stack. It checks if the stack is empty,retrieves the data from the top node, updates the top pointer to the next node,and frees the memory of the old top node.
  - `peek`: Returns the data at the top of the stack without removing it. It checks if the stack is empty before accessing the data.
  - `free_stack`: Frees all nodes in the stack by continuously popping elements until the stack is empty, releasing allocated memory.

  Usage Example:
  The `main` function demonstrates the use of the stack operations:
  - Initializes the stack.
  - Pushes elements onto the stack.
  - Peeks at the top element.
  - Pops elements from the stack and prints them.
  - Frees the stack when no longer in use.

  This code also includes assertions to ensure that operations like `pop` and `peek`are only performed when the stack is not empty, preventing potential errors such asstack underflow.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int data;          // to store one element
    struct Node *next; // to store address of next node
} Node;

// The stack itself is represented by a structure that keeps a pointer to the top node.
typedef struct
{
    Node *top; // Pointer to the top of stack
    // If the stack is empty, the Top should point to NULL, else it should point to the top of the stack
} Stack;

/*
This function initializes the stack.

Input parameters:
- stack: pointer to the Stack structure to initialize

Operation:
- Sets the top of the stack to NULL, indicating that the stack is initially empty.

Return: None
*/
void init_stack(Stack *stack)
{
    stack->top = NULL; // Initialize the top of the stack to NULL at the beginning of program execution
}

/*
This function checks if the stack is empty.

Input parameters:
- stack: pointer to the Stack structure to check

Operation:
- Returns 1 if the top of the stack is NULL (indicating the stack is empty), and 0 otherwise.

Return:
- int: 1 if stack is empty, 0 if not
*/
int is_empty(Stack *stack)
{
    return stack->top == NULL;
}

/*
This function pushes an element onto the stack.

Input parameters:
- stack: pointer to the Stack structure where the element is to be pushed
- value: the integer value to be pushed onto the stack

Operation:
- Allocates memory for a new node.
- Sets the node's data to the provided value.
- Links the new node to the current top of the stack.
- Updates the top pointer to point to the new node.

Return: None
*/
void push(Stack *stack, int value)
{
    Node *newnode = (Node *)malloc(sizeof(Node)); // Allocate memory for a new node
    assert(newnode != NULL && "Memory allocation failed.");

    newnode->data = value;      // Set the data field of the new node to the value being pushed
    newnode->next = stack->top; // Link the new node to the current top node of the stack
    stack->top = newnode;       // Update the top pointer to the new node
}

/*
This function pops an element from the stack.

Input parameters:
- stack: pointer to the Stack structure from which the element is to be popped

Operation:
- Checks if the stack is empty before proceeding.
- Stores the current top node in a temporary pointer.
- Retrieves the data from the top node.
- Updates the top pointer to the next node in the stack.
- Frees the memory of the old top node.

Return:
- int: the data from the popped node
*/
int pop(Stack *stack)
{
    // Ensure the stack is not empty before popping
    assert(!is_empty(stack) && "STACK IS EMPTY. CANNOT POP");

    Node *tempStack = stack->top;  // Store the current top node in a temporary pointer
    int data = tempStack->data;    // Retrieve the data from the top node
    stack->top = stack->top->next; // Update the top pointer to the next node
    free(tempStack);               // Free the memory allocated for the old top node

    return data; // Return the data from the popped node
}

/*
This function retrieves the data at the top of the stack without removing it.

Input parameters:
- stack: pointer to the Stack structure from which to peek the top element

Operation:
- Checks if the stack is empty before proceeding.
- Returns the data stored in the top node.

Return:
- int: the data at the top of the stack
*/
int peek(Stack *stack)
{
    assert(!is_empty(stack) && "Cannot peek an empty stack.");
    return stack->top->data; // Return data at the top node
}

/*
This function frees the memory allocated for the stack.

Input parameters:
- stack: pointer to the Stack structure to be freed

Operation:
- Continuously pops elements from the stack until it is empty, freeing each node in the process.

Return: None
*/
void free_stack(Stack *stack)
{
    while (!is_empty(stack))
    {
        pop(stack); // Pop each element, which also frees the node
    }
}

int main()
{
    Stack stack;
    init_stack(&stack);

    // Push
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element after pushes: %d\n", peek(&stack)); // Expected: 30

    // Pop
    printf("Popped element: %d\n", pop(&stack)); // Expected: 30
    printf("Popped element: %d\n", pop(&stack)); // Expected: 20

    printf("Top element after pops: %d\n", peek(&stack)); // Expected: 10

    // Free the stack
    free_stack(&stack);

    return 0;
}
