#include "IntArray.h"

#include <assert.h>
#include <string.h>

#include <cstdio>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}

IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    data = temp;
    numElements = rhs.numElements;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements && index >= 0);
  const int & ref = data[index];
  return ref;
}

int & IntArray::operator[](int index) {
  assert(index < numElements && index >= 0);
  int & ref = data[index];
  return ref;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (*this == rhs) {
    return false;
  }
  return true;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  // if (rhs.size() != 0) {
  s.write("{", 1);
  for (int i = 0; i < rhs.size(); i++) {
    char asString[sizeof(rhs[i])];
    snprintf(asString, sizeof(rhs[i]), "%d", rhs[i]);
    s.write(asString, strlen(asString));
    if (i != rhs.size() - 1) {
      s.write(", ", 2);
    }
  }
  s.write("}", 1);
  //  }
  return s;
}
