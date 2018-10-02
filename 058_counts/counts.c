#include "counts.h"

#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ctCounts = malloc(sizeof(*ctCounts));
  if (ctCounts == NULL) {
    fprintf(stderr, "Allocation unsuccessful\n");
    exit(EXIT_FAILURE);
  }
  ctCounts->countsArray = malloc(sizeof(*ctCounts->countsArray));
  if (ctCounts->countsArray == NULL) {
    fprintf(stderr, "Allocation unsuccessful\n");
    exit(EXIT_FAILURE);
  }
  ctCounts->length = 0;
  ctCounts->unknownFrequency = 0;
  return ctCounts;
}

char * copyStrings(char * destination, const char * source) {
  size_t i = 0;
  while (source[i] != '\0') {
    destination = realloc(destination, (i + 2) * sizeof(*destination));
    if (destination == NULL) {
      fprintf(stderr, "Not enough space\n");
      exit(EXIT_FAILURE);
    }
    destination[i] = source[i];
    i++;
  }
  destination[i] = '\0';
  return destination;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknownFrequency++;
  }
  else {
    int i = 0;
    while (i < c->length) {
      if (strcmp(c->countsArray[i].string, name) == 0) {
        break;
      }
      i++;
    }
    if (i < c->length) {
      c->countsArray[i].frequency++;
    }
    else {
      c->countsArray = realloc(c->countsArray, (c->length + 1) * sizeof(*c->countsArray));
      if (c->countsArray == NULL) {
        fprintf(stderr, "Not enough space\n");
        exit(EXIT_FAILURE);
      }
      c->length++;
      c->countsArray[i].string = NULL;
      c->countsArray[i].string = copyStrings(c->countsArray[i].string, name);
      c->countsArray[i].frequency = 1;
    }
    // }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    fprintf(outFile, "%s: %d\n", c->countsArray[i].string, c->countsArray[i].frequency);
  }
  if (c->unknownFrequency != 0) {
    fprintf(outFile, "<unknown>: %d\n", c->unknownFrequency);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    free(c->countsArray[i].string);
  }
  free(c->countsArray);
  free(c);
}
