#include "define.h"
#include "parsing.h"

int main(void) {
  // successfully failed failure case: sffc
  std::string tester = "define (  f x y z) = (+ x (- y z))";
  tester = tester.substr(6);
  funcmap_t fmap;
  parse_define(tester, fmap);
  tester = "define (g   e z) = (+ e (f z 1 4.242))";
  tester = tester.substr(6);
  parse_define(tester, fmap);
  //sffc  tester = "define (g   e z) = (+ 45(f @z e 4.242))";
  //sffc  tester = "define g(   e z) = (+ e (f z 1 4.242))";
  //sffc  tester = "define (g   e$ z) = (+ e (f z 1 4.242))";
  tester = tester.substr(6);
  parse_define(tester, fmap);
}
