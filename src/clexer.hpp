#ifndef CLEXER_H
#define CLEXER_H
#include <lexer/lexer.hpp>
#include <vector>
#include <string>
class CLexer: public lexer::Lexer{
    private:
        int line = 1;
    public:
    CLexer();
    int getLine() const;
    std::vector<std::string> getLexemes();
};
#endif