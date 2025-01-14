/*
Output: 
1
2 2 
3 3 3

*/
#include<stdio.h>

void pattern(int n) {
	for(int i=0;i<n;i++){
	for(int j=0;j<=i;j++){
		if(j<=i){
			printf("%d ",i+1);
		}
		
	}printf("\n");
}
}

int main(){
    int size;
    printf("Enter size: ");
    scanf("%d",&size);
    pattern(size);
}