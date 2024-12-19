/*
This function check if the give number is Even or Odd

Input parameters: a unsigned integer
Return: 1 if odd, 0 if even
*/

#include "libs.h"

bool check_even_odd(int number)
{

        if ((number & 1) == 1) return 1;
        else                   return 0;
}

/*
Example:
 00110011 & 00000001 = 1 (Number is  Odd)
 00110010 & 00000001 = 0 ( Number is Even)
*/
