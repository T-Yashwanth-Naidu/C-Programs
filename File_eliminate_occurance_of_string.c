//  PROGRAM TO REMOVE THE OCCURANCE OF A GIVEN STRING IN A FILE.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char **argv)
{
	FILE *fptr;
	int words=0,charcnt=0,newline=0,cnt=0;
	char *word,ch,*buf=NULL,wordstore[25],*q;
	if(argc<3)
	{
		printf("ERROR:Exptected format ./rm <word>  <filename>\n");
		return 0;
	}

	fptr=fopen(argv[2],"r");
	if(fptr==NULL)
	{
		printf("ERROR: File does not exists\n");
		return 0;
	}

	int length=strlen(argv[1]);



	while( (ch=fgetc(fptr))!=EOF)
	{
		buf=realloc(buf,cnt+1);
		buf[cnt++]=ch;
	}
	buf=realloc(buf,cnt+1);
	buf[cnt++]=0;

	word=buf;
	while(*word)
	{
		if( q=strstr(word,argv[1]))
		{
			memmove(q,q+length,strlen(q+length)+1);
				word=q;
			continue;
		}
		word++;
	}
	printf("%s\n",buf);
}









