#include <symbol.hpp>
#include <iostream>

Symbol::Symbol() {}

Symbol::Symbol(std::string tokenName) : tokenName(tokenName)
{
}

Symbol::Symbol(char const *tokenName) : tokenName(tokenName)
{
}

std::ostream &operator<<(std::ostream &os, Symbol symbol)
{
    os << symbol.tokenName;
    return os;
}

bool operator==(Symbol const &symbol1, Symbol const &symbol2)
{
    return symbol1.tokenName == symbol2.tokenName;
}

bool operator==(Symbol const &symbol1, std::string const &symbol2)
{
    return symbol1.tokenName == symbol2;
}

bool operator==(std::string const &symbol1, Symbol const &symbol2)
{
    return symbol1 == symbol2.tokenName;
}

bool operator!=(Symbol const &symbol1, Symbol const &symbol2)
{
    return symbol1.tokenName != symbol2.tokenName;
}

bool operator!=(Symbol const &symbol1, std::string const &symbol2)
{
    return symbol1.tokenName != symbol2;
}

bool operator!=(std::string const &symbol1, Symbol const &symbol2)
{
    return symbol1 != symbol2.tokenName;
}

bool operator<(Symbol const& symbol1, Symbol const& symbol2)
{
    return symbol1.tokenName < symbol2.tokenName;
}