#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t maxlen = 1;
  size_t len = 1;
  if (n == 0)
    return 0;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      len++;
    }
    else {
      if (len > maxlen)
        maxlen = len;
      len = 1;
    }

    if (len > maxlen)
      maxlen = len;
  }
  return maxlen;
}
