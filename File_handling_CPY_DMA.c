#include<stdio.h>
#include<stdlib.h>
int main( int argc, char **argv)
{
	FILE *fptr;
	char ch, *buf=NULL;
	int cnt=0;
	if(argc<3)
	{
		printf("ERROR: EXPECTED FORMAT ./cpy <src> <dst>\n");
		return 0;
	}
	fptr=fopen(argv[1],"r");
	if(fptr==NULL)
	{
		printf("ERROR: Source file does not exists\n");
		return 0;
	
	}

	while( (ch=fgetc(fptr))!=EOF)
	{
		buf=realloc(buf,cnt+1);
		buf[cnt++]=ch;
	}
	buf=realloc(buf,cnt+1);
	buf[cnt++]=0;

	fclose(fptr);

	fptr=fopen(argv[2],"w");
	fputs(buf,fptr);
	fclose(fptr);
	printf("COPY SUCCESS\n");
}




