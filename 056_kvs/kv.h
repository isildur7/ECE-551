#ifndef __KV_H__
#define __KV_H__
#include <stdio.h>
#include <stdlib.h>

struct _kvpair_t {
  //DEFINE ME!
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  //DEFINE ME!
  kvpair_t * kvarray;
  size_t length;
};
typedef struct _kvarray_t kvarray_t;

FILE * openFile(const char * filename);

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
