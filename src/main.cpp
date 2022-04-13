#include <iostream>
#include <lexer/lexer.hpp>
using namespace std;


int main()
{
    lexer::Lexer lex({{R"(char|int)"s,
                       [](string s)
                       {
                           cout << "KEYWORD" << endl;
                       }},
                      {R"( *)"s,
                       [](string s) {
                       }}});

    string s = "int    char";

    unsigned long start = 0;
    while (start < (unsigned long)(-1) && start < s.size())
    {
        start = lex.lex(s, start);
    }
}