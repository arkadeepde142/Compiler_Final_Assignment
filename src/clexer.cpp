#include <clexer.hpp>
#include <iostream>
#include <string>

using namespace std;
string digits = "(1|2|3|4|5|6|7|8|9|0)";
string lowercaseAlpha = "(q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|k|l|z|x|c|v|b|n|m)";
string uppercaseAlpha = "(Q|W|E|R|T|Y|U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M)";
string specialChars = R"((_|\\n|\\t|\\v|\\f|\\b|\\r|\\a|\\e))"s;
CLexer::CLexer() : lexer::Lexer({
                       {R"(+|++|-|--|{|}|\(|\)|=|;|void|.|,|while|return|break)"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol(s);
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"char"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("char");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                        {"string"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("string");
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
                       {">|<|<=|>="s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("relop");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {"(" + lowercaseAlpha + "|" + uppercaseAlpha + "|_)" + "(" +
                    lowercaseAlpha + "|" + uppercaseAlpha + "|_|" + digits + ")*",
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("id");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                       {digits + "*"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("int_num");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }},
                        {"'(" + lowercaseAlpha + "|" + uppercaseAlpha + "|" + digits + "|" + specialChars + ")'"s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("char_literal");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }
                        },
                        {"\"(" + lowercaseAlpha + "|" + uppercaseAlpha + "|" + digits + "|" + specialChars + ")*\""s,
                        [&](string s, unsigned long i)
                        {
                            Symbol symbol("string_literal");
                            symbol.lineNum = line;
                            symbol.lexval = s;
                            symbol.colNum = i - colStart + 1;
                            lexemes.push_back(symbol);
                        }
                        },
                   })
{
}

unsigned long CLexer::getLine() const
{
    return line;
}

// {|}|\\(|\\))|\\\\|.|;|:|\"|\'|>|<|\\|)

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