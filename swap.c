// A program to illustrate swapping of 2 numbers using a temp variable for integers

#include<stdio.h>
void swap(int *,int* );

void main()
{
	int num1,num2;
	
	printf("Enter 2 numbers to be swapped: ");
	scanf("%d%d",&num1,&num2);
	
	printf("Before swapping: num1:%d\tnum2:%d\n",num1,num2);
	swap(&num1,&num2);
	printf("After swapping: num1:%d\tnum2:%d\n",num1,num2);
}

void swap(int *num1,int *num2)
{
	int temp;
	temp=*num1;
	*num1=*num2;
	*num2=temp;	
}
