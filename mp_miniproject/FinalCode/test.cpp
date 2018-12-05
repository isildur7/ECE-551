#include "test.h"

double evaluate_operation(std::string::iterator & it, std::string & name, funcmap_t & funcmap) {
  if (isValidUnOp(name) || isValidBinOp(name) || isValidFunction(name, funcmap)) {
    // if it is valid operation proceed
    std::vector<double> argVector;
    // gather all arguments in this vector
    while (*it != ')') {
      // parse till you reach the close ')'
      skipSpaces(it);
      if (*it == ')') {  // if we reach the closed parentheses, do nothing. Exit next loop
        continue;
      }
      else if (*it == '\0' || *it == '#') {
        // clear I think, should not abruptly end the statement
        std::cerr << "Error: End of line found mid-expression\n";
        exit(EXIT_FAILURE);
      }
      else if (*it == '+' || *it == '-' || *it == '.' || isdigit(*it)) {
        // If it is either of these, it might be a number
        std::string buffer = getNextString(it);
        double num = strtod_wrapper(buffer);
        argVector.push_back(num);
      }
      else if (*it == '(') {
        // A new operation
        double value = parse_operation(it, funcmap);
        argVector.push_back(value);
      }
      else {
        // something invalid found
        std::cerr << "Error: Unknown symbol found '" << *it << "'\n";
        exit(EXIT_FAILURE);
      }
    }
    ++it;  // Extremely important increment. Here just out of the loop *it == ')'.
    // We want to point at the next element for the next loop/check for EOF
    if (isValidUnOp(name)) {
      // if the operation was unary operation like sin, make sure there is only one
      // argument and quick evaluate it on the that
      if (argVector.size() != 1) {
        std::cerr << "Error: incorrect number of arguments passed to " << name << " need 1 \n";
        exit(EXIT_FAILURE);
      }
      return UnOp(name).quick_evaluate(argVector[0]);
    }
    else if (isValidBinOp(name)) {
      // if the operation was binary operation like +, make sure there is only one
      // argument and quick evaluate it on the that
      if (argVector.size() != 2) {
        std::cerr << "Error: incorrect number of arguments passed to " << name << " need 2 \n";
        exit(EXIT_FAILURE);
      }
      return BinOp(name).quick_evaluate(argVector[0], argVector[1]);
    }
    else {
      // if the operation was a function operation, create the variable map and then
      // evaluate
      if (argVector.size() != (unsigned)funcmap[name]->get_nargs()) {
        std::cerr << "Error: Argument size does not match with function defintion\n";
        exit(EXIT_FAILURE);
      }
      varmap_t varmap = funcmap[name]->get_varmap(argVector);
      return funcmap[name]->evaluate(varmap);
    }
  }
  else {
    // unknonwn character
    std::cerr << "Error: unknown identifier '" << name << "'\n";
    exit(EXIT_FAILURE);
  }
}

double parse_operation(std::string::iterator & it, funcmap_t & funcmap) {
  // Gets in an iterator, finds the function, evaluates it and gives the result
  // absolutely red eyed will add commments later
  //----------------------------------
  // ADD THE COMMENTS FOR THIS SECTION
  //----------------------------------
  skipSpaces(it);
  if (*it == '(') {
    ++it;
    skipSpaces(it);
    std::string name = getNextString(it);
    return evaluate_operation(it, name, funcmap);
  }
  else if (*it == '+' || *it == '-' || *it == '.' || isdigit(*it)) {
    std::string buffer = getNextString(it);
    double num = strtod_wrapper(buffer);
    return num;
  }
  else {
    std::cerr << "Error: Expected '(' found '" << *it << "'\n";
    exit(EXIT_FAILURE);
  }
}

size_t get_break_point(std::string & in) {
  // I want to know where to break the thing into two parts
  // for testing. I am definitely expecting (....) format on
  // left side, so I will try and see where the first brace
  // is closed using stacks
  std::stack<int> BraceStack;
  std::string::iterator it = in.begin();
  skipSpaces(it);
  if (*it == '(') {
    BraceStack.push(1);
    while (!BraceStack.empty()) {
      ++it;
      if (it == in.end()) {
        std::cerr << "Error: missing ')' in test\n";
        exit(EXIT_FAILURE);
      }
      if (*it == '(') {
        BraceStack.push(1);
      }
      if (*it == ')') {
        BraceStack.pop();
      }
    }
    return it - in.begin() + 1;
  }
  else {
    std::cerr << "Error: Expected '(' found '" << *it << "'\n";
    exit(EXIT_FAILURE);
  }
}

std::string Formatter(std::string input) {
  // formats the string for output print
  // pretty much hardcoded
  std::string::iterator it = input.begin();
  std::string output;
  skipSpaces(it);
  while (it != input.end()) {
    if (*it == '(') {
      output.push_back('(');
      ++it;
      skipSpaces(it);
    }
    else if (*it == ' ' || *it == '\t') {
      skipSpaces(it);
      if (*it != ')') {
        output.push_back(' ');
      }
    }
    else {
      output.push_back(*it);
      ++it;
    }
  }
  return output;
}

void parse_test(std::string & input, funcmap_t & funcmap) {
  size_t brk = get_break_point(input);
  std::string left = removeExtraSpaces(input.substr(0, brk));
  std::string right = removeExtraSpaces(input.substr(brk, std::string::npos));
  std::string::iterator lit = left.begin();
  std::string::iterator rit = right.begin();
  double lvalue = parse_operation(lit, funcmap);
  CheckChar(lit);
  double rvalue = parse_operation(rit, funcmap);
  CheckChar(rit);
  left = Formatter(left);
  right = Formatter(right);
  if (std::abs(lvalue - rvalue) <= 0.0000000000001) {
    std::cout << left << " = " << right << " [correct]\n";
  }
  else {
    std::cout << left << " = " << right << " [INCORRECT: expected " << lvalue << "]\n";
  }
}
