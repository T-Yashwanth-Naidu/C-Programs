#include<stdio.h>
#define MAX 100
char Stack[MAX];
int top=-1;

void Push(char);
char Pop();

main()
{
	char exp[MAX];
	int i=0;
	printf("enter the expression\n");
	scanf("%s",exp);
	while(exp[i])
	{
		if(exp[i]=='(' || exp[i]=='{' || exp[i]=='[')
			Push(exp[i]); // if current element is open brace push on to the stack
		else if(exp[i]==')') // if current element is function close brace then pop the stack
		{
			if(Pop()!='(')    // if poped element is not equal to function open brace then break the loop
				break;
		}
		else if(exp[i]=='}') // if current element is curly close brace then pop the stack
		{
			if(Pop()!='{')// if poped element is not equal to curly open brace then break the loop
				break;
		}
		else if(exp[i]==']') // if current element is square closed brace then pop the stack
		{
			if(Pop()!='[')// if poped element is not equal to square open brace then break the loop
				break;
		}
		i++;
	}
	if(exp[i]=='\0' && top==-1)
		printf("%s is balanced parathesis exp\n",exp);
	else
		printf("%s is Nonbalanced parathesis exp\n",exp);
}

void Push(char ch)
{
	if(top==MAX)// stack is full
		printf("Stack is overflow\n");
	else
	{
		Stack[++top]=ch;
	}
}
char Pop()
{
	if(top==-1) // Stack is empty
		return -1;
	return Stack[top--];
}
