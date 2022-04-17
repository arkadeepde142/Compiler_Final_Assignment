#include <clexer.hpp>
#include <iostream>
#include <string>

using namespace std;
CLexer::CLexer() : lexer::Lexer({
                       {R"(+|++|-|--|{|}|\(|\)|=|;|void|enum|.|,|for|return|break)"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol(s);
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"struct|union"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("struct_or_union");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"int|float"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("primitive");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {R"( *)"s,
                        [](string s, unsigned long i) {
                        }},
                       {"\n"s,
                        [&](string s, unsigned long i)
                        {
                            line += 1;
                            colStart = i + 1;
                        }},
                       {">|<"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("relop");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"(q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|k|l|z|x|c|v|b|n|m|_|Q|W|E|R|T|Y|U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M)(q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|k|l|z|x|c|v|b|n|m|_|Q|W|E|R|T|Y|U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M|1|2|3|4|5|6|7|8|9|0)*"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("id");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"(1|2|3|4|5|6|7|8|9|0)(1|2|3|4|5|6|7|8|9|0)*"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("int_num");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"(1|2|3|4|5|6|7|8|9|0)(1|2|3|4|5|6|7|8|9|0)*.(1|2|3|4|5|6|7|8|9|0)(1|2|3|4|5|6|7|8|9|0)*"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("fp_num");
                            symbol.lineNum = line;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},

                   })
{
}

unsigned long CLexer::getLine() const
{
    return line;
}

unsigned long CLexer::getColNum() const
{
    return colNum;
}

std::vector<Symbol> const& CLexer::getLexemes() const
{
    return lexemes;
}

void CLexer::generateLexemes(std::string s)
{
    unsigned long start = 0;
    while (start < s.size())
    {
        colNum = start - colStart + 1;
        start = lex(s, start);
    }

    if(start != s.size())
    {
        error = true;
    }
}

void CLexer::reset()
{
    error = false;
    line = 1;
    colNum = 1;
    colStart = 0;
}

bool CLexer::isError() const
{
    return error;
}