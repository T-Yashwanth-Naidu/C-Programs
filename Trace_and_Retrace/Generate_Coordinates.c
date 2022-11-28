#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"trace_retrace.h"
#include"Stack.h"

int x_coordinates[POINTS];
int y_coordinates[POINTS];
int count_x=-1;
int count_y=-1;
static int called=0;
static int called_count;

// FUNCTIONS FOR COORDINATES

int get_x_coordinates()
{    
    int x = rand();            
    if((x>1000000000)||(x>10000000))
    { 
        x=x/10000000;
        count_x++;
    }        
    return x;
}

int get_y_coordinates()
{

    int y;
    y =  rand();        
    if((y>1000000000)||(y>10000000))
    { 
        y=y/10000000;
        count_y++;
    }            
    return y;
}

void generate_coordinates()
{
    srand(time(0));
    int store_x_val;
    int store_y_val;
    for(int generate_points=0;generate_points<POINTS;generate_points++)
    {
        store_x_val=get_x_coordinates();
        store_y_val=get_y_coordinates();
        x_coordinates[count_x]=store_x_val;
        y_coordinates[count_y]=store_y_val;
    }
}

void print_coordinates()
{
    for(int i=0;i<POINTS;i++)
    {
        printf("Coordinate %d: [ %d, %d ] \n",i+1,x_coordinates[i],y_coordinates[i]);
    }
}



// FUNCTIONS FOR TRAVERSING

void goto_destination()
{
    
    if(called==POINTS-1)
    {
        printf("\n....REACHED DESTINATION...\n");
    }
    if(called_count<POINTS)
    {
        pushElement(x_coordinates[called],y_coordinates[called]);
        called++;
        called_count++;
    }
    else{
        printf("\n....NO COORDINATES TO TRAVEL....\n");
    }
}

void back_to_home()
{
    
    
    if( (called>0) && (called<=POINTS) )
    {
        popElement();
        called--;
        called_count--;
    }
    else{
        printf("\n....YOU ARE AT HOME....\n");
    }
    

}

void to_home_at_once()
{
    
    
    while( (called>0) && (called<=POINTS) )
    {
        popElement();
        called--;
        called_count--;
        
    }
    
    printf("\n....YOU ARE AT HOME....\n");
    

}