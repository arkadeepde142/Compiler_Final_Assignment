#ifndef CPARSER_HPP
#define CPARSER_HPP
#include <clexer.hpp>
#include <parser/parser.hpp>

class CParser : public parser::Parser<Symbol>
{
public:
    CParser();
};
#endif