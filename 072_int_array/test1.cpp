#include <cstdlib>
#include <iostream>

#include "IntArray.h"

int main(void) {
  IntArray intArray(5);
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

  intArray3 = intArray4;

  if (intArray4 != intArray3) {
    std::cout << "The two int arrays are not the same\n";
  }
  else {
    std::cout << "The two int arrays are not different\n";
  }

  intArray3 = intArray;
  intArray2 = intArray4;

  if (intArray4 == intArray3) {
    std::cout << "The two int arrays are the same\n";
  }
  else {
    std::cout << "The two int arrays are different\n";
  }
  std::cout << intArray3 << "\n" << intArray2 << std::endl;
  std::cout << intArray[4] << "\n";
  std::cout << intArray2[1] << std::endl;
}
