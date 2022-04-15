#include <iostream>
#include <clexer.hpp>
#include <iomanip>
#include <parser/parser.hpp>
using namespace std;

int main()
{
    // CLexer lex;

    // string s = "int func(int x1, int x2); \n int func(int x1, int x2){return x1 + x2;} \n void main(){ int z = func(2, 3);}";

    // unsigned long start = 0;
    // while (start < s.size())
    // {
    //     start = lex.lex(s, start);
    //     if (start > s.size())
    //     {
    //         cout << "Error at line " << lex.getLine() << endl;
    //     }
    // }

    parser::Grammar<string> grammar{
        {"E", {
                  {{"T", "E'"}, [](vector<string *>) {}},
              }},
        {"E'", {{{"+", "T", "E'"}, [](vector<string *>) {}}, {{"#"}, [](vector<string *>) {}}}},
        {"T", {
                  {{"F", "T'"}, [](vector<string *>) {}},
              }},
        {"T'", {{{"*", "F", "T'"}, [](vector<string *>) {}}, {{"#"}, [](vector<string *>) {}}}},
        {"F", {
                  {{"(", "E", ")"}, [](vector<string *>) {}},
                  {{"id"}, [](vector<string *>) {}},
              }},
    };

    parser::Parser parser(grammar, "#"s, "E"s);

    // grammar["A"] = {
    //         {
    //             {"a"}, [](vector<string*>){}

    //         },
    //         {
    //             {"#"}, [](vector<string*>){}
    //         }
    //     };

    // grammar["B"] = {
    //         {
    //             {"A"}, [](vector<string *>){}
    //         }
    // };
    // auto firstSets = parser::generateFirstSet(grammar, "#"s);
    // auto followSets = parser::generateFollowSet(grammar, "#"s, firstSets, "E"s);

    // cout << "First Sets:\n";
    // for (auto const &[symbol, set] : firstSets)
    // {
    //     cout << symbol << " -> { ";
    //     for (auto a : set)
    //     {
    //         cout << a << ", ";
    //     }
    //     cout << "\b\b }" << endl;
    // }

    // cout << "Follow Sets:\n";
    // for (auto const &[symbol, set] : followSets)
    // {
    //     cout << symbol << " -> { ";
    //     for (auto a : set)
    //     {
    //         cout << (a.empty() ? "$" : a) << ", ";
    //     }
    //     cout << "\b\b }" << endl;
    // }

    // auto a = parser::firstSetOf({"F", "T'"}, firstSets,"#"s);
    // for(auto t: a)
    // {
    //     cout << t << " ";
    // }
    // cout << endl;
    auto table = parser::createParseTable(grammar, "#"s, "E"s);
    for(auto const& [nonTerminal, m]: table)
    {
        for(auto const& [terminal, production]: m)
        {
            cout << "(";
            cout << quoted(nonTerminal);
            cout << ", ";
            cout << quoted(terminal.empty() ? "$": terminal);
            cout << ")";
            cout << " ";
            cout << production.first << " -> ";
            for(auto symbol: production.second.first)
            {
                cout << symbol;
            }
            cout << endl;
        }
    }
}