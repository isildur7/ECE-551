// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  return x + ((x + 1) * (x + 1));
}

int sumSeq2(int low, int high) {
  int sum = 0;
  if (low >= high) {
    return 0;
  }
  for (int i = low; i < high; i++) {
    sum += seq2(i);
  }
  return sum;
}

int main() {
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", -4, seq2(-4));
  printf("seq2(%d) = %d\n", 8, seq2(8));
  printf("seq2(%d) = %d\n", 2, seq2(2));
  printf("sumSeq2(%d, %d) = %d\n", -2, 6, sumSeq2(-2, 6));
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d, %d) = %d\n", 4, 5, sumSeq2(4, 5));
  printf("sumSeq2(%d, %d) = %d\n", 5, 5, sumSeq2(5, 5));

  return EXIT_SUCCESS;
}
