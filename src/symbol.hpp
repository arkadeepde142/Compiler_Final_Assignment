#ifndef SYMBOL_HPP
#define SYMBOL_HPP
#include <string>
#include <functional>

struct Symbol
{
    std::string tokenName;
    std::string lexval;
    std::string id;
    std::string type;
    std::string aspect;
    int lineNum;
    int colNum;
    Symbol();
    Symbol(std::string s);
    Symbol(char const* s);
};

bool operator==(Symbol const& symbol1, Symbol const& symbol2);
bool operator==(Symbol const& symbol1, std::string const& symbol2);
bool operator==(std::string const& symbol1, Symbol const& symbol2);
bool operator!=(Symbol const& symbol1, Symbol const& symbol2);
bool operator!=(Symbol const& symbol1, std::string const& symbol2);
bool operator!=(std::string const& symbol1, Symbol const& symbol2);
bool operator<(Symbol const& symbol1, Symbol const& symbol2);
std::ostream &operator<<(std::ostream &os, Symbol symbol);

template<>
struct std::hash<Symbol> {
    std::size_t operator()(Symbol const& symbol) const {
        return std::hash<std::string>{}(symbol.tokenName);
    }
};

template<>
struct std::less<Symbol> {
    bool operator()(const Symbol& symbol1, const Symbol& symbol2) const {
        return symbol1.tokenName < symbol2.tokenName;
    }
};
#endif