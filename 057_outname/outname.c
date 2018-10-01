#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  if (inputName == NULL) {
    return NULL;
  }

  const char * addition = ".counts";
  size_t length = strlen(inputName) + 8;

  char * output = malloc(length * sizeof(*output));
  if (output == NULL) {
    fprintf(stderr, "Not enough memory\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i <= strlen(inputName); i++) {
    output[i] = inputName[i];
  }
  strcat(output, addition);
  return output;
}
