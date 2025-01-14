/*

Output:

A
B B
C C C

*/
#include <stdio.h>
void pattern(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j <= i) {
        printf("%c ", i + 65);
      }
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