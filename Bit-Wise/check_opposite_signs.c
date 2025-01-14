/*
This function check if 2 integers have opposite signs.

Input parameters:
- Two integers: number1, number2

Return:
- true if they have opposite signs, false if they have the same sign

*/
#include "libs.h"

bool check_opposite_signs(int number1, int number2)
{

    return (number1 ^ number2) < 0;
}

/*
    Example:
    Number1 = -9, Number2 = 33

    -9 in 2's complement - 1111 0111
    33 in binary - 0010 0001
        11110111
    ^   00100001
    _____________
        11010110 ( Since the MSB is 1, the result is negative, indicating opposite signs)
    _____________

    Number1 = 9, Number2 = 33

    9  in binary - 0000 1001
    33 in binary - 0010 0001
        00001001
    ^   00100001
    _____________
        00101000 (Since the MSB is 0, the result is positive, indicating the same sign)
    _____________
*/