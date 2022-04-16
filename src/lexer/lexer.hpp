#ifndef LEXER_HPP
#define LEXER_HPP
#include <unordered_map>
#include <functional>
#include <dfa.hpp>
namespace lexer
{
    using namespace std;

    class Lexer
    {
    private:
        vector<pair<DFA, function<void(string, unsigned long)>>> dfas;
    public:
        Lexer(vector<pair<DFA, function<void(string, unsigned long)>>> dfas);
        unsigned long lex(string const& s, unsigned long curr);
        virtual unsigned long getLine() const = 0;
        virtual unsigned long getColNum() const = 0;
    };
}
#endif