#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * charArray = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    charArray[i] = 0;
  }
  std::ifstream f;
  f.open(fname, std::istream::in);
  if (f.fail()) {
    std::cerr << "error opening this file!\n";
    exit(EXIT_FAILURE);
  }
  else {
    char nextChar = f.get();
    while (nextChar != EOF) {
      charArray[(unsigned char)nextChar]++;
      nextChar = f.get();
    }
    charArray[256] = 1;
  }
  f.close();
  return charArray;
}
