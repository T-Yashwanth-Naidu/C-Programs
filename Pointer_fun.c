#include<stdio.h>
#include<stdlib.h>


int main(int argc, char **argv)
{   

    // Fun with integer variable with different pointer types
    int int_var     =   13 ;
    int *ptr        =   NULL;                  // A interger pointer
    void *void_ptr  =   NULL;                  // A void pointer/Generic pointer

    int *int_ptr        = NULL;              // A integer pointer
    char *char_ptr      = NULL;            // A character pointer
    float *float_ptr    = NULL;          // A float pointer
    double *double_ptr  = NULL;        // A double pointer

    // Assigning the integer value to different types of pointers
    
    int_ptr     =  &int_var;        // Integer value to integer pointer
    char_ptr    =  &int_var;        // Integer value to character pointer | Should get a warning
    float_ptr   =  &int_var;        // Integer value to float pointer | Should get a warning
    double_ptr  =  &int_var;        // Integer value to double pointer | Should get a warning
    
    //NOTE: %p gives the address 

    // Lets print em

    printf("Address of int_var=  %p\n",&int_var);

    printf("\nAddress of the int pointer is %p\n",&int_ptr);
    printf("\nAddress of the char pointer is %p\n",&char_ptr);
    printf("\nAddress of the float pointer is %p\n",&float_ptr);
    printf("\nAddress of the double pointer is %p\n",&double_ptr);

    printf("\nAddress in the int pointer is %p, Value stored in the pointer is %d\n",int_ptr,*int_ptr);
    printf("\nAddress in the char pointer is %p, Value stored in the pointer is %c\n",char_ptr,*char_ptr);
    printf("\nAddress in the float pointer is %p, Value stored in the pointer is %f\n",float_ptr,*float_ptr);
    printf("\nAddress in the double pointer is %p, Value stored in the pointer is %lf\n",double_ptr,*double_ptr);
   
    printf("\n~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~\n");

    char char_var = 'c';

    int_ptr     =  &char_var;        // Char value to integer pointer | Should get a warning
    char_ptr    =  &char_var;        // Char value to character pointer 
    float_ptr   =  &char_var;        // Char value to float pointer | Should get a warning
    double_ptr  =  &char_var;        // Char value to double pointer | Should get a warning
    
    printf("Address of char_var=  %p\n",&char_var);

    printf("\nAddress of the int pointer is %p\n",&int_ptr);
    printf("\nAddress of the char pointer is %p\n",&char_ptr);
    printf("\nAddress of the float pointer is %p\n",&float_ptr);
    printf("\nAddress of the double pointer is %p\n",&double_ptr);

    printf("\nAddress in the int pointer is %p, Value stored in the pointer is %d\n",int_ptr,*int_ptr);
    printf("\nAddress in the char pointer is %p, Value stored in the pointer is %c\n",char_ptr,*char_ptr);
    printf("\nAddress in the float pointer is %p, Value stored in the pointer is %f\n",float_ptr,*float_ptr);
    printf("\nAddress in the double pointer is %p, Value stored in the pointer is %lf\n",double_ptr,*double_ptr);

    printf("\n~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~\n");


    float float_var =  3.141;

    int_ptr     =  &float_var;        // Float value to integer pointer | Should get a warning
    char_ptr    =  &float_var;        // Float value to character pointer | Should get a warning
    float_ptr   =  &float_var;        // Float value to float pointer 
    double_ptr  =  &float_var;        // Float value to double pointer | Should get a warning
    

    printf("Address of float_var=  %p\n",&float_var);

    printf("\nAddress of the int pointer is %p\n",&int_ptr);
    printf("\nAddress of the char pointer is %p\n",&char_ptr);
    printf("\nAddress of the float pointer is %p\n",&float_ptr);
    printf("\nAddress of the double pointer is %p\n",&double_ptr);

    printf("\nAddress in the int pointer is %p, Value stored in the pointer is %d\n",int_ptr,*int_ptr);
    printf("\nAddress in the char pointer is %p, Value stored in the pointer is %c\n",char_ptr,*char_ptr);
    printf("\nAddress in the float pointer is %p, Value stored in the pointer is %f\n",float_ptr,*float_ptr);
    printf("\nAddress in the double pointer is %p, Value stored in the pointer is %lf\n",double_ptr,*double_ptr);

    printf("\n~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~\n");

    double double_var =  12365.1177845962546;

    int_ptr     =  &double_var;        // Double value to integer pointer | Should get a warning
    char_ptr    =  &double_var;        // Double value to character pointer | Should get a warning
    float_ptr   =  &double_var;        // Double value to float pointer | Should get a warning
    double_ptr  =  &double_var;        // Double value to double pointer 
    

    printf("Address of double_var=  %p\n",&double_var);

    printf("\nAddress of the int pointer is %p\n",&int_ptr);
    printf("\nAddress of the char pointer is %p\n",&char_ptr);
    printf("\nAddress of the float pointer is %p\n",&float_ptr);
    printf("\nAddress of the double pointer is %p\n",&double_ptr);

    printf("\nAddress in the int pointer is %p, Value stored in the pointer is %d\n",int_ptr,*int_ptr);
    printf("\nAddress in the char pointer is %p, Value stored in the pointer is %c\n",char_ptr,*char_ptr);
    printf("\nAddress in the float pointer is %p, Value stored in the pointer is %f\n",float_ptr,*float_ptr);
    printf("\nAddress in the double pointer is %p, Value stored in the pointer is %lf\n",double_ptr,*double_ptr);

    printf("\n~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~\n");



    /*
    So you see the effects of wrong type assignment.     
    Wrong type casting is dangerous and can lead to breaking of the system. Be careful of the type you are using for the varaible
    More about void soon.
    */

     printf("\n~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~\n");
    /*
      Let us check with some different pointer types.
      1) Wild Pointer
      2) Dangling Pointer
      3) NULL Pointer
      4) Void Pointer
    */

    // A pointer pointing to a location that has been deleted/freed is known as Dangling Pointer
    
    int *dangling =  NULL ; // NULL Pointer: Initializing a pointer with NULL is known as NULL pointer
    /*
     What happens if you de-reference a NULL pointer? Well, its not a good idea as it will lead to Segmentaiton Fault. 
     Yeah , don't dereference a NULL pointer. It is a great practice to check if a pointer is NULL or not before de-referencing it.
    */

    //printf("DANGLING POINTER contains the value %d\n",*dangling);

    //Now with Dangling
    printf("\n~~~~~~~~~~~~~~~~~~~~~  ABOUT DANGLING  ~~~~~~~~~~~~~~~~~~~\n");
    if(dangling ==NULL)
        printf("\n\nWARNING! It is a NULL pointer. Dosen't contain any address\n\n");

    dangling=(int*)malloc(sizeof(int)); // Initializes memory to store 4 integers
    printf("\nSize of Integer varaiable is : %ld\n",sizeof(int));


    if(dangling)
    printf("\nSome Random varaibles are stored here. The pointer does have an address where data can be placed\n");
    printf("The random variable is: %d\n",*dangling);

    *dangling = 0xffffffff;
    printf("Address of value pointed by dangling: %p\n",dangling);
    printf("Address of value  dangling: %p\n",&dangling);

    printf("\nValue stored by Dangling Pointer: %x\n",*dangling);

    // What if i do *dangling+1 ? Let's check

    for(int i=0;i<6;i++)
    {
        *(dangling+i)=350000+i;
        printf("Address  of *(dangling  + %d): %p, Value  stored by *(dangling  + %d) is: %d\n",i,(dangling  + i),i,*(dangling+i));
    }

    // Why the above? Lets see by using the free.

    free(dangling);
    // Once freed, the "dangling" pointer that we declared becomes a Dangling Pointer
    

    printf("\nAFTER FREEING:\n");
    printf("\nValue stored by Dangling Pointer: %x\n",*dangling); //Pointer points to the memory after being freed
    // free() dosen't change the value of dangling, but it still points to chuck of memory that malloc() gave.
    // Now the heap allocator, the one responsible for dynamic memory allocation is ready to give away that location.

    for(int i=0;i<6;i++)
    {
        
        printf("Address  of *(dangling  + %d): %p, Value  stored by *(dangling  + %d) is: %d\n",i,(dangling  + i),i,*(dangling+i));
    }

    /*  Observed anything? Yep.
        The starting 4 locations pointed by the pointer are storing garbage value. but the remaining locations store the values that
        are initialized. But the base pointer is lost once freed, hence it is difficult to get the values from those locations 
        unless they are stored.
    */

    // ~~~~~~~~~~~~~~~~~~~~~  ABOUT WILD  ~~~~~~~~~~~~~~~~~~~
    // So now what are wild pointers?
    // The uninitialized pointers are called as WILD POINTERS

    int *Wild_ptr;
    /*Yeah, that's it. That's the WILD POINTER. A pointer that is not initialized. 
    If this Wild_ptr is dereferrenced, we will see unexpected behaviour by the compiler, like Segmentation Fault.*/

    //printf("Address  of Wild_ptr : %p, Value  stored by *(Wild_ptr) is: %d\n",Wild_ptr,*(Wild_ptr));
    // The above gives Seg Fault

    printf("\n~~~~~~~~~~~~~~~~~~~~~  ABOUT VOID  ~~~~~~~~~~~~~~~~~~~\n");
    //Now let us look at void pointer
    int_var =  215;

     void_ptr    =  &int_var;      //   Integer value to void pointer | ERROR! */
     //void_ptr    =  &char_var;      //   Char value to void pointer | ERROR! */
     //void_ptr    =  &float_var;      // Float value to void pointer | ERROR! */
     //void_ptr    =  &double_var;      // Double value to void pointer | ERROR! */

    //printf("\nVoid pointer address is: %p, Value stored in the pointer is %d\n",*void_ptr); 
    // The above statement should give error as it is a must to externally type cast void pointer    
    
    // You can either type cast it where it is being used or you can type cast it during initialization

    printf("\nVoid pointer(int *) address is: %p, Value stored in the pointer is %d\n",void_ptr,*((int *)void_ptr)); 
    // The above statement would be the right use of void pointer

    // What if the external type casting is wrong for void pointer?
    // Lets find out
    printf("\nVoid pointer(char *) address is: %p, Value stored in the pointer is %c\n",void_ptr,*((char *)void_ptr)); 
    printf("\nVoid pointer(float *) address is: %p, Value stored in the pointer is %f\n",void_ptr,*((float *)void_ptr)); 
    printf("\nVoid pointer(double *) address is: %p, Value stored in the pointer is %lf\n",void_ptr,*((double *)void_ptr)); 


    // THE TRUE WAY TO USE THE %p. Use it with generic pointer and a good use of void pointer is as below
    void *true_ptr = NULL;
    int some_int_val = 10;
    char some_char_val = '1';
    float some_float_val = 3.141;
    double some_double_val  = 3.14159265358979;

    true_ptr = &some_int_val;
    printf("\nAddress of true_ptr is: %p, Address pointed by true_ptr: %p, Value in  true_ptr:%d \n", 
    &true_ptr,  true_ptr, *((int*)true_ptr));    

    true_ptr = &some_char_val;
    printf("\nAddress of true_ptr is: %p, Address pointed by true_ptr: %p, Value in  true_ptr:%c \n", 
    &true_ptr,  true_ptr, *((char*)true_ptr));    

    true_ptr =  &some_float_val;
    printf("\nAddress of true_ptr is: %p, Address pointed by true_ptr: %p, Value in  true_ptr:%f \n", 
    &true_ptr,  true_ptr, *((float*)true_ptr));    

    true_ptr = &some_double_val;
    printf("\nAddress of true_ptr is: %p, Address pointed by true_ptr: %p, Value in  true_ptr:%lf \n", 
    &true_ptr,  true_ptr, *((double*)true_ptr));    

    /* As you can see in the output, the same pointer is pointing to different address.
     Yeah, a void pointer can be used to derefence any pointer type.*/




    /*
     CAME THIS FAR? Why not go ahead with Dynamic Memory Allocation?
     Well, there are just a few handfull of Dynamic Mem functions.
     1) MALLOC
     2) CALLOC
     3) REALLOC
     4) FREE
     */
    

    // More Soon. Stay Tuned!

    












    return 0;
}