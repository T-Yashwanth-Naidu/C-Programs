/*
Output: 

1 2 3
1 2
1

*/
#include<stdio.h>
void pattern(int n) {
    
    for(int i=n;i>0;i--){
        for(int j=1;j<=i;j++){
             printf("%d ",j);
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