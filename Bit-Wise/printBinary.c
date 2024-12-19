#include"libs.h"


// Function to print binary representation of any data type
void print_binary(void *value, size_t size) {
    unsigned char *byte = (unsigned char *)value; // Treat the value as an array of bytes

    // Loop over each byte from the most significant to the least significant
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) { // Each byte has 8 bits
            // Use bitwise AND and right shift to get each bit
            printf("%d", (byte[i] >> j) & 1);
        }
        printf(" "); // Separate each byte with a space
    }
    printf("\n"); // New line at the end of the binary representation
}