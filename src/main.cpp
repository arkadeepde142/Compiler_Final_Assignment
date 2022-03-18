#include <iostream>
#include <lexer/nfa.hpp>
using namespace std;
int main()
{
    lexer::NFA nfa = lexer::convertREToNFA("a|b.c");
    cout << nfa;
}