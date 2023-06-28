// This program is an new implementation of strpbrk().
// strpbrk searchs a given string for the first occurrence of any character from a specified set of character.
// In this program, s1 is the string where the search is being performed and s2 is the string that needs to be searched. stribrk returns the positon and characters(s) in s1 that are mentioned in s2.
// This program does not use any function from the string.h library.
// Synatx of strpbrk:  char *strpbrk(const char *s, const char *accept)

#include<stdio.h>
#include<stdlib.h>


int string_length(const char *string)       // Calculate the length of the string
{ 
    int i=0;
    
    while(*(string+i)!='\0')
    {   
        i++;
    }
    printf("length is %d\n",i);
    return i;
}



char *stribrk(const char *s1, const char *s2)   // Check for the first occurance of elements of s2 in s1
{
    int i,j;
    int string1_length= string_length(s1);
    int string2_length= string_length(s2);
    int store_length= string2_length;
    char store[store_length];
    int *result=NULL;
    
    for(i=0;i<store_length;i++)
    {
        store[i]=  *(s2+i);
    }

    for(i=0;i<store_length;i++)
    {
        for(j=0;j<string1_length;i++)
        {
            if(*(s2+i)== *(s1+j))
            {
                result=(char*)malloc(2*sizeof(char));
                *(result+0) =
            }
        }
    }



    printf("\n%s\n ",store);

    return store;
}


void main()
{
    
    char string1[100], string2[100];
    char* data =NULL;

    printf("Enter the string S1(length < 100): ");
    gets(string1);

    printf("Enter the string S2(length < 100): ");
    gets(string2);
    
    data = (char *)malloc(20*(sizeof(char)));
    data = stribrk(string1,string2);

 // printf("\n*(string2+0)=%c\t*(string2+1)=%c\t*(string2+2)=%c\t(*string2+1)=%c\t(*string2+2)=%c\t(*string2)++ =%c\n ",*(string2+0),*(string2+1),*(string2+2),(*string2+1),(*string2+2),(*string2)++);
  
    
    printf("\nThe S1 starts in S2 at %s in S2\n",*data);
}