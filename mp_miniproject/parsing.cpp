#include "parsing.h"

void skipSpaces(std::string::iterator & it) {
  // Inspired from code in 83, takes in a string iterator
  // and increments it till a non space character is reached
  while (*it == ' ' || *it == '\t') {
    ++it;
  }
  return;
}

bool isValidUnOp(std::string & op) {
  // Check if it is a valid Binary Operator
  std::string validUnOp("sin cos ln sqrt");
  if (validUnOp.find(op) == std::string::npos) {
    return false;
  }
  else {
    return true;
  }
}

bool isValidBinOp(std::string & op) {
  // Check if it is a valid Unary Operator
  std::string validBinOp("+ - * / % pow");
  if (validBinOp.find(op) == std::string::npos) {
    return false;
  }
  else {
    return true;
  }
}

bool isValidFunction(std::string & op, funcmap_t & funcmap) {
  // Check if the function name exists
  if (funcmap.find(op) == funcmap.end()) {
    return false;
  }
  else {
    return true;
  }
}

std::string getNextString(std::string::iterator & it) {
  std::string buffer;
  while (*it != '(' && *it != ' ' && *it != ')' && *it != '\t' && *it != '\n' && *it != '\0') {
    buffer.push_back(*it);
    ++it;
  }
  return buffer;
}

double strtod_wrapper(std::string input) {
  char * endp;
  double num = strtod(input.c_str(), &endp);
  if (input.c_str() == endp) {
    std::cerr << "Error: Expected a number or variable but found " << input << std::endl;
    std::cerr << "Error: Could not parse Expression\n";
    exit(EXIT_FAILURE);
  }
  // advance iterator
  // it = it + (endp - input.c_str() + 1);
  // No need?
  return num;
}

std::string removeExtraSpaces(std::string input) {
  // remove whitespaces at the front and back and
  // also remove comments, everything after #
  size_t begin = input.find_first_not_of(" \t\n");
  size_t com = input.find('#');
  if (com != std::string::npos) {
    input = input.substr(begin, com - begin);
    begin = 0;
  }
  size_t end = input.find_last_not_of(" \t\n");
  return input.substr(begin, end - begin + 1);
}
