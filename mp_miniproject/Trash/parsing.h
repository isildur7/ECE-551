#ifndef __PARSING_H__
#define __PARSING_H__

#include <sstream>
#include <string>

#include "expressions.h"

typedef std::map<std::string, FuncStore *> funcmap_t;
void skipSpaces(std::string::iterator & it);
bool isValidBinOp(std::string & op);
bool isValidUnOp(std::string & op);
bool isValidFunction(std::string & op, funcmap_t & funcmap);
double strtod_wrapper(std::string input);
std::string getNextString(std::string::iterator & it);
std::string removeExtraSpaces(std::string input);
long strtol_wrapper(std::string input);

#endif
