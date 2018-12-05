#include "mcint.h"

#include "numint.h"

double getRandomValue(double low, double high) {
  return low + rand() / (double)RAND_MAX * (high - low);
}

double doMCInt(FuncStore * function,
               std::vector<std::pair<double, double> > & limits,
               long numtrials) {
  double sum = 0;
  // for the number of trials
  for (int i = 0; i < numtrials; i++) {
    std::vector<double> argvector;
    // for each variable, generate a random value within the range
    for (size_t j = 0; j < limits.size(); j++) {
      double pick = getRandomValue(limits[j].first, limits[j].second);
      argvector.push_back(pick);
    }
    // evaluate at that point amaknd add to sum
    varmap_t varmap = function->get_varmap(argvector);
    sum += function->evaluate(varmap);
  }
  // average
  sum = sum / (double)numtrials;
  // multiply by the limit space
  for (size_t j = 0; j < limits.size(); j++) {
    sum *= (limits[j].second - limits[j].first);
  }
  return sum;
}

void parse_mcint(std::string & input, funcmap_t & funcmap) {
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
  std::string buffer = getNextString(it);
  long trials = strtol_wrapper(buffer);
  if (trials < 1) {
    std::cerr << "Error: NUmber of trials is less than 1, cannot proceed\n";
    exit(EXIT_FAILURE);
  }
  // Now we read in the limits. There should be a limit
  // for each argument of the function. So two values.
  int nargs = funcmap[fname]->get_nargs();
  std::vector<std::pair<double, double> > limits;
  for (int i = 0; i < nargs; i++) {
    double lower = read_one_limit(it);
    double upper = read_one_limit(it);
    if (lower > upper) {
      std::cerr << "Error: lower limit higher than upper for variable " << i << std::endl;
      exit(EXIT_FAILURE);
    }
    limits.push_back(std::pair<double, double>(lower, upper));
  }

  // Actual integration
  double result = doMCInt(funcmap[fname], limits, trials);
  std::cout << "Result of mcint = " << result << std::endl;
}
