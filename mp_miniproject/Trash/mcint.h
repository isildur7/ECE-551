#ifndef __MCINT_H__
#define __MCINT_H__

#include "expressions.h"
#include "parsing.h"

double getRandomValue(double low, double high);
double doMCInt(FuncStore * function,
               std::vector<std::pair<double, double> > & limits,
               long numtrials);
void parse_mcint(std::string & input, funcmap_t & funcmap);

#endif
