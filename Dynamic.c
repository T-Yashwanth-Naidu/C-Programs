#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// In this article, lets explore about Dynamic Memory allocation functions and a bit about memory allocator.
/*
In C, We use the following 4 primitive functions for Dynamic Memory Allocation.
1) Malloc
2) Calloc
3) Realloc
4) Free

Well, the above are commonly heard and commonly seen. What are some other Memory allocator functions that work Behind
the screen to keep the above functions working?
1) brk
2) sbrk
3) mmap

Combined with the commonly heard, we shall go through a little bit working of the above functions.
*/


int main(int argc,char **argv;)
{

/* Using brk()*/
long int page_size = sysconf(_SC_PAGESIZE);
printf("The page size is: %ld\n",page_size);

void *point1 =sbrk(0);              // Gives present location
printf("The current program address break is at: %p\n",point1);

point1 = (void*) ((char*)point1+1); // Increments the brk
printf("Point 1 after incrementing: %p\n",point1);

brk(point1);    // Assigns 0 at this location

void *point2 =sbrk(0);              // Gives present location
printf("The current program address break is at: %p\n",point2);

/*
( Check with the output image parallely Img 1)
As seen in the output above, the page size in my system is 4096. 
By using sbrk(0), we can get the current address of program break.
Now we are incrementing the program break by 1.
The brk() sets the end of program break specified by point1. Hence, the program break should now be at
previous_address + 1 byte location.
We can check that by again calling sbrk(0).
*/
/* Checking the assembly of brk()*/

return 0;
}

