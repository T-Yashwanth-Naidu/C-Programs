/*
This function finds the positions of set bits (bits with value 1) in a given integer.

Input parameter:
- number: an integer whose set bits will be identified

Return:
- A struct of type set_bit_struct containing:
  - numberOfSetBit: the count of set bits
  - bitPos: an array holding the positions of each set bit (0-indexed from the least significant bit)
*/
#include "libs.h"

// Function to free allocated memory for bitPos in the set_bit_struct
void free_set_bit_struct(struct set_bit_struct *kth_bit)
{
    free(kth_bit->bitPos);
}

struct set_bit_struct find_set_bits(int number)
{
    // Define a struct to store the results
    struct set_bit_struct kth_bit;

    // Set numberOfBits to the total bit width of an integer (usually 32 bits)
    kth_bit.numberOfBits = sizeof(int) * CHAR_BIT;

    // Initialize the count of set bits to 0
    kth_bit.numberOfSetBit = 0;

    // Allocate memory to store possible set bit positions (up to numberOfBits positions)
    kth_bit.bitPos = (unsigned char *)malloc(kth_bit.numberOfBits * sizeof(unsigned char));

    // Check if memory allocation was successful
    if (kth_bit.bitPos == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Loop through each bit position of the integer
    for (int i = 0; i < kth_bit.numberOfBits; i++)
    {
        // Check if the least significant bit (LSB) of 'number' is set (1)
        if (number & 1)
        {
            // Store the position of the set bit (0-indexed)
            kth_bit.bitPos[kth_bit.numberOfSetBit] = i;

            // Increment the count of set bits
            kth_bit.numberOfSetBit++;
        }
        // Right-shift 'number' by 1 to check the next bit in the next iteration
        number >>= 1;
    }
    // Return the struct containing the count and positions of set bits
    return kth_bit;
}

/*
Example:
Number: 59 (binary: 00111011)

Position: 7 6 5 4 3 2 1 0
Bit:      0 0 1 1 1 0 1 1

numberOfBits = sizeof(int) * CHAR_BIT = 32 (assuming a 32-bit system)
numberOfSetBit = 0

Position	Number & 1 (set?)	    Action
0	            Yes	                Store position 0 in bitPos, increment numberOfSetBit
1	            Yes	                Store position 1 in bitPos, increment numberOfSetBit
2	            No	                Skip
3	            Yes	                Store position 3 in bitPos, increment numberOfSetBit
4	            Yes	                Store position 4 in bitPos, increment numberOfSetBit
5	            Yes	                Store position 5 in bitPos, increment numberOfSetBit
6	            No	                Skip
7	            No	                Skip


numberOfSetBit = 5
bitPos = [0, 1, 3, 4, 5]

*/
