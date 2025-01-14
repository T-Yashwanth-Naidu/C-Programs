#include <stdio.h>
#include <stdlib.h>
#define SIZE 64
char *convertobinary(int);
char storenum[SIZE] = {0};
void checkendian();

int main() {

  int num1;
  char *binNum = NULL;
  printf("Enter a number: ");
  scanf("%d", &num1);
  checkendian();
  binNum = convertobinary(num1);
}

char *convertobinary(int num1) {
  int tempnum = num1;
  int num2, i = 0;

  printf("...Converting to binary...\n");
  while (tempnum != 0) {
    num2 = tempnum % 2;
    storenum[i] = num2;
    tempnum /= 2;
    i++;
  }

  printf("...Conversion succesfull...\nConverted number is:\t ");

  for (i = 0; i < SIZE; i++) {
    if (i % 8 == 0)
      printf("  ");
    printf("%d", storenum[i]);
    if (i == SIZE - 1)
      printf("\n");
  }
  return storenum;
}

void checkendian() {
  int tempval = 0x12345678, i;
  char *store = (char *)&tempval;
  printf("Sizeof int is %ld\n", sizeof(int));
  for (i = 0; i < sizeof(int); i++)
    printf("%.1x", store[i]);

  printf("\n");
  if (store[0] == 0x12)
    printf("System is BIG ENDIAN\n");
  else
    printf("System is LITTLE ENDIAN\n");
  printf("\n");
}
