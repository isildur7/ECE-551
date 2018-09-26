#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

void rot_matrix(FILE * f) {
  int i = 0;
  char array[MAX_SIZE][MAX_SIZE + 2];
  while (fgets(array[i], MAX_SIZE + 2, f) != NULL) {
    int yank = strchr(array[i], '\n') - array[i];
    if (yank != 10) {
      fprintf(stderr, "line too long\n");
      exit(EXIT_FAILURE);
    }
    i++;
    if (i > MAX_SIZE) {
      fprintf(stderr, "more than 10 lines\n");
      exit(EXIT_FAILURE);
    }
  }
  if (i < MAX_SIZE) {
    fprintf(stderr, "less than 10 lines\n");
    exit(EXIT_FAILURE);
  }

  char rotation[10][11];
  for (int old_i = 0; old_i < MAX_SIZE; old_i++) {
    for (int old_j = 0; old_j < MAX_SIZE; old_j++) {
      int new_i = old_j;
      int new_j = MAX_SIZE - old_i - 1;
      rotation[new_i][new_j] = array[old_i][old_j];
    }
    rotation[old_i][MAX_SIZE] = '\0';
  }
  for (i = 0; i < MAX_SIZE; i++) {
    fprintf(stdout, "%s\n", rotation[i]);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rot_matrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
