#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void){

    char *ptr1 = "abcd";
    char *ptr2 = "1234";

    unsigned int sizeofPtr1 = strlen(ptr1);
    unsigned int sizeofPtr2 = strlen(ptr2);

    char *result = (char*)malloc(sizeofPtr2+sizeofPtr1);
    
    unsigned int index=0;

    for(int i=0;i<sizeofPtr1;i++){
        result[index++]= *(ptr1+i);
        result[index++]= *(ptr2+i);
    }
    result[index]='\0';

    printf("\n%s\n", result);

    free(result);
    return 0;
}