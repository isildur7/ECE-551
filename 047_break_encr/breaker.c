#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int frequencyFinder(int * array, size_t len, FILE * f) {
  char c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      array[c - 'a']++;
    }
  }
  int high = 0;
  for (size_t i = 0; i < len; i++) {
    if (array[i] > array[high])
      high = i;
  }
  return high;
}

void findKey(FILE * f) {
  int frequency_array[26] = {0};
  int high = frequencyFinder(frequency_array, 26, f);
  // printf("high = %d\n", high);

  int key = 0;
  char highest_char = high + 'a';

  if (highest_char < 'e') {
    key = 26 + highest_char - 'e';
  }
  else {
    key = highest_char - 'e';
  }

  printf("%d\n", key);
  return;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  findKey(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
