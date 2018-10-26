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

class Operator : public Expression
{
  Expression * rhs;
  Expression * lhs;
  char sign;

 public:
  Operator(Expression * lhs, Expression * rhs, char sg) : rhs(rhs), lhs(lhs), sign(sg) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " " << sign << " " << rhs->toString() << ")";
    return ss.str();
  }
  virtual ~Operator() {
    delete lhs;
    delete rhs;
  }
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
class PlusExpression : public Operator
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : Operator(lhs, rhs, '+') {}
  ~PlusExpression() {}
};

class MinusExpression : public Operator
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : Operator(lhs, rhs, '-') {}
  ~MinusExpression() {}
};
class TimesExpression : public Operator
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : Operator(lhs, rhs, '*') {}
  ~TimesExpression() {}
};
class DivExpression : public Operator
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : Operator(lhs, rhs, '/') {}
  ~DivExpression() {}
};

#endif
