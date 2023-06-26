#include<stdio.h>
#define MAX 5

int Q[MAX];
int front=-1;
int rear=-1;

void Enq(int);
int Deq();
int isempty();
int isfull();
main()
{
	int choice,data;
	while(1)
	{
		printf("1.Enq 2.Deq \n");
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
					printf("Queue is empty\n");
				else
					printf("Data dequed is %d\n",Deq());
				break;
		}
	}
}

int isfull()
{
	if(rear==MAX-1)  // if Q is full
		return 1;
	return 0; // Q is not full
}

int isempty()
{
	if(front==-1)  // Q is empty
		return 1;
	return 0; // Q is not empty
}

void Enq(int d)
{
	if(front==-1) // if Q is empty
		front++; // making front to point to first inserted data
	Q[++rear]=d;  // adding data at rear end
}

int Deq()
{
	int temp;
	temp=Q[front++];// deleting ele from front end
	if(front==rear+1) // means all the elements are deleted
		front=rear=-1; // reseting
	return temp;
}

