#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	FILE *fptr;
	int words=0,charcnt=0,newline=0,cnt=0;
	char ch,*buf=NULL;;
	if(argc<2)
	{
		printf("ERROR:Exptected format ./wc  <filename>\n");
		return 0;
	}

	fptr=fopen(argv[1],"r");
	if(fptr==NULL)
	{
		printf("ERROR: File does not exists\n");
		return 0;
	}

	while( (ch=fgetc(fptr))!=EOF)
	{
		buf=realloc(buf,cnt+1);
		buf[cnt++]=ch;
	}
	buf=realloc(buf,cnt+1);
	buf[cnt++]=0;


	for(int  i=0;i<cnt;i++)
	{
		if(buf[i]=='\n')  newline++;
		if(   ((buf[i]!=' ')&&(buf[i+1]=='\n') )|| ( (buf[i]==' ')&&(buf[i+1]!='\n')))  words++;
	}

fclose(fptr);
	
	printf("characters: %d\t words:%d\t lines:%d\n",cnt,words,newline);





}
