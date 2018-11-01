#include "ll.h"

int main(void) {
  LinkedList<int> a;
  a.printList();
  std::cout << a.getSize() << std::endl;
  a.addBack(4);
  a.printList();
  std::cout << a.getSize() << std::endl;
  /*a.addFront(3);
  a.printList();
  std::cout << a.getSize() << std::endl;*/

  LinkedList<int> b;
  b.addFront(5);
  b.printList();
  b.addBack(6);
  b.printList();
  b.addBack(4);
  b.printList();

  LinkedList<int> c(b);
  c.printList();
  std::cout << c.getSize() << std::endl;
  c.addFront(2);
  c.printList();
  std::cout << c.getSize() << std::endl;

  LinkedList<int> d;
  d = c;
  d.printList();
  std::cout << d.getSize() << std::endl;
  d = a;
  d.printList();
  std::cout << d.getSize() << std::endl;
  std::cout << d.remove(28) << std::endl;
  std::cout << d.remove(4) << std::endl;
  d.printList();
  d = b;
  //std::cout << d[1] << std::endl;
  d[1] = 10;
  //std::cout << d[1] << std::endl;
  // std::cout << d.find(d[1]) << std::endl;
  //  std::cout << d.find(1) << std::endl;
  std::cout << d.remove(d[1]) << std::endl;
  d.printList();
  std::cout << d.getSize() << std::endl;
  return EXIT_SUCCESS;
}
