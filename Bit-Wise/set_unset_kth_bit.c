/*
This function sets or unsets the kth bit.

Input parameters:
- number: pointer to an integer
- pos: position of the bit to set/unset (0-based index)
- choice: an integer to specify the action: 1 - set the bit, 0 - clear the bit

Return: None
*/

#include "libs.h"

void set_unset_kth_bit(int* number, int pos, int choice)
{

   if (choice == 1)    // Turn on the kth bit
    { 
        *number = *number | (1 << pos);
    }
    else                // Turn off the kth bit
    { 
        *number = *number & ~(1 << pos);
    }
}

/*
Example:

- Clearing the nth bit

*number & ~(1 << (pos))

Number = 59 (binary: 00111011)
pos = 1;
1 << 1 = 00000010 (mask)

Negated Mask: ~(1 << 1) = 11111101

number & ~(1 << (pos))
    = 00111011
    & 11111101
    __________
      00111001 (39 in decimal)
    __________

- Setting the nth bit

*number | (1 << (pos))

Number = 59 (binary: 00111011)
pos = 2

1 << 2 = 00000100

number | (1 << pos)
    = 00111011
    | 00000100
    __________
      00111111 (63 in decimal)
    __________
*/
