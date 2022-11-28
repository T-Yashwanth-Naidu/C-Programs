#include<stdio.h>
#include<stdlib.h>
#include"trace_retrace.h"
#include"Stack.h"



void main()
{

    generate_coordinates();
    printf("....Coordinates generated.....\n");    
    while(1){   

    printf("\n~~~~~~~~~~~Choose your action from the following~~~~~~~~~~~\n");
    printf("1)Trace the path\t2)Go back to home\t3) Print Coordinates\t4)To Home directly\n");
    int choice;
    scanf("%d",&choice);
    switch(choice){

        case  1:    goto_destination();
                    break;
        
        case  2:    printf("\n...Traces back to home step by step...\n");
                    back_to_home();
                    break;

        case  3:    print_coordinates();
                    break;


        case  4:     printf("\n...Traces back to home directly...\n");
                    to_home_at_once();
                    break;

        default:    printf("ENTER VALID OPTION\n");
                    break;

    }
    }
    
}