#include "define.h"
#include "mcint.h"
#include "numint.h"
#include "parsing.h"
#include "test.h"

int main(void) {
  // successfully failed failure case: sffc
  std::string tester = "define (  f x y z) = (  +(sqrt x) (- y z))";
  //std::string tester = "define (  f x) = (sqrt x)";
  tester = tester.substr(6);
  funcmap_t fmap;
  parse_define(tester, fmap);
  tester = "define (g   e z) = (+ e (f z 1 4))";
  tester = tester.substr(6);
  parse_define(tester, fmap);
  tester = "define (h t  u v) = (* t(* u v))";
  //sffc  tester = "define (g   e z) = (+ 45(f @z e 4.242))";
  //sffc  tester = "define g(   e z) = (+ e (f z 1 4.242))";
  //sffc  tester = "define (g   e$ z) = (+ e (f z 1 4.242))";
  tester = tester.substr(6);
  parse_define(tester, fmap);
  tester = "h 0.01 0 1 0 1 4 5";
  parse_numint(tester, fmap);
  tester = "h 100000 0 1 0 1 4 5";
  parse_mcint(tester, fmap);
  tester = "   (f 16 9 (g 5 9))     12  #comments ho    ";
  //  tester = "(f 36) 6";
  //std::string::iterator it = tester.begin();
  parse_test(tester, fmap);
}
