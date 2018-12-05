#ifndef __EXPRESSIONS_H__
#define __EXPRESSIONS_H__

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//---------------------------------------------
// I have used code inspired from assignment 83
// in some places
//---------------------------------------------

// To make things easier
typedef std::map<std::string, double> varmap_t;

class Expression
{
  // Class defines all kinds of Expressions
  // It will be extended by:
  // 1. Binary Operators like '+' '-' etc
  // 2. Unary Operators like 'sin' 'cos' etc
  // 3. Functions (user defined)
  // 4. Variables (are letters)
  // 5. Numbers (doubles)
 public:
  // Decide and add methods
  virtual double evaluate(varmap_t & varMap) = 0;
  virtual ~Expression() {}
};

class BinOp : public Expression
{
  // Class of binary operators, they
  // take exactly two expressions and
  // perform an operation

  // Add private fields
  Expression * lhs;
  Expression * rhs;
  std::string operation;

 public:
  // Add methods
  // Taken in part from assignment
  BinOp(Expression * lhs, Expression * rhs, std::string op) : lhs(lhs), rhs(rhs), operation(op) {}

  BinOp(std::string op) : lhs(NULL), rhs(NULL), operation(op) {}

  virtual double evaluate(varmap_t & varMap) {
    if (operation.compare("+") == 0)
      return lhs->evaluate(varMap) + rhs->evaluate(varMap);
    else if (operation.compare("-") == 0)
      return lhs->evaluate(varMap) - rhs->evaluate(varMap);
    else if (operation.compare("*") == 0)
      return lhs->evaluate(varMap) * rhs->evaluate(varMap);
    else if (operation.compare("/") == 0)
      return lhs->evaluate(varMap) / rhs->evaluate(varMap);

    else if (operation.compare("%") == 0)
      return fmod(lhs->evaluate(varMap), rhs->evaluate(varMap));
    else if (operation.compare("pow") == 0)
      return pow(lhs->evaluate(varMap), rhs->evaluate(varMap));
    else {
      std::cerr << "Error: Unknown Operation\n";
      return 0;
    }
  }

  double quick_evaluate(double lhs, double rhs) {
    // for quick evaluation on doubles
    if (operation.compare("+") == 0)
      return lhs + rhs;
    else if (operation.compare("-") == 0)
      return lhs - rhs;
    else if (operation.compare("*") == 0)
      return lhs * rhs;
    else if (operation.compare("/") == 0)
      return lhs / rhs;
    else if (operation.compare("%") == 0)
      return fmod(lhs, rhs);
    else if (operation.compare("pow") == 0)
      return pow(lhs, rhs);
    else {
      std::cerr << "Error: Unknown Operation\n";
      return 0;
    }
  }

  virtual ~BinOp() {
    delete lhs;
    delete rhs;
  }
};

class UnOp : public Expression
{
  // Class of unary operators, they
  // take exactly one expression and
  // perform an operation

  // Add private fields
  Expression * side;
  std::string operation;

 public:
  // Add methods
  // Taken in part from Assignment 83
  UnOp(Expression * hs, std::string op) : side(hs), operation(op) {}

  UnOp(std::string op) : side(NULL), operation(op) {}

  virtual double evaluate(varmap_t & varMap) {
    if (operation.compare("sin") == 0)
      return sin(side->evaluate(varMap));
    else if (operation.compare("cos") == 0)
      return cos(side->evaluate(varMap));
    else if (operation.compare("ln") == 0)
      return log(side->evaluate(varMap));
    else if (operation.compare("sqrt") == 0)
      return sqrt(side->evaluate(varMap));
    else {
      std::cerr << "Error:Unknown Operation\n";
      return 0;
    }
  }
  double quick_evaluate(double side) {
    // for quick evalution
    if (operation.compare("sin") == 0)
      return sin(side);
    else if (operation.compare("cos") == 0)
      return cos(side);
    else if (operation.compare("ln") == 0)
      return log(side);
    else if (operation.compare("sqrt") == 0)
      return sqrt(side);
    else {
      std::cerr << "Error:Unknown Operation\n";
      return 0;
    }
  }

  virtual ~UnOp() { delete side; }
};

class FuncStore : public Expression
{
  // This class stores the definition of
  // functions. What that means is it will
  // define the behaviour of the function
  // in terms of an Expression

  Expression * expr;
  std::vector<std::string> var_vec;

 public:
  FuncStore(Expression * expr, std::vector<std::string> var_vec) : expr(expr), var_vec(var_vec) {}

  FuncStore(Expression * expr) : expr(expr) {}

  FuncStore(std::vector<std::string> var_vec) : expr(NULL), var_vec(var_vec) {}

  void set_var_vec(std::vector<std::string> var) { var_vec = var; }

  void set_expression(Expression * expression) { expr = expression; }

