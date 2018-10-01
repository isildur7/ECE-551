#include "kv.h"

#include <stdio.h>
#include <string.h>

FILE * openFile(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  return f;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  // Function which opens file and handles errors
  FILE * f = openFile(fname);

  // Get space for array of kv structures
  kvarray_t * kvt_arr = malloc(sizeof(*kvt_arr));
  kvt_arr->kvarray = malloc(sizeof(*kvt_arr->kvarray));

  // For the getline function
  char * line = NULL;
  size_t sz;

  // set current length 0, this will increase for every line added and
  // will also as the iterator
  kvt_arr->length = 0;

  // run getline while a line exists
  while (getline(&line, &sz, f) >= 0) {
    // First increase the size of the kv structure array
    kvt_arr->kvarray = realloc(kvt_arr->kvarray, (kvt_arr->length + 1) * sizeof(*kvt_arr->kvarray));

    // error handling
    if (kvt_arr->kvarray == NULL) {
      fprintf(stderr, "Cannot allocate enough memory\n");
      exit(EXIT_FAILURE);
    }

    // Key is the first field, from start to the first '='. Find length by pointer substraction
    // Value is rest of the line till '\n'
    int length_key = strchr(line, '=') - line;
    int length_val = strchr(line, '\n') - strchr(line, '=') - 1;

    // Because kvt_arr->length is also the iterator, we will always be adding new blocks at
    // kvarray[kvt_arr->length]
    // Now inside that structure, allocate space for key and value using the calculated lengths
    kvt_arr->kvarray[kvt_arr->length].key =
        malloc((length_key + 1) * sizeof(*kvt_arr->kvarray[kvt_arr->length].key));
    kvt_arr->kvarray[kvt_arr->length].value =
        malloc((length_val + 1) * sizeof(*kvt_arr->kvarray[kvt_arr->length].value));

    // Now copy each character from the line to respective fields using again the lengths
    // obtained above. From [0,length_key) is the key and
    // [length_key + 1, length_key + 1 + length_val) is the value
    // Don't forget the '\0' characters at the end for both the strings.
    int i;
    for (i = 0; i < length_key; i++) {
      kvt_arr->kvarray[kvt_arr->length].key[i] = line[i];
    }
    kvt_arr->kvarray[kvt_arr->length].key[i] = '\0';

    for (i = i + 1; i < length_key + length_val + 1; i++) {
      kvt_arr->kvarray[kvt_arr->length].value[i - length_key - 1] = line[i];
    }
    kvt_arr->kvarray[kvt_arr->length].value[i - length_key - 1] = '\0';

    // free line to avoid potential leaks
    free(line);
    line = NULL;

    // length increases by one for each iteration
    (kvt_arr->length)++;
  }
  // free line after last iteration because getLine still works one more time
  free(line);
  // also close the file now that the data has been read
  if (fclose(f) != 0) {
    perror("Failed to close input file");
    exit(EXIT_FAILURE);
  }

  return kvt_arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  // Free in reverse order of mallocs and free everything inside the structures
  // Just iterate over the kv array using its length and free the keys and values.
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->kvarray[i].key);
    free(pairs->kvarray[i].value);
  }
  // Now free the array
  free(pairs->kvarray);
  // And finally, free the whole big struct
  free(pairs);
  // "Mr. Chaware, I don't feel so good" - pairs
  return;
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  // Just iterate over the kv array using its length and print out the keys and values
  // from every pair
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s', value = '%s'\n", pairs->kvarray[i].key, pairs->kvarray[i].value);
  }
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t counter = 0; counter < pairs->length; counter++) {
    if (strcmp(pairs->kvarray[counter].key, key) == 0) {
      return pairs->kvarray[counter].value;
    }
  }
  return NULL;
}
