//PROGRAM TO COUNT NUMBER OF WORDS IN A TEXT FILE USING FILE


#include<stdio.h>
int main(int argc, char **argv)
{
	FILE *fptr;
	char ch;
	int i,cnt=0;
	
	if(argc<2)
		{	
			printf("ERROR: Expected format ./cnt <src>\n");
			return 0;
		}
	fptr=fopen(argv[1],"r");
	
	if(fptr==NULL)
	{
		printf("ERROR: Source file not found\n");
		return 0;
	}
	
/*	while( (ch=fgetc(fptr))!=EOF)
	{
			printf("%c",ch);
	
	}*/

/*	while( (ch=fgetc(fptr))!=EOF)
		{  
			while(ch!=' '&&)
				cnt++;
		}
	fclose(fptr);*/

	while(ch=fgetc(fptr)!=EOF)
	{		getw(fptr);  cnt++;}
	printf("Number of words in the text file are: %d\n",cnt);


}
