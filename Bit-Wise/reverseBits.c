/*
This function reverses the bits of an 8-bit unsigned integer.

Input parameters:
- value: an 8-bit unsigned integer whose bits will be reversed.

Return:
- The 8-bit unsigned integer with bits reversed.

Example:

value = 0b11010010 (210 in decimal)
After reversing, the result will be 0b01001011 (75 in decimal)

Explanation:
Starting with an empty result, we shift the result left each time and add the least significant
bit of 'value' to the result. We then shift 'value' right to process the next bit. This continues for all 8 bits.

*/

#include "libs.h"

uint32_t reverseBits_naive(uint32_t value)
{
   uint32_t result = 0;
   for (int i = 0; i < 32; i++)
   {
      result = (result << 1) | (value & 1); // Add the LSB of 'value' to 'result'
      value >>= 1;                          // Shift 'value' right to process the next bit
   }
   return result;
}

/*
Example:

Let's say value = 0b11010010.

Iteration-by-iteration:

1. result = 0b00000000, value = 0b11010010
   - result << 1 = 0b00000000
   - (value & 1) = 0 (add LSB of 'value')
   - result = 0b00000000, value >>= 1 -> 0b01101001

2. result = 0b00000000, value = 0b01101001
   - result << 1 = 0b00000000
   - (value & 1) = 1 (add LSB of 'value')
   - result = 0b00000001, value >>= 1 -> 0b00110100

3. result = 0b00000001, value = 0b00110100
   - result << 1 = 0b00000010
   - (value & 1) = 0
   - result = 0b00000010, value >>= 1 -> 0b00011010

4. Continue similarly until all 8 bits are processed.

Final result after 8 iterations: 0b01001011 (75 in decimal).
*/

int32_t reverseBits_optimized(uint32_t value)
{
   // Step 1: Swap adjacent bits
   value = ((value & 0x55555555) << 1) | ((value & 0xAAAAAAAA) >> 1);

   // Step 2: Swap pairs of 2 bits
   value = ((value & 0x33333333) << 2) | ((value & 0xCCCCCCCC) >> 2);

   // Step 3: Swap 4-bit nibbles
   value = ((value & 0x0F0F0F0F) << 4) | ((value & 0xF0F0F0F0) >> 4);

   // Step 4: Swap bytes (8 bits)
   value = ((value & 0x00FF00FF) << 8) | ((value & 0xFF00FF00) >> 8);

   // Step 5: Swap 16-bit halves
   value = ((value & 0x0000FFFF) << 16) | ((value & 0xFFFF0000) >> 16);

   return value;
}
/*
This function reverses the bits of a 32-bit unsigned integer using an optimized approach.

Input parameters:
- value: a 32-bit unsigned integer whose bits will be reversed.

Return:
- The 32-bit unsigned integer with bits reversed.

Example:

Let's say value = 0x12345678 (binary: 0b0001 0010 0011 0100 0101 0110 0111 1000).

Iteration-by-iteration:

1. Swap adjacent bits:
   value = ((value & 0x55555555) << 1) | ((value & 0xAAAAAAAA) >> 1)

   - Mask 0x55555555 (binary: 01010101 01010101 01010101 01010101) extracts bits in odd positions.
   - Mask 0xAAAAAAAA (binary: 10101010 10101010 10101010 10101010) extracts bits in even positions.
   - Shift left and right to swap each adjacent bit.

   After step 1: value = 0b0010 0010 0001 0100 1010 1001 1101 0000 (0x2214A9D0)

2. Swap pairs of 2 bits:
   value = ((value & 0x33333333) << 2) | ((value & 0xCCCCCCCC) >> 2)

   - Mask 0x33333333 (binary: 00110011 00110011 00110011 00110011) extracts bits in 2-bit pairs.
   - Mask 0xCCCCCCCC (binary: 11001100 11001100 11001100 11001100) extracts bits in complementary pairs.
   - Shift left and right by 2 to swap each 2-bit group.

   After step 2: value = 0b0000 0100 0010 0100 0110 0101 0010 1011 (0x0424652B)

3. Swap 4-bit nibbles:
   value = ((value & 0x0F0F0F0F) << 4) | ((value & 0xF0F0F0F0) >> 4)

   - Mask 0x0F0F0F0F (binary: 00001111 00001111 00001111 00001111) extracts 4-bit groups.
   - Mask 0xF0F0F0F0 (binary: 11110000 11110000 11110000 11110000) extracts complementary 4-bit groups.
   - Shift left and right by 4 to swap each 4-bit group.

   After step 3: value = 0b0100 0010 0100 0000 1011 0110 0101 0010 (0x4240B652)

4. Swap bytes (8-bit groups):
   value = ((value & 0x00FF00FF) << 8) | ((value & 0xFF00FF00) >> 8)

   - Mask 0x00FF00FF (binary: 00000000 11111111 00000000 11111111) extracts bytes in odd positions.
   - Mask 0xFF00FF00 (binary: 11111111 00000000 11111111 00000000) extracts bytes in even positions.
   - Shift left and right by 8 to swap each byte.

   After step 4: value = 0b1011 0000 0100 0010 0110 0101 0000 0010 (0xB0426502)

5. Swap 16-bit halves:
   value = ((value & 0x0000FFFF) << 16) | ((value & 0xFFFF0000) >> 16)

   - Mask 0x0000FFFF (binary: 00000000 00000000 11111111 11111111) extracts the lower 16 bits.
   - Mask 0xFFFF0000 (binary: 11111111 11111111 00000000 00000000) extracts the upper 16 bits.
   - Shift left and right by 16 to swap the 16-bit halves.

   After step 5: value = 0b0000 0010 0101 0110 0000 0010 1011 1100 (0x2A650000)

Final result after all iterations: value = 0b0000 0010 0101 0110 0000 0010 1011 1100 (0x2A650000)

Final result: 0b0000 0010 0101 0110 0000 0010 1011 1100

Final result: 0x2A650000
*/



#include <stdio.h>
#include <stdlib.h>

void modify(int *ptr) {
    *ptr = 42;
}

void confusingFunction(int **ptr) {
    *ptr = (int *)malloc(sizeof(int));
    **ptr = 99;
    ptr++;
}

int main() {
    int val = 7;
    int *p = &val;
    int **pp = &p;

    modify(p);
    printf("After modify: %d\n", *p);

    confusingFunction(pp);
    printf("After confusingFunction: %d\n", *p);
    free(p);
    return 0;
}