  varmap_t get_varmap(std::vector<double> values) {
    // This function will create a map of variable names paired
    // to the corresponding values. Variables are taken from the
    // variable vector of this function and values vector is
    // passed in to this function

    // I hope I know where the fuck I am going with this
    if (values.size() != var_vec.size()) {
      std::cerr << "Incorrect number of arguments to function\n";
      exit(EXIT_FAILURE);
    }
    varmap_t varMap;
    for (size_t i = 0; i < var_vec.size(); i++) {
      // Said pairing up occurs here
      varMap.insert(std::pair<std::string, double>(var_vec[i], values[i]));
    }
    return varMap;
  }

  bool isValidVar(std::string & op) {
    // check if this string is a valid variable name for the function
    for (size_t i = 0; i < var_vec.size(); i++) {
      if (var_vec[i].compare(op) == 0) {
        return true;
      }
    }
    return false;
  }
  int get_nargs() {  // gives the number of arguments
    return var_vec.size();
  }
  double evaluate(varmap_t & varMap) {
    double val = expr->evaluate(varMap);
    return val;
  }

  std::vector<std::string> get_var_vec() const { return var_vec; }

  Expression * get_expression() { return expr; }

  ~FuncStore() { delete expr; }
};

class FuncOp : public Expression
{
  // Functions can have another behaviour
  // which is more akin to an operation. It
  // encapsulates the storage class and
  // captures the operator behaviour. It is
  // in many ways a generalised class of
  // BinOp and UnOp.

  // Add private fields
  std::string id;
  FuncStore * func;
  std::vector<Expression *> expr_vec;

 public:
  // Add methods
  FuncOp(std::string id, FuncStore * func) : id(id), func(func) {}

  FuncOp(std::string id, FuncStore * func, std::vector<Expression *> vec) :
      id(id),
      func(func),
      expr_vec(vec) {}

  void set_expr_vec(std::vector<Expression *> var) { expr_vec = var; }

  std::vector<Expression *> get_expr_vec() { return expr_vec; }

  virtual double evaluate(varmap_t & varMap) {
    // First evaluate all of the expression vector
    // put the values in a vector which is then
    // used to evaluate the stored function
    std::vector<double> eval_vec;
    for (size_t i = 0; i < expr_vec.size(); i++) {
      eval_vec.push_back(expr_vec[i]->evaluate(varMap));
    }
    varmap_t newMap = func->get_varmap(eval_vec);
    return func->evaluate(newMap);
  }

  int get_nargs() {  // gives the number of arguments
    return expr_vec.size();
  }

  ~FuncOp() {
    // Don't delete func,it is in the table and will be
    // deleted when the table is deleted
    for (size_t i = 0; i < expr_vec.size(); i++) {
      delete expr_vec[i];
    }
  }
};

class Variable : public Expression
{
  // Class of placeholders
  // they will be filled in at some point

  // Add private fields
  std::string id;
  double value;

 public:
  // Add Methods
  Variable(std::string name) : id(name) {}

  void set_value(varmap_t * VarMap) { value = (*VarMap)[id]; }

  virtual double evaluate(varmap_t & varMap) { return varMap[id]; }

  virtual ~Variable() {}
};

class Number : public Expression
{
  // Stores Numbers for better use in
  // the Expressions scheme
  double value;
  // Add if more are required
 public:
  // Add Methods
  Number(double val) : value(val) {}

  virtual double evaluate(varmap_t & varMap) { return value; }

  virtual ~Number() {}
};
class PlusExpression : public BinOp
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : BinOp(lhs, rhs, "+") {}
  ~PlusExpression() {}
};

class MinusExpression : public BinOp
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : BinOp(lhs, rhs, "-") {}
  ~MinusExpression() {}
};

class TimesExpression : public BinOp
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : BinOp(lhs, rhs, "*") {}
  ~TimesExpression() {}
};

class DivExpression : public BinOp
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : BinOp(lhs, rhs, "/") {}
  ~DivExpression() {}
};

class ModExpression : public BinOp
{
 public:
  ModExpression(Expression * lhs, Expression * rhs) : BinOp(lhs, rhs, "%") {}
  ~ModExpression() {}
};

class PowExpression : public BinOp
{
 public:
  PowExpression(Expression * lhs, Expression * rhs) : BinOp(lhs, rhs, "pow") {}
  ~PowExpression() {}
};

class SinExpression : public UnOp
{
 public:
  SinExpression(Expression * lhs) : UnOp(lhs, "sin") {}
  ~SinExpression() {}
};

class CosExpression : public UnOp
{
 public:
  CosExpression(Expression * lhs) : UnOp(lhs, "cos") {}
  ~CosExpression() {}
};

class SqrtExpression : public UnOp
{
 public:
  SqrtExpression(Expression * lhs) : UnOp(lhs, "sqrt") {}
  ~SqrtExpression() {}
};

class LogExpression : public UnOp
{
 public:
  LogExpression(Expression * lhs) : UnOp(lhs, "ln") {}
  ~LogExpression() {}
};

#endif
