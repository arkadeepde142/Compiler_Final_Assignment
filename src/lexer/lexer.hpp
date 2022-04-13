#ifndef LEXER_HPP
#define LEXER_HPP
#include <unordered_map>
#include <functional>
#include "dfa.hpp"
namespace lexer
{
    using namespace std;

    class Lexer
    {
    private:
        vector<pair<DFA, function<void(string)>>> dfas;
    public:
        Lexer(vector<pair<DFA, function<void(string)>>> dfas);
        unsigned long lex(string const& s, unsigned long curr);
    };
}
#endif