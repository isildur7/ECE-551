#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low + 2 > high) {
    return low;
  }
  int c = f->invoke((low + high) / 2);
  if (c > 0) {
    return binarySearchForZero(f, low, (low + high) / 2);
  }
  else if (c < 0) {
    return binarySearchForZero(f, (low + high) / 2, high);
  }
  return (low + high) / 2;
}
