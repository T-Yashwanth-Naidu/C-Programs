#include<stdio.h>
#include<string.h>

int main(int argc,char **argv)
{
	FILE *fp;
	char ch[500],c;

	if(argc<3)
	{
		printf("ERROR! Invalid synatx.Expected ./grep <pattern> <file>\n");
		return 0;
	}
	
	fp=fopen(argv[2],"r");

	if(fp==NULL)
	{
		printf("ERROR! File does not exists. Enter a valid file name\n");
		return 0;
	}

	while( (c=fgetc(fp))!=EOF)
		
	{
		fscanf(fp, "%[^\n]", ch);
		if( (strstr(ch,argv[1]))!=NULL)
			printf("%s\n",ch);

	}
	fclose(fp);


	

}
