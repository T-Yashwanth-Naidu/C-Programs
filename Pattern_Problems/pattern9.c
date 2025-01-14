/*

Output:

*
**
***
**
*

*/
#include <stdio.h>
void pattern(int n) {

  for (int i = 0; i < 2 * n - 1; i++) {

    if (i < n) {
      for (int j = 0; j < i + 1; j++) {
        printf("*");
      }
    }
    if (i >= n) {
      for (int j = 0; j < 2 * n - 1 - i; j++)
        printf("*");
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