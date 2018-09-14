// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return (-3 + 4 * x);
}

void printSeq1range(int low, int high) {
  if (low >= high) {
    printf("\n");
    return;
  }
  for (int i = low; i <= high; i++) {
    printf("%d", seq1(i));
    if (i >= high) {
      printf("\n");
      return;
    }
    printf(", ");
  }
}

int main() {
  printf("seq1(%d) = %d\n", -4, seq1(-4));
  printf("seq1(%d) = %d\n", -1, seq1(-1));
  printf("seq1(%d) = %d\n", 9, seq1(9));
  printf("seq1(%d) = %d\n", 3, seq1(3));
  printf("printSeq1Range(%d, %d)\n", 6, 3);
  printSeq1range(6, 3);
  printf("printSeq1Range(%d, %d)\n", -4, 4);
  printSeq1range(-4, 4);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1range(0, 0);
  printf("printSeq1Range(%d, %d)\n", 3, 10);
  printSeq1range(3, 10);
  return EXIT_SUCCESS;
}
