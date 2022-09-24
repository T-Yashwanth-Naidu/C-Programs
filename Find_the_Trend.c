#include<stdio.h>   


#define SIZE 10                                                             // Set the Size  of the array
int Input_array[SIZE];                                                      // The input array
//int start_count=0;                                                          // Start the count when elements are inputted
int Store_inc_array[SIZE][SIZE];                                            // Rows indicate Number of sets, and columns indicate elements.
int set,element_of_set=0;                                                   // Rows= set, elements_of_set=columns
int in_greater,in_lesser=0;                                                 // The ascending and descending flags
int ascending_count,equal,descending_count=0;                               // Counting of the trends
void Inc_array(int value)                                                   // This functions stores the element from the trend function.
{
    // if(start_count!= start_count++)                                     
    // {
        element_of_set++;                                                   // Increment the columns in the 2-D array
   // }

    if(in_greater==1 && in_lesser==1)                                       // If transition occurs, increment the rows in 2-D array and reset 
    {                                                                       // number of elements
        element_of_set=0;                                                   // When transition occurs, reset the columns
        set++;                                                              // and increment the rows
    }
    
    Store_inc_array[set][element_of_set]=value;                             // Store the value in required position.

    //printf("Store_inc_array[%d][%d]=%d\n",set,element_of_set,value);      // Print the values  (for checking  (under draft))

}

void findTrend()                                                            // This function finds the trend, ascending/descending
{
    for(char i=0;i<SIZE-1;i++)                                                // Run loop on each element; i
    {
        for(char j=i+1;j<SIZE;j++)                                          // Initialize next element to j
        {
            if(Input_array[i]>Input_array[j])                               // Compare current element with next element
            {
                in_greater=1;                                               // Flag for ascending
                ascending_count++;                                          // Increment the count for ascending
                printf(" %d is greater than %d\n",Input_array[i],Input_array[j]);
                Inc_array(Input_array[i]);                                  // Store the element

                break;                                                      // break when comparision is done and goto next element
            }

            else if ((Input_array[i]==Input_array[j]))                      // Checking for euality of elements
            {
                equal++;
                break;
            }
            

            else
            {
                descending_count++;                                         // Increment the descending counter
                in_lesser=1;                                                // Flag for descending 
                if((in_greater==1)&&(in_lesser==1) )                            // If transition occurs
                    Inc_array(Input_array[i]);                              // Store the i th element
                in_greater=0;                                               // Reset the greater flag to 0
                printf(" %d is less than %d\n",Input_array[i],Input_array[j]);
                break;                                                      // Break when comparision is done and goto next element
            }
            
        }
    }
}


// Prints the input array 
void printArray()
{
    printf("Input array is: ");
    for(int elements=0;elements<SIZE;elements++)
        printf(" %d ",Input_array[elements]);
    printf("\n\n");

}



void main()
{
    printf("Enter the elements( Signed/Unsigned):\n ");
    int get_val;
    for(int elements=0; elements<SIZE; elements++)                          // Get values from user
                 scanf("%d",&Input_array[elements]);                        // Enter intergers only.
    printArray();                                                           // Print the input array
    findTrend();                                                            // Find the trend

    if(equal==SIZE-1)                                                       // If all the elements are equal.
    {
        printf("\n All elements are equal\n");
    }
    else if(ascending_count>descending_count)                               // Ascending .
    {
        printf("\nAscending is the repeated trend\n ");
    }
    else if(ascending_count==descending_count)                              // If the trends are equal.
    {
        printf("\nAscending and Descending are of equal trends\n ");
    }
    
    else  if(descending_count>ascending_count)                              // Descending.
        printf("\nDescending is the repeated trend\n ");
    else{
        printf("No Op");                                                     // Still need to write conditions for test cases.
    }
}