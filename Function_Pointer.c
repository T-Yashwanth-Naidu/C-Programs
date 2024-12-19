#include<stdio.h>
void  add(int, int);
void  sub(int, int);
void  mul(int, int);
void  div(int, int);
void (*fptr[4])(int, int);

void main()
{
	fptr[0]=add;
	fptr[1]=sub;
	fptr[2]=mul;
	fptr[3]=div;
	int select,num1,num2;

	printf("~~~~~WELCOME TO ARTHEMETIC OPERATIONS USING FUNCTION POINTERS~~~~~\n");
	printf("Enter two numbers: ");
	scanf("%d%d", &num1, &num2);

	printf("Select your choice of operation: \n");
	printf("\t1)ADD\t2)SUBTRACT\t3)MULTIPLY\t4)DIVIDE\n");
	scanf("%d", &select);

	switch (select)
	{
	case 1:	//fptr= fun_array[0];
			//fun_array[0];
			printf("ADDING....");
			(*fptr[0])(num1,num2);
			break;
			
	}



}

void add(int num1, int num2)
{
	printf("Addition of %d, %d is : %d\n", num1, num2, (num1 + num2));
}

void sub(int num1, int num2)
{
	printf("Subtraction of %d, %d is : %d\n", num1, num2, (num1 - num2));
}

void mul(int num1, int num2)
{
	printf("Multiplication of %d, %d is : %d\n", num1, num2, (num1 * num2));
}

void div(int num1, int num2)
{
	printf("Division of %d, %d is : %d\n", num1, num2, (num1 / num2));
}




