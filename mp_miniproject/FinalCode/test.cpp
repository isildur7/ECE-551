#include "test.h"

double evaluate_operation(std::string::iterator & it, std::string & name, funcmap_t & funcmap) {
  // Absolytely red eyed, will add comments later
  //----------------------------------
  // ADD THE COMMENTS FOR THIS SECTION
  //----------------------------------
  if (!isValidFunction(name, funcmap)) {
    std::cerr << "Error: unknown identifier '" << name << "'\n";
    exit(EXIT_FAILURE);
  }
  std::vector<double> argVector;
  while (*it != ')') {
    skipSpaces(it);
    if (*it == '\0' || *it == '#') {
      std::cerr << "Error: End of line found mid-expression\n";
      exit(EXIT_FAILURE);
    }
    else if (*it == '+' || *it == '-' || *it == '.' || isdigit(*it)) {
      std::string buffer = getNextString(it);
      double num = strtod_wrapper(buffer);
      argVector.push_back(num);
    }
    else if (*it == '(') {
      double value = parse_operation(it, funcmap);
      argVector.push_back(value);
    }
    else {
      std::cerr << "Error: Unknown symbol found '" << *it << "'\n";
      exit(EXIT_FAILURE);
    }
  }
  if (argVector.size() != (unsigned)funcmap[name]->get_nargs()) {
    std::cerr << "Error: Argument size does not match with function defintion\n";
    exit(EXIT_FAILURE);
  }
  varmap_t varmap = funcmap[name]->get_varmap(argVector);
  return funcmap[name]->evaluate(varmap);
}

double parse_operation(std::string::iterator & it, funcmap_t & funcmap) {
  // Gets in an iterator, spits out an argument vector which can be given to
  // Expression->evaluate() hopefully
  //----------------------------------
  // ADD THE COMMENTS FOR THIS SECTION
  //----------------------------------
  skipSpaces(it);
  if (*it == '(') {
    ++it;
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

void parse_test(std::string input, funcmap_t funcmap) {
  size_t brk = get_break_point(input);
  std::string left = removeExtraSpaces(input.substr(0, brk));
  std::string right = removeExtraSpaces(input.substr(brk, std::string::npos));
  std::string::iterator lit = left.begin();
  std::string::iterator rit = right.begin();
  double lvalue = parse_operation(lit, funcmap);
  double rvalue = parse_operation(rit, funcmap);
  if (std::abs(lvalue - rvalue) <= 0.0000000000001) {
    std::cout << left << " = " << right << " [correct]\n";
  }
  else {
    std::cout << left << " = " << right << " [INCORRECT: expected " << lvalue << "]\n";
  }
}
