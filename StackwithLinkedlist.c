#include<stdio.h>
#include<stdlib.h>

struct Stack
{
	int data;
	struct Stack *next;
};

void Push(int);

int Pop();

int isempty();

int Peek();
struct Stack *top=NULL;  // top of the stack
main()
{
	int choice,val;
	while(1)
	{
		printf("1.Push 2.Pop 3.Peek\n");
		printf("enter the choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("enter the data\n");
				scanf("%d",&val);
				Push(val);
				break;
			case 2: if(isempty())
					printf("Stack is empty\n");
				else
				
				printf("data poped from stack is %d\n",Pop());
				
				break;
			case 3: if(isempty())
					printf("Stack is empty\n");
				else
					printf("top of the stack pointing to %d",Peek());
				break;
		}
	}
}

void Push(int d)
{
	struct Stack *newnode=NULL;
	newnode=calloc(1,sizeof(struct Stack));
	if(newnode==NULL)
	{
		printf("Stack is FULL\n");
	}
	else
	{
		newnode->data=d;
		newnode->next=top;
		top=newnode;  // adding at top
	}
}

int Pop()
{
	struct Stack *temp=NULL;
	int d;
	temp=top;
	d=top->data;  // d=temp->data;
	top=top->next;
	free(temp);
	temp=NULL;
	return d;
}

int Peek()
{
	return top->data;
}

int isempty()
{
	if(top==NULL)  // stack is empty
		return 1;
	return 0; // stack is not empty
}
