#ifndef __NUMERICS_H__
#define __NUMERICS_H__

#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Abstract class for storing expressions
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual double evaluate() const = 0;
  virtual void fillValues(std::map<std::string, double> * varMap) = 0;
};

// Binary operatorations are expressions, they have
// lhs and rhs operators can be evaluated
class BinOperator : public Expression
{
  Expression * rhs;
  Expression * lhs;
  char sign;

 public:
  BinOperator(Expression * lhs, Expression * rhs, char sg) : rhs(rhs), lhs(lhs), sign(sg) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " " << sign << " " << rhs->toString() << ")";
    return ss.str();
  }
  virtual double evaluate() const {
    if (sign == '+')
      return lhs->evaluate() + rhs->evaluate();
    else if (sign == '-')
      return lhs->evaluate() - rhs->evaluate();
    else if (sign == '*')
      return lhs->evaluate() * rhs->evaluate();
    else if (sign == '/')
      return lhs->evaluate() / rhs->evaluate();
    else if (sign == '%')
      return fmod(lhs->evaluate(), rhs->evaluate());
    else
      return 0;
  }

  virtual void fillValues(std::map<std::string, double> * varMap) {
    lhs->fillValues(varMap);
    rhs->fillValues(varMap);
    return;
  }

  virtual ~BinOperator() {
    delete lhs;
    delete rhs;
  }
};

// VarExpressions are variables and they don't have a value
// associated with them unless we put a number there
// They have a name.
class VarExpression : public Expression
{
  double value;
  std::string name;

 public:
  VarExpression(std::string n) : name(n) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << name;
    return ss.str();
  }

  std::string getName() const { return name; }

  virtual void fillValues(std::map<std::string, double> * varMap) {
    std::map<std::string, double>::iterator it;
    it = varMap->find(name);
    if (it == varMap->end()) {
      std::cerr << "unknown variable!\n";
      exit(EXIT_FAILURE);
    }
    value = (*varMap)[name];
    return;
  }

  virtual double evaluate() const { return value; }
  ~VarExpression() {}
};

// NumExpressions are plain old numbers which represent a
// a sort of base case for evaluation of expressions
class NumExpression : public Expression
{
  double number;

 public:
  NumExpression(long n) : number(n) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }

  virtual void fillValues(std::map<std::string, double> * varMap) { return; }

  virtual double evaluate() const { return number; }
  ~NumExpression() {}
};

class Function
{
  std::string name;
  Expression * expr;
  std::vector<std::string> vars;

 public:
  Function(std::string name) : name(name), expr(NULL) {}

  void set_expression(Expression * expression) { expr = expression; }

  void set_vars(std::vector<std::string> var) { vars = var; }

  void set_vals(std::vector<double> vals) {
    if (vals.size() != vars.size()) {
      std::cerr << "Incorrect number of arguments to function\n";
      exit(EXIT_FAILURE);
    }
    std::map<std::string, double> varMap;
    for (size_t i = 0; i < vars.size(); i++) {
      varMap.insert(std::pair<std::string, double>(vars[i], vals[i]));
    }
    expr->fillValues(&varMap);
  }

  double evaluate(std::vector<double> vals) {
    set_vals(vals);
    return expr->evaluate();
  }
};

class PlusExpression : public BinOperator
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : BinOperator(lhs, rhs, '+') {}
  ~PlusExpression() {}
};

class MinusExpression : public BinOperator
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : BinOperator(lhs, rhs, '-') {}
  ~MinusExpression() {}
};

class TimesExpression : public BinOperator
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : BinOperator(lhs, rhs, '*') {}
  ~TimesExpression() {}
};

class DivExpression : public BinOperator
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : BinOperator(lhs, rhs, '/') {}
  ~DivExpression() {}
};

class ModExpression : public BinOperator
{
 public:
  ModExpression(Expression * lhs, Expression * rhs) : BinOperator(lhs, rhs, '%') {}
  ~ModExpression() {}
};

#endif
