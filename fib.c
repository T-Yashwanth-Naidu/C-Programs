#include<stdio.h>
#include<stdlib.h>
#define COUNT 10
int num1=0,num2=1,sum=0,i;
int innercount=0;
void fibo(int);



void main()
{
	int num1=0,num2=1,sum=0,i;
	printf("%d, %d ,",num1,num2);
	sum=num1+num2;
	fibo(sum);
	

}

void fibo(int sum)
{
	printf(" %d ",sum);
	num1=num2;
	num2=sum;
	sum=num1+num2;
	if(innercount==COUNT)
		exit(0);
	innercount++;
	for(int i=0;i<COUNT;i++)
	{
		fibo(sum);
	}

}
