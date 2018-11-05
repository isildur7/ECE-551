#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <cmath>
#include <cstdlib>
#include <iostream>

template<typename R, typename A>
class Function
{
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  CountedIntFn fn(log2(high - low) + 1, f, mesg);
  int c = binarySearchForZero(&fn, low, high);
  if (c != expected_ans) {
    std::cout << "In " << mesg;
    std::cout << " c = " << c << " != "
              << "expected = " << expected_ans << std::endl;
    exit(EXIT_FAILURE);
  }
  return;
}

#endif
