#include "numint.h"

double read_one_limit(std::string::iterator & it) {
  skipSpaces(it);
  if (*it == '\0') {
    std::cerr << "Error: Premature end of line found, improper number of limits might have been "
                 "passed to numint\n";
    exit(EXIT_FAILURE);
  }
  if ((!isdigit(*it)) && *it != '-' && *it != '+' && *it != '.') {
    std::cerr << "Error: Expected number as limit for integral, found '" << *it << "'\n";
    exit(EXIT_FAILURE);
  }
  std::string buffer = getNextStringNum(it);
  return strtod_wrapper(buffer);
}

void numintIterator(FuncStore * function,
                    std::vector<double> high,
                    std::vector<double> low,
                    std::vector<double> & args,
                    double & sum,
                    double inc,
                    int layer) {
  // This function is a little hard to explain, they should probably
  // allow picture comments lol. Next paragraph skippable.

  // Anyway, since I want to do the Riemann Sum integration, the easiest
  // (by easy I mean it took me 3 hours to think it through to here) way
  // to do it would be to have nested for loops, one for each variable.
  // If we start each of variable's loop at (lower limit) + 0.5*inc every center
  // point would be inc distance away. For example in 1D case we are doing
  // sum of (f(x)+f(x+inc))/2 * inc. Instead I can continue the trapezoid
  // approximation and do f((x+inc)/2) * inc to get a very similar result.
  // This would reduce computations by a lot. Now, next point is then 1 inc
  // away, and I would increase my counter by that much and go till the higher
  // limit. This for each variable. Hence the need for nested loops.

  // So, this function is like a one layer of nested loop. layer parameter is
  // the layer number and it calls the layer below it by recursing and passing
  // parameter layer-1. When we reach layer = 1 (which is the bottom layer)
  // we evaluate the passing it the current arg vector. Arg vector is the
  // iterator in each loops, more specifically for each layer, arg[layer-1]
  // acts as iterator.

  if (layer == 1) {
    for (args[0] = low[0] + (inc / 2); args[0] < high[0]; args[0] += inc) {
      varmap_t varmap = function->get_varmap(args);
      sum += function->evaluate(varmap);
    }
  }
  else {
    for (args[layer - 1] = low[layer - 1] + (inc / 2); args[layer - 1] < high[layer - 1];
         args[layer - 1] += inc) {
      numintIterator(function, high, low, args, sum, inc, layer - 1);
    }
  }
}

double doNumInt(FuncStore * function,
                std::vector<double> high,
                std::vector<double> low,
                double inc) {
  // Number of variables decides the loops in iteration
  int nargs = high.size();
  // start at lower limits
  std::vector<double> args = low;
  // variable to hold the integration value
  double sum = 0;
  // Recursive integrator
  numintIterator(function, high, low, args, sum, inc, nargs);
  // Since each prism or hyperprism or whatever has a base
  // (or hyperbase) of each length equal to inc
  return sum * pow(inc, nargs);
}

void parse_numint(std::string & input, funcmap_t & funcmap) {
  // commnad will have only one string and then all numbers
  // First remove whitespaces and comments
  input = removeExtraSpaces(input);
  // then start reading in the command
  std::string::iterator it = input.begin();
  std::string fname = getNextString(it);
  // Check if it is a valid function
  if (!isValidFunction(fname, funcmap)) {
    std::cerr << "Error: Function '" << fname << "' does not exist\n";
    exit(EXIT_FAILURE);
  }
  // Now read the increment
  skipSpaces(it);
  if (*it == '\0') {
    std::cerr << "Error: end of line found mid sentence\n";
    exit(EXIT_FAILURE);
  }
  std::string buffer = getNextStringNum(it);
  double increment = strtod_wrapper(buffer);
  if (increment <= 0) {
    std::cerr << "Error: increment amount should be a strictly positive number";
    exit(EXIT_FAILURE);
  }
  // Now we read in the limits. There should be a limit
  // for each argument of the function. So two values.
  int nargs = funcmap[fname]->get_nargs();
  std::vector<double> highVec;
  std::vector<double> lowVec;
  for (int i = 0; i < nargs; i++) {
    double lower = read_one_limit(it);
    double upper = read_one_limit(it);
    if (lower > upper) {
      std::cerr << "Error: lower limit higher than upper for variable " << i << std::endl;
      exit(EXIT_FAILURE);
    }
    lowVec.push_back(lower);
    highVec.push_back(upper);
  }
  // Just an additional sanity check
  if (lowVec.size() != highVec.size()) {
    std::cerr << "Error: Higher limits don't match up with lower limits/n";
    exit(EXIT_FAILURE);
  }
  // Actual integration
  double result = doNumInt(funcmap[fname], highVec, lowVec, increment);
  std::cout << "Result of numint of " << fname << " = " << result << std::endl;
}
