#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
  }
}

char ** getInput(FILE * f, int * p) {
  char * line = NULL;
  char ** data = NULL;
  size_t sz;
  *p = 0;
  while (getline(&line, &sz, f) >= 0) {
    data = realloc(data, (*p + 1) * sizeof(*data));
    if (data == NULL) {
      fprintf(stderr, "Cannot allocate enough memory\n");
      exit(EXIT_FAILURE);
    }
    data[*p] = line;
    line = NULL;
    (*p)++;
  }
  free(line);
  return data;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    //Read from stdin and print to stdout
    int len = 0;
    char ** input = getInput(stdin, &len);
    sortData(input, len);
    for (int i = 0; i < len; i++)
      free(input[i]);
    free(input);
    //printf("placeholder\n");
  }
  if (argc > 1) {
    // Loop over all the args and print to stdout
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      int len = 0;
      char ** input_data = getInput(f, &len);
      sortData(input_data, len);
      for (int i = 0; i < len; i++)
        free(input_data[i]);
      free(input_data);
      if (fclose(f) != 0) {
        perror("Failed to close input file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
