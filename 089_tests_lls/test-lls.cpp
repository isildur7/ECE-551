#include <cassert>
#include <cstdlib>
#include <exception>
#include <stdexcept>

#include "il.h"

void testList(void) {
  IntList l = IntList();
  try {
    l[0];  //out of range should happen
    assert(false);
  }
  catch (std::exception &) {
  }
}
int main(void) {
  testList();
  return EXIT_SUCCESS;
}
/*#include <cstdlib>
#include <iostream>

#include "il.h"

int main(void) {
  testList();
  return EXIT_SUCCESS;
}

void testList(void) {
  IntList a;

  if (a.head != NULL)
    exit(EXIT_FAILURE);
  if (a.tail != NULL)
    exit(EXIT_FAILURE);
  if (a.getSize() != 0)
    exit(EXIT_FAILURE);

  a.addFront(3);
  if (a.head != a.tail)
    exit(EXIT_FAILURE);
  if (a.getSize() != 1)
    exit(EXIT_FAILURE);
  if (a.head->data != 3)
    exit(EXIT_FAILURE);

  a.addFront(4);
  if (a.head->next != a.tail)
    exit(EXIT_FAILURE);
  if (a.head->data != 4)
    exit(EXIT_FAILURE);
  if (a.getSize() != 2)
    exit(EXIT_FAILURE);

  IntList b;

  b.addBack(3);
  if (b.head != b.tail)
    exit(EXIT_FAILURE);
  if (b.getSize() != 1)
    exit(EXIT_FAILURE);
  if (b.head->data != 3)
    exit(EXIT_FAILURE);

  b.addBack(4);
  if (b.head->next != b.tail)
    exit(EXIT_FAILURE);
  if (b.head->data != 3)
    exit(EXIT_FAILURE);
  if (b.getSize() != 2)
    exit(EXIT_FAILURE);

  IntList c(a);
  if (c.head == a.head)
    exit(EXIT_FAILURE);
  if (c.head->next == a.head->next)
    exit(EXIT_FAILURE);
  if (a.tail == c.tail)
    exit(EXIT_FAILURE);
  if (c.head->data != a.head->data)
    exit(EXIT_FAILURE);

  a = b;
  if (b.head == a.head)
    exit(EXIT_FAILURE);
  if (b.head->next == a.head->next)
    exit(EXIT_FAILURE);
  if (a.tail == b.tail)
    exit(EXIT_FAILURE);
  if (b.head->data != a.head->data)
    exit(EXIT_FAILURE);

  a.addBack(3);
  if (a.find(2) != -1)
    exit(EXIT_FAILURE);
  if (a.find(3) != 0)
    exit(EXIT_FAILURE);
  if (a.find(4) != 1)
    exit(EXIT_FAILURE);

  if (a.remove(4) != true)
    exit(EXIT_FAILURE);
  if (a.remove(2) != false)
    exit(EXIT_FAILURE);

  if (a.head->next != a.tail)
    exit(EXIT_FAILURE);
  if (a.getSize() != 2)
    exit(EXIT_FAILURE);
  if (a.head->data != 3)
    exit(EXIT_FAILURE);

  if (a.remove(3) != true)
    exit(EXIT_FAILURE);
  if (a.head != a.tail)
    exit(EXIT_FAILURE);
  if (a.getSize() != 1)
    exit(EXIT_FAILURE);
  if (a.head->data != 3)
    exit(EXIT_FAILURE);

  if (a.remove(3) != true)
    exit(EXIT_FAILURE);
  if (a.head != NULL)
    exit(EXIT_FAILURE);
  if (a.getSize() != 0)
    exit(EXIT_FAILURE);

  if (a.remove(3) != false)
    exit(EXIT_FAILURE);
  if (a.getSize() != 0)
    exit(EXIT_FAILURE);
  if (a.head != a.tail)
    exit(EXIT_FAILURE);

  b.addBack(5);
  b.addFront(6);
  if (b.getSize() != 4)
    exit(EXIT_FAILURE);
  if (b[3] != b.tail->data)
    exit(EXIT_FAILURE);
  if (b[0] != 6 || b[1] != 3)
    exit(EXIT_FAILURE);
  if ((b[0]) != b.head->data)
    exit(EXIT_FAILURE);

  b[2] = 8;
  if (b[2] != 8)
    exit(EXIT_FAILURE);

  b.remove(b[2]);
  if (b.getSize() != 3)
    exit(EXIT_FAILURE);
  if (b.tail->data != 5)
    exit(EXIT_FAILURE);
  if (b.head->next != b.tail->prev)
    exit(EXIT_FAILURE);
    }*/
