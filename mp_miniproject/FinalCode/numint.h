#ifndef __NUMINT_H__
#define __NUMINT_H__

#include "expressions.h"
#include "parsing.h"

double doNumInt(FuncStore *, std::vector<std::pair<double, double> > lims, double inc);
void parse_numint(std::string & input, funcmap_t & funcmap);
double read_one_limit(std::string::iterator & it);
void numintIterator(FuncStore * function,
                    std::vector<double> high,
                    std::vector<double> low,
                    std::vector<double> & args,
                    double & sum,
                    double inc,
                    int layer);
double doNumInt(FuncStore * function,
                std::vector<double> high,
                std::vector<double> low,
                double inc);

#endif
