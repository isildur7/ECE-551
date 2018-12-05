#include "define.h"

std::vector<std::string> getIDs(std::string & define) {
  // get a list of all identifiers in order
  std::string::iterator it = define.begin();
  std::vector<std::string> identifier;
  skipSpaces(it);
  if (*it != '(') {
    std::cerr << "Error: improper function definition\n";
    exit(EXIT_FAILURE);
  }
  ++it;
  while (*it != ')') {
    skipSpaces(it);
    // get current position in the string
    // cut from this position to the first
    // occurence of space and put in the
    // vector
    std::string temp;
    while (*it != ' ' && *it != ')') {
      if (it == define.end()) {
        // If end of line encountered, the opening parentheses
        // was never closed
        std::cerr << "Error: Expected ')'\n";
        exit(EXIT_FAILURE);
      }
      if (!isalpha(*it)) {
        // I am not allowing non alphabetic identifiers
        std::cerr << "Error: Non Alphabetic character used as identifier\n";
        exit(EXIT_FAILURE);
      }
      temp.push_back(*it);
      ++it;
    }

    for (size_t i = 0; i < identifier.size(); i++) {
      if (temp == identifier[i]) {
        std::cerr << "Error: Identifier '" << temp << "' used more than once\n";
        exit(EXIT_FAILURE);
      }
    }
    identifier.push_back(temp);
  }
  if (identifier.empty()) {
    // Don't want to return empty vector
    std::cerr << " Error! could not get any IDs";
    exit(EXIT_FAILURE);
  }
  return identifier;
}

std::string functionDefinition(std::string define, funcmap_t & funcmap) {
  // takes in the lhs of define and creates a function to store in funcmap
  std::vector<std::string> ids = getIDs(define);
  // By design, first id will be a function name and next ones will be vars
  std::string name = ids.front();
  // remove it so that we get var vector and create a new function out of it
  ids.erase(ids.begin());
  // Check if the function exists, remove it if it does
  if (funcmap.find(name) != funcmap.end()) {
    delete funcmap[name];
    funcmap.erase(name);
  }
  FuncStore * function = new FuncStore(ids);
  // Insert into map
  funcmap.insert(std::pair<std::string, FuncStore *>(name, function));
  return name;
}

Expression * makeBinOp(std::string & operation, Expression * lhs, Expression * rhs) {
  if (operation.compare("+") == 0)
    return new PlusExpression(lhs, rhs);
  else if (operation.compare("-") == 0)
    return new MinusExpression(lhs, rhs);
  else if (operation.compare("*") == 0)
    return new TimesExpression(lhs, rhs);
  else if (operation.compare("/") == 0)
    return new DivExpression(lhs, rhs);
  else if (operation.compare("%") == 0)
    return new ModExpression(lhs, rhs);
  else if (operation.compare("pow") == 0)
    return new PowExpression(lhs, rhs);
  else {
    std::cerr << "Error: Unknown Operation\n";
    return NULL;
  }
}

Expression * makeUnOp(std::string & operation, Expression * side) {
  if (operation.compare("sin") == 0)
    return new SinExpression(side);
  else if (operation.compare("cos") == 0)
    return new CosExpression(side);
  else if (operation.compare("ln") == 0)
    return new LogExpression(side);
  else if (operation.compare("sqrt") == 0)
    return new SqrtExpression(side);
  else {
    std::cerr << "Error:Unknown Operation\n";
    return NULL;
  }
}

Expression * parseBinOp(std::string::iterator & it,
                        std::string & op,
                        std::string & fName,
                        funcmap_t & funcmap) {
  // parse a binary operation and return a fully made expression
  // skip spaces and you should get your first Expression
  skipSpaces(it);
  Expression * lhs = buildExpression(it, fName, funcmap);
  if (lhs == NULL) {
    return NULL;
  }
  Expression * rhs = buildExpression(it, fName, funcmap);
  if (rhs == NULL) {
    return NULL;
  }
  skipSpaces(it);
  if (*it == ')') {
    ++it;
    return makeBinOp(op, lhs, rhs);
  }
  std::cerr << "Expected ')' but found '" << *it << "'\n";
  delete lhs;
  delete rhs;
  return NULL;
}

Expression * parseUnOp(std::string::iterator & it,
                       std::string & op,
                       std::string & fName,
                       funcmap_t & funcmap) {
  // parse a binary operation and return a fully made expression
  // skip spaces and you should get your first Expression
  skipSpaces(it);
  Expression * side = buildExpression(it, fName, funcmap);
  if (side == NULL) {
    return NULL;
  }
  skipSpaces(it);
  if (*it == ')') {
    ++it;
    return makeUnOp(op, side);
  }
  std::cerr << "Expected ')' but found '" << *it << "'\n";
  delete side;
  return NULL;
}

