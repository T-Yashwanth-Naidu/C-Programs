/*

Output:

*****
 ***
  *

*/
#include <stdio.h>
void pattern(int n) {

  for (int i = n; i > 0; i--) {

    for (int j = 0; j < n - i; j++) {
      printf(" ");
    }
    for (int j = 0; j < 2 * i - 1; j++) {
      printf("*");
    }
    for (int j = 0; j < n - i; j++) {
      printf(" ");
    }
    printf("\n");
  }
}

int main() {
  int size;
  printf("Enter size: ");
  scanf("%d", &size);
  pattern(size);
}