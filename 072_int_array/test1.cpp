#include <cstdlib>
#include <iostream>

#include "IntArray.h"
int main(void) {
  IntArray intArray(10);
  for (int i = 0; i < intArray.size(); i++) {
    intArray[i] = i * i;
  }
  IntArray intArray2(intArray);
  IntArray intArray3(0), intArray4;

  if (intArray != intArray2) {
    std::cout << "The two int arrays are not the same\n";
  }
  else {
    std::cout << "The two int arrays are not different\n";
  }
  if (intArray4 != intArray3) {
    std::cout << "The two int arrays are not the same\n";
  }
  else {
    std::cout << "The two int arrays are not different\n";
  }
  std::cout << intArray3 << "\n" << intArray4 << std::endl;
}
