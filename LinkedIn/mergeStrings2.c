/*

char *ptr1 = "HELLO";
char *ptr2 = "world";

Output: hWoErLlLoD

first idea
the caps are converted to smaller for ptr1 and the inverse for ptr2.
while printing ouput, and after conversion, one char from  ptr1 and then ptr2

so it is something like, (after conversion): ptr1ptr2ptr1ptr2... until 5 chars
but just before i keep that, 
to convert a --> A i do -62 for converting it to higher case and +62 for converitng from higer case to lower case.

*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

int main(void){

    char *ptr1 = "HELLO";
    char *ptr2 = "world";

    uint64_t sizeofPtr1=strlen(ptr1);
    uint64_t sizeofPtr2=strlen(ptr2);
    uint64_t resultSize= sizeofPtr1+sizeofPtr2;
    uint64_t index=0,i=0;

    char *result=(char*)malloc(resultSize+1);

    for(i=0;i<sizeofPtr1;i++){
        result[index++] = *(ptr1+i) + 32;
        result[index++] = *(ptr2+i) - 32;
    }
    result[index] = '\0';

    printf("\n%s\n",result);
    
    
    
    return 0;
}