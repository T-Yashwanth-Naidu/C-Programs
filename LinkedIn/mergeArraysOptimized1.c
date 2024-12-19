/*
int arr1[] = {1, 3, 5, 7};
int arr2[] = {2, 4, 6, 8};

Write a program that merges these two arrays into a new array, but with a twist:

The new array should alternate elements from arr1 and arr2.
If one array is longer than the other, append the remaining elements from the longer array at the end.

1 2 3 4 5 6 7 8

Approach:
- get sizes of those arrays individually
- the result array has the combined size
- before adding element into the result array, check if you have reached end of the respective array size
- if within the size, input the elements one by one.

- While calculating size, i thought what if the array sizes are different and implemented  a new logic


What is optimized?
- removed unncessary else if condition and changed the expression into terinary operation
*/

/*
Inefficient areas:
- Checking with if conditions eveyrtime in for loop. It is inefficient for larger dataset.
- Is it possible to reduce te number of conditional checks in the merging logic?
- Will there be any memory leaks? How to ensure that they dont occur?
- How would you avoid using malloc?(if its for smaller data set) or if the array size is known at compile time?
-  What changes would you make to handle cases where one of the arrays is NULL

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(void)
{

    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8, 9, 10, 11};

    uint64_t sizeofArr1 = sizeof(arr1) / sizeof(int);
    uint64_t sizeofArr2 = sizeof(arr2) / sizeof(int);
    uint64_t sizeofResultArr = sizeofArr1 + sizeofArr2;
    uint64_t iterationSize = 0;

    iterationSize = (sizeofArr1 > sizeofArr2) ? sizeofArr1 : sizeofArr2;

    if ((arr1 == NULL) && (arr2 == NULL))
    {
        printf("\nBoth the arrays are empty\n");
    }
    else if (arr1 == NULL)
    {
        printf("\nArray1 is empty\n");
    }
    else if (arr2 == NULL)
        printf("\nArray2 is empty\n");

    int *resultArray = (int *)malloc(sizeofResultArr * sizeof(int));

    uint64_t index = 0, i = 0;
    while(i<sizeofArr1 && i<sizeofArr2)
    {

        resultArray[index++] = arr1[i];
        resultArray[index++] = arr2[i];i++;
    }
    // Runs min(arr1,arr2) , no conditional checks in the above
    

    while (i < sizeofArr1)
        resultArray[index++] = arr1[i++];
    while (i < sizeofArr2)
        resultArray[index++] = arr2[i++];

    // Even after the above 2, it goes O(m+n)

    for (i = 0; i < sizeofResultArr; i++)
    {
        printf(" %d ", resultArray[i]);
    }

    free(resultArray);

    return 0;
}
