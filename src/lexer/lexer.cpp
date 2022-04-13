#include <lexer.hpp>

namespace lexer
{

    Lexer::Lexer(vector<pair<DFA, function<void(string)>>> dfas) : dfas(dfas)
    {
    }

    unsigned long Lexer::lex(string const& s, unsigned long start)
    {
        pair<int, int> match = {-1, -1};

        for (int i = start; i < s.size(); ++i)
        {
            for (int j = 0; j < dfas.size(); ++j)
            {
                dfas[j].first.move(s[i]);
                if (dfas[j].first.isAccepting())
                {
                    auto &[dfaIndex, stringIndex] = match;
                    if(i > stringIndex)
                    {
                        stringIndex = i;
                        dfaIndex = j;
                    }
                }
            }
        }

        for (auto &dfa : dfas)
        {
            dfa.first.reset();
        }

        if(match != pair{-1, -1})
        {
            dfas[match.first].second(s.substr(start, match.second - start + 1));
            return match.second + 1;
        }
        return -1;
    }
}