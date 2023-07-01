#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void reverse(char *,int);

void main()
{
/*	
	char *S1="Welcome";
	char *S2=NULL;
	int i,j,len;
	
	printf("Original String is %s\n", S1);
	
	len = strlen(S1);
	
	for( i=len-1,j=0; i>0 ;i--,j++ )
	{
		S2 = (char*)malloc(sizeof(char));
		*(S2+j) = *(S1+i);
	}
	
	printf("Reversed String is %s\n", S2);
*/

//Working	
	char S1[100],ch;
	char *S2=NULL;
	int i,len;
	
	printf("Enter a string that is to be reverse: ");
	gets(S1);
	printf("Word before swapping: %s",S1);
	len=strlen(S1);
	for(i=0;i<len/2;i++)
	{
		ch=S1[i];
		S1[i]=S1[len-1-i];
		S1[len-1-i]=ch;
		
	}
	printf("Reversed string is %s",S1);
	
}
