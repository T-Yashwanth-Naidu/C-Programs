#include<stdio.h>
int main( int argc, char **argv)
{
	FILE *sptr,*dptr;
	char ch;
	if(argc<3)
	{
		printf("ERROR: Expected ./cpy <src> <dst>\n");
		return 0;
	}

	sptr=fopen(argv[1],"r");
	if(sptr==NULL)
	{
		printf("ERROR: Source file is not existing\n");
		return 0;
	
	}
	dptr=fopen(argv[2],"w");

	while( (ch=fgetc(sptr))!=EOF)
	{
		fputc(ch,dptr);
	
	}
	fclose(sptr);
	fclose(dptr);
	printf("STATUS: FILE COPIED\n");



}
