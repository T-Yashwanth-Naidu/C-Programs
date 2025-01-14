#include "libs.h"
#include "functions.h"
#include "structures.h"
int main()
{
    int number1 = 0, number2 = 0;

    // Input numbers from user
    printf("Enter the first number to check: ");
    scanf("%d", &number1);

    printf("Enter the second number to check: ");
    scanf("%d", &number2);

    printf("First number: %d - ",number1);
        print_binary(&number1,sizeof(number1));
    printf("Second number: %d - ",number2);
    print_binary(&number2,sizeof(number2));

    // Check if the Given Number is Even or Odd
    if (check_even_odd(number1) == 1)
        printf("\nNumber is Odd\n");
    else
        printf("\nNumber1 is even\n");

    // Check if given numbers have opposite signs
    if (check_opposite_signs(number1, number2))
        printf("\nHave Opposite Sign\n");
    else
        printf("\nHave Same Sign\n");

    // Swap Numbers
    printf("\nBefore Swap: Number1 = %d, Number2= %d\n", number1, number2);
    swap_integers(&number1, &number2);
    printf("After Swap: Number1 = %d, Number2= %d\n", number1, number2);
    swap_integers(&number1, &number2); // Reset


    // Set or Unset Kth bit
    int pos, choice;

    printf("\n1- Set Bit, 0- Unset Bit: ");
    scanf("%d", &choice);

    printf("\nEnter the position: ");
    scanf("%d", &pos);

    set_unset_kth_bit(&number1, pos, choice);

    if (choice == 1)
    {
        printf("\nAfter setting a bit: \n");
        print_binary(&number1,sizeof(number1));
    }
    else
    {
        printf("\nAfter unsetting a bit: \n");
        print_binary(&number1,sizeof(number1));
    }
    // Reset the bit by calling set_unset_kth_bit with the opposite choice
    set_unset_kth_bit(&number1, pos, !choice); // Reset

    printf("\nNumber reset to original value: %d\n",number1);


    // Find number of set bits
    struct set_bit_struct result = find_set_bits(number1);
    printf("\nNumber of set bits: %u\n", result.numberOfSetBit);
    printf("\nPositions of set bits: ");
    for (int i = 0; i < result.numberOfSetBit; i++) {
        printf("%d ", result.bitPos[i]);
    }
    printf("\n");

    
    print_binary(&number1,sizeof(number1));
    free_set_bit_struct(&result);

    

    return 0;
}