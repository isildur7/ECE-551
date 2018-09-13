#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (expected_ans == power(x, y))
    return;
  else
    exit(EXIT_FAILURE);
}

int main() {
  run_check(2, 0, 1);
  run_check(0, 0, 1);
  run_check(2, 6, 64);
  run_check(1, 0, 1);
  run_check(5, 1, 5);
  run_check(-1, 2, 1);
  run_check(1, -4, 1);
  run_check(-1, 1, -1);

  return EXIT_SUCCESS;
}
