/*

Output: 
* * *
* *
*

*/
#include<stdio.h>
void pattern(int n) {

	for(int i=n;i>0;i--){
		for(int j=n;j>0;j--){
			if(j<=i) printf("* ");
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