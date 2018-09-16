#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void testSeq(int * arr, size_t n, size_t ans) {
  if (ans == maxSeq(arr, n)) {
    printf("SUCcess\n");
    return;
  }
  printf("FailURE\n");
  exit(EXIT_FAILURE);
}

int main() {
  int arr1[] = {1, 2, 3, 4, 5, 5, 5, 5, 8, 9, 87, 5674};  //12
  int arr3[] = {-1, -7, -4, 0, 4, 7, 4};                  //7
  int arr4[] = {0};
  int arr5[] = {};
  int arr6[] = {0, -4, -6, -8, -7};

  testSeq(arr1, 12, 5);
  testSeq(arr3, 7, 5);
  testSeq(arr4, 1, 1);
  testSeq(arr5, 0, 0);
  testSeq(arr6, 5, 2);

  return EXIT_SUCCESS;
}
