#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	FILE *fp,*dest;
	char *buf=NULL,ch,choice;
	int i, cnt=0;

	if(argc<3)
	{
		printf("ERROR!  INAVALID SYNTAX. REQ'D ./MV <SRC> <DEST>\n");
		return 0;
        }
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("ERROR! SOURCE FILE DOES NOT EXISTS\n");
		return 0;
	}
	dest=fopen(argv[2],"r");
	if(dest!=NULL)
	{
		printf("WARNING! DESTINATION FILE EXISTING. PREVIOUS CONTENT WILL BE ERASED. PROCEED?(y/n):");
		choice=getchar();	
		if(choice=='n') exit(0);
		else goto g;

		
	}


	else
	
	{
		printf("ERROR! DESTINATION FILE DOES NOT EXISTS. CREATE DESTINATION FILE \n");
		return 0;
	}
g:	fclose(dest);


        while( (ch=fgetc(fp))!=EOF)
                {
                        buf=realloc(buf,cnt+1);
                        buf[cnt++]=ch;
                }

        dest=fopen(argv[2],"w");
        for(i=0;i<cnt;i++)
        {
                fputc(buf[i],dest);
        }

        fclose(fp);
        fclose(dest);
        remove(argv[1]);

}
