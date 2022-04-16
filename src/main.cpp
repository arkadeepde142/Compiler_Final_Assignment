#include <iostream>
#include <clexer.hpp>
#include <iomanip>
#include <parser/parser.hpp>
#include <symbol.hpp>
using namespace std;

int main()
{
    // CLexer lex;

    string s = "int func(int x1, int x2); \n int func(int x1, int x2){return x1 + x2;} \n void main(){ int z = func(2, 3);}";

    // unsigned long start = 0;
    // while (start < s.size())
    // {
    //     start = lex.lex(s, start);
    //     if (start > s.size())
    //     {
    //         cout << "Error at line " << lex.getLine() << endl;
    //     }
    // }
    // Symbol a("a");
    // Symbol b("b");
    // cout << (a != b);
    CLexer lexer;
    lexer.generateLexemes(s);
    for (auto lexeme : lexer.getLexemes())
    {
        cout << lexeme << endl;
    }

    parser::Grammar<Symbol> grammar{
        {"E", {
                  {{"T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                                  { cout << "E -> TE'" << endl; }}}},
              }},
        {"E'", {{{"+", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                                     { cout << "E' -> +TE'" << endl; }}}},
                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                          { cout << "E' -> #" << endl; }}}}}},
        {"T", {
                  {{"F", "T'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                                  { cout << "T -> FT'" << endl; }}}},
              }},
        {"T'", {{{"*", "F", "T'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                                     { cout << "T' -> *FT'" << endl; }}}},
                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                          { cout << "T' -> #" << endl; }}}}}},
        {"F", {
                  {{"(", "E", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                                      { cout << "F -> (E)" << endl; }}}},
                  {{"id"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
                             { cout << "F -> id" << endl; }}}},
              }},
    };

    parser::Parser<Symbol> parser(grammar, "#"s, "E"s);

    parser.parse({"id", "+", "id", "*", "id"});
}