Expression * parseFuncOp(std::string::iterator & it,
                         std::string & op,
                         std::string & fName,
                         funcmap_t & funcmap) {
  // Can have arbitrary number of arguments so need to store them
  // in vector
  std::vector<Expression *> expr_vec;
  skipSpaces(it);
  // Get number of possible arguments will need to read in those
  // many number of expressions
  size_t nargs = funcmap[op]->get_nargs();
  for (size_t i = 0; i < nargs; i++) {
    Expression * side = buildExpression(it, fName, funcmap);
    if (side == NULL) {
      return NULL;
    }
    expr_vec.push_back(side);
  }
  // Find the closing brace
  skipSpaces(it);
  if (*it == ')') {
    ++it;
    return new FuncOp(op, funcmap[op], expr_vec);
  }
  std::cerr << "Expected ')' but found '" << *it << "'\n";
  for (size_t i = 0; i < expr_vec.size(); i++) {
    delete expr_vec[i];
  }
  return NULL;
}

Expression * parseOp(std::string::iterator & it, std::string & fName, funcmap_t & funcmap) {
  // well, parses the operation and returns an expression
  skipSpaces(it);
  // Okay, there can be three possible scenarios
  // 1. BinOp
  // 2. UnOp
  // 3. Function Op
  // So, first find out which is it
  std::string buffer = getNextString(it);
  // Then break out into focus groups lol
  if (isValidBinOp(buffer)) {
    return parseBinOp(it, buffer, fName, funcmap);
  }
  if (isValidUnOp(buffer)) {
    return parseUnOp(it, buffer, fName, funcmap);
  }
  if (isValidFunction(buffer, funcmap)) {
    return parseFuncOp(it, buffer, fName, funcmap);
  }
  else {
    std::cerr << "Error: unknown identifier '" << buffer << "'\n";
    return NULL;
  }
}

Expression * buildExpression(std::string::iterator & it, std::string & fName, funcmap_t & funcmap) {
  // Inspired from assignment 83, takes an iterator, function map and the name of
  // the function for which we want to build the expression. Builds an expression
  // tree recursively and returns the expression
  if (funcmap.find(fName) == funcmap.end()) {
    std::cerr << "Error: Invalid Function Name to build\n";
    return NULL;
  }
  skipSpaces(it);
  if (*it == '\0') {
    std::cerr << "Error: End of line found mid-expression\n";
    return NULL;
  }
  else if (*it == '(') {
    // A new Operator Expression
    ++it;
    Expression * op = parseOp(it, fName, funcmap);
    if (op == NULL) {
      return NULL;
    }
    return op;
  }
  else if (isalpha(*it)) {
    // possible variable
    std::string buffer = getNextString(it);
    if (!funcmap[fName]->isValidVar(buffer)) {
      // check if it is a valid variable
      std::cerr << "Error: unknown symbol '" << buffer << "'\n";
      return NULL;
    }
    return new Variable(buffer);
  }
  else {
    // Possible number
    // So everthing in here should be either +, ., -, or number till
    // a tokenizer is reached
    std::string buffer;
    while (*it != '(' && *it != ' ' && *it != ')' && *it != '\t' && *it != '\n' && *it != '\0') {
      if (*it == '-' || *it == '+' || *it == '.' || isdigit(*it)) {
        buffer.push_back(*it);
        ++it;
      }
      else {
        std::cerr << "Expected a number but found: '" << *it << "'\n";
        return NULL;
      }
    }
    double num = strtod_wrapper(buffer);
    return new Number(num);
  }
}

void parse_define(std::string & in, funcmap_t & funcmap) {
  // Assumes that define command has been removed already
  // First remove the comments and additional spaces
  in = removeExtraSpaces(in);
  // Then, check if = is present
  size_t equal_pos = in.find('=');
  if (equal_pos == std::string::npos) {
    std::cerr << "Error: Improper defintion, no '=' found\n";
    exit(EXIT_FAILURE);
  }
  // Now, cut the string upto the point of eqaulity operator
  std::string definition = in.substr(0, equal_pos);
  definition = removeExtraSpaces(definition);
  // Once done that, get the actual definition of the function
  // and put it in the map and get back the name of the function
  std::string name = functionDefinition(definition, funcmap);
  // Next step is to build an expression for this
  // Get the other part of the string and build an expression
  // out of it.
  std::string::iterator it = in.begin() + equal_pos + 1;
  Expression * expr = buildExpression(it, name, funcmap);
  if (expr == NULL) {
    std::cerr << "Error: Could not parse Expression\n";
    delete funcmap[name];
    funcmap.erase(name);
    exit(EXIT_FAILURE);
  }
  // Set this expression in the function stored
  funcmap[name]->set_expression(expr);
  // and now print successfull definition
  std::cout << "Successfully defined (" << name;
  for (int i = 0; i < funcmap[name]->get_nargs(); i++) {
    std::cout << ' ' << funcmap[name]->get_var_vec()[i];
  }
  std::cout << ')' << std::endl;
}

// I guess that's that
