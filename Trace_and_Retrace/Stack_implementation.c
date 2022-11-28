#include"stack.h"
#include"trace_retrace.h"

int stack_count;
stack_t  *head=NULL;                                                    // Create Head Globally


void pushElement(int temp_x,int temp_y){                               //Function to push elements into stack.
        
   if(stack_count==POINTS-1)
   {
    printf("...REACHED DESTINATION...\n");
   }

        stack_t *new=NULL;                                              // Init a temp stack     
        
        new= (stack_t *)malloc(sizeof(stack_t));                        // Create a stack        
        new->x_data=temp_x;
        new->y_data=temp_y;
        new->next=head;        

        printf("Current location : (%d,%d)  \n",temp_x,temp_y);
        head=new;                                                       // Point back to head
        stack_count++;
printStack(head);
}

void popElement(){                                                      // Pop elements out of stack
    stack_t * temp=head;
    
    if(head==NULL)                                                      // If not elements present, print error msg.
    {
        printf("...ALREADY AT HOME...\n");
    }
    else{                                                               // If present, Pop the latest element out.

        printf("Left (%d,%d) \n",temp->x_data,temp->y_data);        
        head=head->next;
        
        free(temp);                                                     //  Free memory of the popped element.        
        stack_count--;
    }
printStack(head);
}


void printStack(stack_t* head)                                          //  Print elements of the stack
{
    int i=0;
    if(head==NULL)                                                      // If no elements are present, print err msg.
    {     
        printf("\n...REACHED HOME...\n");
    }
    else{        
        while(head)
        {
            printf("(%d,%d)--",x_coordinates[i],y_coordinates[i]);
            head=head->next;
            i++;
        }
    }
}
