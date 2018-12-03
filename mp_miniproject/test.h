#ifndef __TEST_H__
#define __TEST_H__

#include <stack>

#include "expressions.h"
#include "parsing.h"

double parse_operation(std::string::iterator & it, funcmap_t & funcmap);
double evaluate_operation(std::string::iterator & it, std::string & name, funcmap_t & funcmap);
size_t get_break_point(std::string & in);
void parse_test(std::string input, funcmap_t funcmap);

#endif
