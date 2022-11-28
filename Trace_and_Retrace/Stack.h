#ifndef __STACKH__
#define __STACKH__

#include<stdio.h>
#include<stdlib.h>
struct stack{
    int x_data;
    int y_data;
    struct stack* next;
};

typedef struct stack stack_t;


void pushElement(int,int);
void popElement();
void printStack(stack_t* );
#endif