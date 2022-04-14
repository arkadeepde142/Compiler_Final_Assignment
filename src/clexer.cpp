#include <clexer.hpp>
#include <iostream>
#include <string>

using namespace std;
CLexer::CLexer() : lexer::Lexer({
                       {R"(+|++|-|--|{|}|\(|\)|=|;|void|enum|.|,|for|return|break)"s,
                        [](string s)
                        {
                            cout << s << " ";
                        }},
                       {"struct|union"s,
                        [](string s)
                        {
                            cout << "struct_or_union"
                                 << " ";
                        }},
                       {"int|float"s,
                        [](string s)
                        {
                            cout << "primitive"
                                 << " ";
                        }},
                       {R"( *)"s,
                        [](string s) {
                        }},
                       {"\n"s,
                        [&](string s)
                        {
                            line += 1;
                        }},
                       {">|<"s,
                        [](string s)
                        {
                            cout << "relop"
                                 << " ";
                        }},
                       {"(q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|k|l|z|x|c|v|b|n|m|_|Q|W|E|R|T|Y|U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M)(q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|k|l|z|x|c|v|b|n|m|_|Q|W|E|R|T|Y|U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M|1|2|3|4|5|6|7|8|9|0)*"s,
                        [](string s)
                        {
                            cout << "id"
                                 << " ";
                        }},
                       {"(1|2|3|4|5|6|7|8|9|0)(1|2|3|4|5|6|7|8|9|0)*"s,
                        [](string s)
                        {
                            cout << "int_num"
                                 << " ";
                        }},
                       {"(1|2|3|4|5|6|7|8|9|0)(1|2|3|4|5|6|7|8|9|0)*.(1|2|3|4|5|6|7|8|9|0)(1|2|3|4|5|6|7|8|9|0)*"s,
                        [](string s)
                        {
                            cout << "fp_num"
                                 << " ";
                        }},

                   })
{
}

int CLexer::getLine() const
{
    return line;
}