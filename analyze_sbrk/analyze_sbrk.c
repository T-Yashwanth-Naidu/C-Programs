#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #define DEBUG        // Uncomment this to print debug information

int *head = NULL;        // Pointer to start of allocated memory
int count = 1;           // Counter for the number of allocations
int total_allocated = 0; // Total Bytes allocated

// Allocate Memory using sbrk system call
int *allocate_memory(int *current_address, int bytes)
{

    printf("\nAllocation - %d\n", count); // Print the allocation number
    count++;                              // Increment allocation count
    total_allocated += bytes;             // Accumulate total allocated bytes
    int *temp = NULL;                     // Temporary pointer to store allocated memory
#ifdef DEBUG
    // Debug prints for current state
    printf("Current address: %p\n", current_address);
    printf("Head is at: %p\n", head);
#endif

    // Allocate memory using sbrk and update the temp pointer
    temp = (int *)sbrk(bytes);

#ifdef DEBUG
    // Print the allocated memory address
    printf("Printing temp: %p\n", temp);

    // Check for sbrk allocation error
    if (temp == (int *)-1)
        printf("\n\n\n\nSbreak allocation error\n\n\n\n");

    // Print the range of addresses allocated
    printf("Address range:%p to %p available\n", current_address, temp);
    printf("Allocated:   %ld bytes\n", temp - current_address);
#endif
    // Return the new memory location
    return temp;
}

int main(int argc, char *argv[])
{

    int *current_address = NULL; // Pointer to track the current address in memory
    int number_to_allocate;      // Number of bytes to allocate
    int original_break; //Save location for deallocation

    // Get the current break (end of the data segment) address
    current_address = (int *)sbrk(0);
    original_break = sbrk(0);
    printf("\nSBRk:%p\n", (int *)sbrk(0)); // Print the current break

    // Set the head to the start of allocated memory
    head = current_address;
    printf("Allocation starts at: %p\n", head);

    // Sequentially allocate memory in chunks of 256 bytes
    number_to_allocate = 256; // 256 Bytes
    current_address = allocate_memory(current_address, number_to_allocate);
    printf("\nSBRk:%p\n", (int *)sbrk(0)); // Print the new break address

    number_to_allocate = 256; // 256+256 = 512 Bytes
    current_address = allocate_memory(current_address, number_to_allocate);
    printf("\nSBRk:%p\n", (int *)sbrk(0)); // Print the new break address

    number_to_allocate = 256; // 256+256+256 = 768 Bytes
    current_address = allocate_memory(current_address, number_to_allocate);
    printf("\nSBRk:%p\n", (int *)sbrk(0)); // Print the new break address

    number_to_allocate = 256; // 256+256+256+256 = 1024 Bytes
    current_address = allocate_memory(current_address, number_to_allocate);

    // Summary of memory allocated
    printf("\nAllocated total: %d bytes\n", total_allocated);
    
    // The end(current_address) marks the end of the current allcoation region, but not an addresswere data is stored. 

    printf("Total available range: %p to %p\n", head, current_address);


    int total_integers = total_allocated / sizeof(int); // Calculate total integers that can fit in allocated memory

    // Populate allocated memory with integer values starting from 0
    for (int i = 0; i < total_allocated; i++)
    {
       *(head + i) = (unsigned char)i; // Assign values to each allocated memory location

#ifdef DEBUG
        if ((i == 1) || (i == 2)) //||(i==total_allocated-1))      // Just print first 2 elements
#endif
            printf("Address: %p, value= %d\n", (head + i), *(head + i));
    }


    // Read data from allcoated locations ( Dosen't do anything. Could be used for debugging)
    int read, j;
    for (j = 0; j < total_allocated; j++)
    {
        read = *(head + j);
    }


    // Attempt to read from specific memory locations, which might be outside the allocated range. Just for program analysis
    printf("\nData read from allocated locations\n");
    printf("Trying to access last location *(head+j-1):  %d \n", *(head + j - 1)); // Check last allocated value
    printf("Trying to access jth location  *(head+j):  %d \n", *(head + j));    // Outside current boundary
    printf("Trying to access next location  *(head+j+1):  %d \n", *(head + j + 1)); // Outside current boundary

    // Calculate and display the difference between the current address and the head pointer
    printf("The difference: %ld\n", current_address - head);
    
    // Free the allocated space. 
    sbrk(original_break - sbrk(0))
}