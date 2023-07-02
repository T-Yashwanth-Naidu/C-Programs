// A Program to illustrate reversing of a int array using recursion

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void rev(int);
int revarr[50];
static int indexval;
int next;

int main(int argc, char const *argv[]) {

	int number;
	printf("Enter a number: ");
	scanf("%d",&number);
	printf("\nThe reverse of the number is : ");
	rev(number);

}


void rev(int  number)
{
	int retval,revnum;
	retval=number;
	if( (retval%10!=0))
{
	revnum=retval%10;
	printf("%d",revnum);
	next=retval/10;
	rev(next);
}
else exit(0);


}
