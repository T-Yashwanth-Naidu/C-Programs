/*
 Given a string, find the length of the longest substring without repeating characters.

Input: "abcabcbb"
Output: 3
Explanation: The longest substring without repeating characters is "abc", which has a length of 3.

*/
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG
int main(void){


    // Step 1: Ask input from the user
    char *inputString=NULL;

    // I have 2 options, one if the strins size is small(like not an entire file, i can use fgets, else i need to use getline)

    // Approach 1, using fgets

    size_t bufferSize = 256;
    inputString=(char*)malloc(bufferSize);
    
    printf("\nEnter a String: ");
    if(fgets(inputString,bufferSize, stdin)!=NULL){  // Checking with NULL to check if it successfully reads input
        
        inputString[strcspn(inputString,"\n")]='\0';   
        // String complement span. It searches for the string for the first occurance of any character in the set specified in the second argument. It returns the first occurance of \n or the length of the string if not found.

        // we are using \0 as we removed the new line earlier and we are terminating the string with NULL.
    }

    #ifdef DEBUG

    printf("[DEBUG: ] String is: %s", inputString);

    #endif 

    // Step 2: Traverse through the string to find the longest substring
    /*
    Hints to solve Step 2

    1. Initialize lastSeen array of size 128 with all values set to -1.
    2. Initialize startPtr = 0, maxLength = 0.

    3. For each character in the input string (use traversePtr as the loop index):
    a. If the character is already seen (i.e., lastSeen[character] >= startPtr):
        - Move startPtr to lastSeen[character] + 1.
    b. Update lastSeen[character] with the current index (traversePtr).
    c. Calculate currentLength = traversePtr - startPtr + 1.
    d. Update maxLength if currentLength is greater than maxLength.

    4. Print maxLength as the result.

    
    */
    char lastSeen[128]; // 128 covers all the values in the ASCII table

    for(int i=0;i<128;i++) lastSeen[i]= -1; // Initialize all elments with -1

    int startPtr=0, maxLength=0, currentLength=0;
    // startPtr - Keeps track of Start of current substring
    // maxLength - stores the length of longest substring found
    // currenlength - used to calculate current substring window

    int sizeofInputString = strlen(inputString);
    char currentChar;

    for(int i=0;i<sizeofInputString;i++)
    {
        // Get current character from the input string
        currentChar = inputString[i]; 

        // If current character is seen before within the current substring window, i.e after startPtr, move the startPtr to lasteSeen[currentChar]+1 to exclude the repeating character. It shrinks the window
        if( lastSeen[(int)currentChar] >=startPtr ){
            startPtr = lastSeen[(int)currentChar] + 1;
        }        

        lastSeen[(int)currentChar] = i; // update last seen index with current index. It now holds the latest occurance of the character

        currentLength = i - startPtr +1; 

        // Update the maximum length
        if(currentLength>maxLength) maxLength=currentLength;


    }
    printf("Length of the longest substring without repeating characters: %d\n", maxLength);


    free(inputString);


}
