#ifndef CLEXER_H
#define CLEXER_H
#include <lexer/lexer.hpp>
#include <symbol.hpp>


class CLexer : public lexer::Lexer
{
private:
    std::vector<Symbol> lexemes;
    unsigned long line = 1;
    unsigned long colStart = 0;
    unsigned long colNum = 0;
    bool error = false;

public:
    CLexer();
    unsigned long getLine() const;
    unsigned long getColNum() const;
    bool isError() const;
    void reset();
    std::vector<Symbol> const &getLexemes() const;
    void generateLexemes(std::string s);
};

#endif