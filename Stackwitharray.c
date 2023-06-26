#include<stdio.h>
#define MAX 5

int Stack[MAX];
int top=-1;

void Push(int);
int Pop();
int Peek();

int isempty(); // returns 1 if stack is empty, returns 0 if stack is nonempty
int isfull();  // retuns 1 if stack is full , return 0 if stack is not full
main()
{	int choice;
	int data;
	while(1)
	{
		printf("1.Push 2.Pop 3.Peek\n");
		printf("enter the choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("enter the data\n");
				scanf("%d",&data);
				Push(data);
				break;
			case 2: if(isempty())
					printf("Stack is empty\n");
				else
				printf("data poped from stack is %d\n",Pop());
				break;
			case 3: if(isempty())
					printf("Stack is empty\n");
				else
				printf("top of the stack pointing %d\n",Peek());
				break;
		}
	}
}

void Push(int val)
{
	if(isfull())
		printf("Stack is full\n");// if stack is full insertion not possible
	else
	{	/*++top;
		Stack[top]=val;  */

		Stack[++top]=val;// increment the top.and store value at top 
	}
}
int Pop()
{
	return Stack[top--];  // return the value at top and decrement the top
}

int Peek()
{
	return Stack[top];  // returns the value at the top
}


int isempty()
{
	if(top==-1)
		return 1; // stack is empty
	return 0; // stack not empty
}

int isfull()
{
	if(top==MAX-1)
		return 1; // stack is full
	return 0; // stack not full
}
