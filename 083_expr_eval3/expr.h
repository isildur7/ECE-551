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
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const {
    if (sign == '+')
      return lhs->evaluate() + rhs->evaluate();
    if (sign == '-')
      return lhs->evaluate() - rhs->evaluate();
    if (sign == '*')
      return lhs->evaluate() * rhs->evaluate();
    if (sign == '/')
      return lhs->evaluate() / rhs->evaluate();
    return 0;
  }
  virtual ~Operator() {
    delete lhs;
    delete rhs;
  }
};

class NumExpression : public Expression
{
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
  virtual long evaluate() const { return number; }
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
