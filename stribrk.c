// This program is an new implementation of strpbrk().
// strpbrk searchs a given string for the first occurrence of any character from a specified set of character.
// In this program, s1 is the string where the search is being performed and s2 is the string that needs to be searched. stribrk returns the positon and characters(s) in s1 that are mentioned in s2.
// This program does not use any function from the string.h library.
// Synatx of strpbrk:  char *strpbrk(const char *s, const char *accept)

// Progress: Working.

#include<stdio.h>
#include<stdlib.h>

struct Result{
    int location;
    char character;
};
typedef struct Result result;

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



result stribrk(const char *s1, const char *s2)   // Check for the first occurance of elements of s2 in s1
{
    int i,j;
    int string1_length= string_length(s1);
    int string2_length= string_length(s2);
    int store_length= string2_length;
    char store[store_length];
    result stribrk_result;
    
    for(i=0;i<store_length;i++)
    {
        store[i]=  *(s2+i);
    }

    for(i=0;i<store_length;i++)
    {
        for(j=0;j<string1_length;j++)
        {
            if( *(store+i) == *(s1+j) )
            {
                printf("i=%d\n",i);
                printf("%c %c\n",*(store+i),*(s1+j));
                stribrk_result.location=i;
                stribrk_result.character= *(store+i);
                return stribrk_result;
            }
            
        }
        
    }

    stribrk_result.location=0;
    stribrk_result.character= '\0'; 
    return (stribrk_result);

}


void main()
{
    
    char string1[100], string2[100];
    result main_result;
    printf("Enter the string S1(length < 100): ");
    gets(string1);

    printf("Enter the string S2(length < 100): ");
    gets(string2);
    
    
    main_result = stribrk(string1,string2);
    if(main_result.character=='\0')
    {   
         printf("No match\n");
    }
    else{    
        printf("\nThe first occurance of %d in S1 starts at %c character\n",main_result.location, main_result.character);
    }
}