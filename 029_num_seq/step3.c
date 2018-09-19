// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return x * (y - 3) + y * 2;
}

int countEvenInSeq3Range(int xLow, int xHigh, int yLow, int yHigh) {
  int numEven = 0;

  if ((xLow == xHigh) && (yLow == yHigh))
    return 0;

  if (xLow == xHigh) {
    for (int j = yLow; j < yHigh; j++) {
      if (seq3(xLow, j) % 2 == 0)
        numEven++;
    }
  }
  if (yLow == yHigh) {
    for (int j = xLow; j < xHigh; j++) {
      if (seq3(j, yLow) % 2 == 0)
        numEven++;
    }
  }

  for (int i = xLow; i < xHigh; i++) {
    for (int j = yLow; j < yHigh; j++) {
      if (seq3(i, j) % 2 == 0)
        numEven++;
    }
  }
  return numEven;
}

int main() {
  printf("seq3(%d, %d) = %d\n", 2, -5, seq3(2, -5));
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));
  printf("seq3(%d, %d) = %d\n", 3, 2, seq3(3, 2));
  printf("seq3(%d, %d) = %d\n", -4, -1, seq3(-4, -1));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 9, 2, 0, 3, countEvenInSeq3Range(9, 2, 0, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 3, 3, countEvenInSeq3Range(0, 0, 3, 3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         0,
         -5,
         3,
         countEvenInSeq3Range(0, 0, -5, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 7, 3, 3, countEvenInSeq3Range(0, 7, 3, 3));

  return EXIT_SUCCESS;
}
