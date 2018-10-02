#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    perror("Could not close the file");
    exit(EXIT_FAILURE);
  }
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = openFile(filename);

  counts_t * c = createCounts();

  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    *strchr(line, '\n') = '\0';
    addCount(c, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
  }
  free(line);
  closeFile(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr,
            "Incorrect use! Need at least two arguments. Correct usage:\n./count_values "
            "key-value-file (input-files)\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open file for writing");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    closeFile(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
