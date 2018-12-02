#include <ctype.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "numerics.h"

// Functions taken from assignment 83
Expression * parse(const char ** strp, std::vector<std::string> vars);

void skipSpace(const char ** strp) {
  while (isspace(**strp)) {
    *strp = *strp + 1;
  }
}

Expression * makeExpr(char op, Expression * lhs, Expression * rhs) {
  switch (op) {
    case '+':
      return new PlusExpression(lhs, rhs);
    case '-':
      return new MinusExpression(lhs, rhs);
    case '*':
      return new TimesExpression(lhs, rhs);
    case '/':
      return new DivExpression(lhs, rhs);
    case '%':
      return new ModExpression(lhs, rhs);
    default:
      std::cerr << "Impossible op char: " << op << "\n";
      abort();
  }
}

bool isValidOp(char c) {
  return strchr("+-*/%", c) != NULL;
}

Expression * parseOp(const char ** strp, std::vector<std::string> vars) {
  skipSpace(strp);
  char op = **strp;
  if (!isValidOp(op)) {
    std::cerr << "Invalid op: " << op << "\n";
    return NULL;
  }
  *strp = *strp + 1;
  Expression * lhs = parse(strp, vars);
  if (lhs == NULL) {
    return NULL;
  }
  Expression * rhs = parse(strp, vars);
  if (rhs == NULL) {
    delete lhs;
    return NULL;
  }
  skipSpace(strp);
  if (**strp == ')') {
    *strp = *strp + 1;
    return makeExpr(op, lhs, rhs);
  }
  std::cerr << "Expected ) but found " << *strp << "\n";
  delete lhs;
  delete rhs;
  return NULL;
}

Expression * parse(const char ** strp, std::vector<std::string> vars) {
  skipSpace(strp);
  if (**strp == '\0') {
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (**strp == '(') {
    // (op E E)
    *strp = *strp + 1;
    return parseOp(strp, vars);
  }
  else if (isalpha(**strp)) {
    //variable
    char * id = new char[strlen(*strp)];
    strcpy(id, *strp);
    id = strtok(id, " \n)");
    *strp = *strp + strlen(id);
    for (size_t i = 0; i < vars.size(); i++) {
      if (std::string(id) == vars[i])
        return new VarExpression(vars[i]);
    }
    std::cerr << "Unknown symbol '" << id << "' found!\n";
    delete[] id;
    return NULL;
  }
  else {
    //number
    char * endp;
    double num = strtod(*strp, &endp);
    if (endp == *strp) {
      std::cerr << "Expected a number, but found " << *strp << "\n";
      return NULL;
    }
    *strp = endp;
    return new NumExpression(num);
  }
}

char parseMode(const char ** strp) {
  // parses whether define is entered or test is entered
  // input: string from the input
  // output: char "d" for define, "t" for test
  if (**strp == 'd') {
    // if first letter is d, then first word must be define
    if (strstr(*strp, "define") != *strp) {
      std::cerr << "invalid command!" << std::endl;
      exit(EXIT_FAILURE);
    }
    return 'd';
  }
  else if (**strp == 't') {
    // if first letter is t, then first word must be test
    if (strstr(*strp, "test") != *strp) {
      std::cerr << "invalid command!" << std::endl;
      exit(EXIT_FAILURE);
    }
    return 't';
  }
  else {
    // it's not a valid command
    std::cerr << "invalid command!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  FILE * f = fopen("input1.txt", "r");
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, f /*stdin*/) != -1) {
    const char * temp = line;
    std::cout << "Read expression: " << line;
    std::vector<std::string> vars;
    vars.push_back("x");
    vars.push_back("y");
    vars.push_back("z");
    Expression * expr = parse(&temp, vars);
    if (expr != NULL) {
      std::cout << "Parsed expression to: " << expr->toString() << "\n";
      // std::cout << "Evaluated expression to: " << expr->evaluate() << "\n";

      delete expr;
    }
    else {
      std::cout << "Could not parse expression, please try again.\n";
    }
  }
  free(line);
  return EXIT_SUCCESS;
}
