#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "parsing.h"

std::vector<std::string> getIDs(std::string & define);
void parse_define(std::string & in, funcmap_t & funcmap);
std::string functionDefinition(std::string define, funcmap_t & funcmap);
Expression * buildExpression(std::string::iterator & it, std::string & fName, funcmap_t & funcmap);
Expression * parseOp(std::string::iterator & it, std::string & fName, funcmap_t & funcmap);
Expression * parseBinOp(std::string::iterator & it,
                        std::string & op,
                        std::string & fName,
                        funcmap_t & funcmap);
Expression * makeBinOp(std::string & operation, Expression * lhs, Expression * rhs);
Expression * parseFuncOp(std::string::iterator & it,
                         std::string & op,
                         std::string & fName,
                         funcmap_t & funcmap);
Expression * parseUnOp(std::string::iterator & it,
                       std::string & op,
                       std::string & fName,
                       funcmap_t & funcmap);
Expression * makeUnOp(std::string & operation, Expression * side);

#endif
