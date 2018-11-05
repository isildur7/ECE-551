#include "function.h"

int main(void) {
  class ConstNegFunction : public Function<int, int>
  {
   public:
    virtual int invoke(int arg) { return -1; }
  };

  class ConstFunction : public Function<int, int>
  {
   public:
    virtual int invoke(int arg) { return 1; }
  };

  class ConstRiseFunction : public Function<int, int>
  {
   public:
    virtual int invoke(int arg) { return 4 * arg; }
  };

  ConstFunction a;
  ConstNegFunction b;
  ConstRiseFunction c;
  check(&a, 3, 6, 3, "constfunc");
  check(&b, 3, 3, 3, "negative");
  check(&b, 3, 6, 5, "negative");
  check(&c, -2, 5, 0, "constrise");
  check(&c, -5, -2, -3, "constrise");
  return EXIT_SUCCESS;
}
