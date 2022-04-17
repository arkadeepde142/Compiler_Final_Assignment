#ifndef CPARSER_HPP
#define CPARSER_HPP
#include <clexer.hpp>
#include <parser/parser.hpp>
#include <symboltable.hpp>

class CParser : public parser::Parser<Symbol>
{
private:
    SymbolTable symbolTable;
public:
    CParser();
};
#endif