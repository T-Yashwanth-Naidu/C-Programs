//Program to find factorial of a given number
#include<stdio.h>

int main(int argc, char const *argv[]) {
  long long int number,i=0,fact=1;
  printf("Enter a number to find the factorial for: " );
  scanf("%lld",&number);
  if(number==0)
    printf("Factorial of 0 is 0\n");
    else
  {
  while(number>=1)
  {
    fact=fact*number;
    number--;
  }
  printf("Factorial is : %lld",fact);
  }
  return 0;
}
