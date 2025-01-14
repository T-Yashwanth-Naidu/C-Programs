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

*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>


int main(void){


    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8,9,10,11};

    uint64_t sizeofArr1= sizeof(arr1)/sizeof(int);
    uint64_t sizeofArr2= sizeof(arr2)/sizeof(int);
    uint64_t sizeofResultArr = sizeofArr1 + sizeofArr2;
    uint64_t iterationSize=0;

    if(sizeofArr1>sizeofArr2) iterationSize=sizeofArr1;
    else if (sizeofArr1<sizeofArr2) iterationSize=sizeofArr2;
    else iterationSize = sizeofArr1;
    

    int *resultArray= (int*)malloc(sizeofResultArr*sizeof(int));

    uint64_t index=0, i=0;
    for(i=0;i<iterationSize;i++){   // iteration is max length of arr1 and arr2
        
        if(i<sizeofArr1)
        resultArray[index++]= arr1[i];

        if(i<sizeofArr2)
        resultArray[index++]= arr2[i];
    }
    //  2 conditional checks, --> 2*iteration size in worst case
    // Loop runs max(arr1,arr2) and performs 2 conditional checks == O(m+n)


    for(i=0;i<sizeofResultArr;i++){
        printf(" %d ",resultArray[i]);
    }

    free(resultArray);


    return 0;
}


