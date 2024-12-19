#include<stdio.h>
int main( int argc, char **argv)
{
	FILE *sptr,*dptr;
	char ch;
	sptr=fopen("argv[1]","r");
	if(sptr==NULL)
	{
		printf("ERROR: File not found\n");  
		return 0;
	}

	while( (ch=fgetc(sptr))!=EOF)
		printf("%c",ch);


}
