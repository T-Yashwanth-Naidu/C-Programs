/*
COBS (Consistent Overhead Byte Stuffing)

Purpose:
- Encodes data to ensure that a delimiter byte (e.g., 0x00) does not appear in
  the payload.
- Guarantees that 0x00 is reserved for marking the end of a packet, simplifying
  parsing and ensuring reliable communication in data transmission.

How It Works:
1. Replace each 0x00 byte in the input data with a value indicating the distance
   (in bytes) to the next 0x00 or the end of the packet.
2. If no more 0x00 bytes exist, the distance value points to the end of the
   packet.
3. The encoded data is appended with a 0x00 delimiter to clearly mark the end of
   the packet.

Example:

Input:
Index:      0   1   2   3   4   5
Data:      [2,  0,  1,  3,  0,  2]

Encoded Output:
[3, 2, 1, 3, 2, 0]
*/

#include <stdio.h>
#include <stdlib.h>

// Function to perform COBS encoding
int *cobs_encode(const int *input_array, int size) {
  if (input_array[size - 1] != 0) {
    printf("Error: Input must terminate with a zero delimiter.\n");
    return NULL;
  }

  // Allocate memory for the output array
  int *output_array = (int *)malloc((size + 1) * sizeof(int));
  if (output_array == NULL) {
    printf("Memory allocation failed.\n");
    return NULL;
  }

  // COBS encoding logic
  for (int i = 0; i < size; i++) {
    if (input_array[i] == 0) { // Found a zero
      int distance = 1;
      for (int j = i + 1; j < size; j++) {
        if (input_array[j] == 0) { // Next zero found
          break;
        }
        distance++;
      }
      output_array[i] = distance; // Replace 0 with the distance
    } else {
      output_array[i] = input_array[i]; // Copy non-zero value as-is
    }
  }

  // Append the delimiter 0x00 to the output array
  output_array[size] = 0;

  return output_array;
}

int main() {
  // Initialize input data
  int input_array[] = {2, 0, 1, 3, 0, 2};
  int size = sizeof(input_array) / sizeof(input_array[0]);

  // Perform COBS encoding
  int *encoded_array = cobs_encode(input_array, size);

  if (encoded_array == NULL) {
    return 1; // Exit on error
  }

  // Print the encoded output
  printf("Encoded Output:\n[");
  for (int i = 0; i <= size; i++) {
    printf("%d", encoded_array[i]);
    if (i < size) {
      printf(", ");
    }
  }
  printf("]\n");

  // Free allocated memory
  free(encoded_array);

  return 0;
}
