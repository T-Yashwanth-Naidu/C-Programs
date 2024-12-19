/*
This function check swap 2 integers without using third variable

Input parameters: 2 pointers to integers. number1 and number2
Return: None
*/

#include "libs.h"

void swap_integers(int *number1, int *number2)
{

    if (*number1 != *number2)
    {
        *number1 = *number1 ^ *number2;
        *number2 = *number1 ^ *number2;
        *number1 = *number1 ^ *number2;
    }
}

/*
Example:

    Let's say:
   int num1 = 5;  // Binary: 0101
   int num2 = 9;  // Binary: 1001

   Calling swap_integers(&num1, &num2) will swap their values.

   Step-by-step breakdown:

   num1 = 5 (0101), num2 = 9 (1001)

   1. num1 = num1 ^ num2;   // num1 becomes 0101 ^ 1001 = 1100 (12 in decimal)
   2. num2 = num1 ^ num2;   // num2 becomes 1100 ^ 1001 = 0101 (5 in decimal)
   3. num1 = num1 ^ num2;   // num1 becomes 1100 ^ 0101 = 1001 (9 in decimal)

   Now, num1 = 9, and num2 = 5. The integers have been swapped without using a third variable.

*/
