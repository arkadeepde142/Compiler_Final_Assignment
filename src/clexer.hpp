#ifndef CLEXER_H
#define CLEXER_H
#include <lexer/lexer.hpp>


struct Symbol{
    std::string tokenName;
    std::string lexval;
    std::string id;
    std::string type;
    std::string aspect;
    int lineNum;
    int colNum;
    Symbol(std::string);
};

class CLexer: public lexer::Lexer {
    private:
        std::vector<Symbol> lexemes;
        int line = 1;
        unsigned long colStart = 0;
        bool error = false;
    public:
    CLexer();
    int getLine() const;
    void reset();
    std::vector<Symbol> getLexemes() const;
    void generateLexemes(std::string s);
};

#endif