#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

char *head=NULL;
int count=1;
int total_allocated=0;
int allocation_from_start=0;

char *allocate_memory(char *current_address,int bytes)
{
     printf("\nAllocation - %d\n",count);
    count++;
    total_allocated+=bytes;
    char *temp=NULL;
    printf("Current address: %p\n",current_address);
    printf("Head is at: %p\n",head); 

    temp=(char*)sbrk(bytes);
    printf("Printing temp: %p\n",temp);

    if(  temp  ==  (char*)-1)
        printf("\n\n\n\nSbreak allocation error\n\n\n\n");

    allocation_from_start= allocation_from_start+(temp - current_address);
    printf("Address range:%p to %p available\n",current_address,temp);
    printf("Allocated:   %ld bytes\n",temp - current_address);
    return temp;
}

int main(int argc, char *argv[])
{


   char *current_address=NULL;   
   int number_to_allocate;
   current_address=(char*)sbrk(0);
   printf("\nSBRk:%p\n",(char*)sbrk(0));

  head=current_address;  
  printf("Allocation starts at: %p\n",head);

    //Allocation-1
   number_to_allocate=256;
   current_address=allocate_memory(current_address,number_to_allocate);
   printf("\nSBRk:%p\n",(char*)sbrk(0));

   //Allocation-2
   number_to_allocate=256;
   current_address=allocate_memory(current_address,number_to_allocate);
   printf("\nSBRk:%p\n",(char*)sbrk(0));
   
   //Allocation-3
   number_to_allocate=256;   
   current_address=allocate_memory(current_address,number_to_allocate);
   printf("\nSBRk:%p\n",(char*)sbrk(0));
   
   //Allocation-4
   number_to_allocate=256;
   current_address=allocate_memory(current_address,number_to_allocate);
   printf("\nSBRk:%p\n",(char*)sbrk(0));
   
   
   printf("\nAllocated total: %d bytes\n",total_allocated);
   printf("Total available range: %p to %p\n",head,current_address);
   
   int i;
   for(i=0;i<total_allocated;i++)
   {
    *(head+i)=i;
    
    if(((i>=0)&&(i<=2))||(i==total_allocated-1))    
        printf("Address: %p, value= %d\n",(head+i),*(head+i));
   }

    //Read data from allcoated locations
    int read,j;
    
    for(j=0;j<total_allocated;j++)
    {
        
        read=*(head+j);        
        if(((j>=0)&&(j<=2))||(j==total_allocated-1))    
            printf("Reading from....Address: %p, value= %d\n",(head+j),read);
    }
   
    printf("\nData read from allocated locations\n");
    printf("Trying to access last location *(head+j-1) %p:  %d \n",(head+j-1),*(head+j-1));
    printf("Trying to access jth location  *(head+j) %p:  %d \n",(head+j),*(head+j));        // Invalid read
    printf("Trying to access next location  *(head+j+1) %p:  %d \n",(head+j+1),*(head+j+1)); // Invalid read
    printf("\nNumber of bytes allocated from start: %d\n",allocation_from_start);
    printf("...Proceeding for deallocation\n");
    char *toDeallocate=NULL;
    toDeallocate=sbrk(-allocation_from_start);
    printf("\nSBRk:%p\n",(char*)sbrk(0) );
    j=0;
    printf("\nData read from De-allocated locations\n");
    printf("Trying to access last location *(head+j-1) %p:  %d \n",(head+j-1),*(head+j-1));
    printf("Trying to access jth location  *(head+j) %p:  %d \n",(head+j),*(head+j));        // Invalid read
    printf("Trying to access next location  *(head+j+1) %p:  %d \n",(head+j+1),*(head+j+1)); // Invalid read
   
   
}