#ifndef LEXER_HPP
#define LEXER_HPP
#include <unordered_map>
#include <dfa.hpp>
namespace lexer
{
    using namespace std;
    using SymbolTable = unordered_map<int, int>;

    class Lexer
    {
    private:
        SymbolTable table;
    public:
        virtual void lex(string s) = 0;
    };
}
#endif