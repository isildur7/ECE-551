#include "bstmap.h"

int main(void) {
  BstMap<int, int> a;
  a.add(45, 0);
  a.add(34, 1);
  a.add(24, 2);
  a.add(56, 3);
  a.add(12, 4);
  a.add(13, 5);
  a.add(49, 6);
  a.add(67, 7);
  a.add(4, 8);
  BstMap<int, int> b(a);
  b.printTree();
  std::cout << a.lookup(56) << std::endl;
  // std::cout << a.lookup(52) << std::endl;
  a.remove(49);
  a.printTree();
}
