#ifndef __EXPR_H__
#define __EXPR_H__

#include <iostream>
#include <sstream>
#include <string>

class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
  int number;

 public:
  NumExpression(int n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
  ~NumExpression() {}
};
class PlusExpression : public Expression
{
  Expression * rhs;
  Expression * lhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : rhs(rhs), lhs(lhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
