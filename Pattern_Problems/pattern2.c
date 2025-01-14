/*

Output: 
* 
* *
* * *

*/
#include<stdio.h>
void pattern(int n) {
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
		{
			if(j<=i){
				printf("* ");
			}
		}
		printf("\n");
	}

}

int main(){
    int size;
    printf("Enter size: ");
    scanf("%d",&size);
    pattern(size);
}
