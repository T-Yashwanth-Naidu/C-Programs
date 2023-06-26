#include<stdio.h>
#define MAX 5

int Q[MAX];
int rear=-1;
int front=-1;

void Enq(int);
int Deq();
int isfull();
int isempty();

int main()
{
	int choice,data;
	while(1)
	{
		printf("1. Enq 2.Deq\n");
		printf("Enter your choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("Enter the data\n");
				scanf("%d",&data);
				if(isfull())
					printf("Queue is full\n");
				else
					Enq(data);
				break;
			case 2: if(isempty())
				{
					printf("Queue is empty\n");
				}
				else
				{
					printf("data deques is %d\n",Deq());
				}
				break;
		}
	}
}

void Enq(int d)
{
	if(front==-1) // inserting first ele
		front++;
	Q[++rear]=d;
	if(rear==MAX-1)  //inserting last index ele
		rear=-1; // resetting rear to initial stage
}

int Deq()
{
	int temp;
	temp=Q[front++];
	if(front==MAX && rear >-1)  // circular q formed 
		front=0;
	else if((front==MAX) || (front==rear+1)) // all eles in Q are deleted
		rear=front=-1;  // resetting rear and front
	return temp;
}
int isfull()
{
	if(front==rear+1)  // Q is full
		return 1;
	return 0;// Q is not full
}
int isempty()
{
	if(front==-1)// Q is empty
		return 1;
	return 0;// Q is not empty
}

