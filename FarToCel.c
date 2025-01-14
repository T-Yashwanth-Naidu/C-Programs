// This is a simple program that give a table of Celsius to Farenheit conversions


#include<stdio.h>

void main()
{
	int lowerLimit = -30;
	int upperLimit=70;

	printf("Celsius		-		Farenheit\n");
	for(int i=lowerLimit;i<upperLimit;i++)
		printf("%d C		-		%.2f F\n",i,( (i*1.8) +32));

}
