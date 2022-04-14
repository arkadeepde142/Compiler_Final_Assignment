#include <iostream>
#include <clexer.hpp>
#include <parser/parser.hpp>
using namespace std;

int main()
{
    CLexer lex;

    string s = "int func(int x1, int x2); \n int func(int x1, int x2){return x1 + x2;} \n void main(){ int z = func(2, 3);}";

    unsigned long start = 0;
    while (start < s.size())
    {
        start = lex.lex(s, start);
        if (start > s.size())
        {
            cout << "Error at line " << lex.getLine() << endl;
        }
    }
}