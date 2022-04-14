#ifndef PARSER_H
#define PARSER_H
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>

namespace parser
{
    using namespace std;

    template <typename Symbol>
    using Grammar = unordered_map<Symbol, vector<pair<vector<Symbol>, function<void(vector<Symbol &>)>>>>;

    template <typename Symbol>
    using Production = pair<Symbol, vector<Symbol>>;

    template <typename Symbol>
    unordered_map<Symbol, unordered_set<Symbol>> generateFirstSet(Grammar<Symbol> const& grammar, Symbol const& epsilon);

    template <typename Symbol>
    void generateFirstSetRecur(Grammar<Symbol> const& grammar, Symbol symbol,unordered_map<Symbol, unordered_set<Symbol>>& sets, Symbol const& epsilon);

    template <typename Symbol>
    unordered_map<Symbol, unordered_set<Symbol>> generateFollowSet(Grammar<Symbol> const& grammar, Symbol const& epsilon);

    template <typename Symbol>
    void generateFollowSetRecur(Grammar<Symbol> const& grammar, Symbol symbol,unordered_map<Symbol, unordered_set<Symbol>>& sets, Symbol const& epsilon);

    template <typename Symbol>
    class Parser
    {

    private:
        const Grammar<Symbol> grammar;
        const Symbol epsilon;

    public:
        Parser(Grammar<Symbol> grammar, Symbol epsilon);
        vector<Production<Symbol>> getLMD(vector<Symbol> const &symbols) const;

    };

    template <typename Symbol>
    Parser<Symbol>::Parser(Grammar<Symbol> grammar, Symbol epsilon) : grammar(grammar), epsilon(epsilon)
    {
    }

    template <typename Symbol>
    vector<Production<Symbol>> Parser<Symbol>::getLMD(vector<Symbol> const &symbols) const
    {
    }

    template <typename Symbol>
    void generateFirstSetRecur(Grammar<Symbol> const& grammar, Symbol symbol, unordered_map<Symbol, unordered_set<Symbol>>& sets, Symbol const& epsilon)
    {
        for(auto const& production: grammar.at(symbol))
        {
            unordered_set<Symbol> tempSet;
            for(auto const& _symbol: production)
            {
                if(grammar.find(_symbol) == grammar.end() || _symbol == epsilon)
                {
                    tempSet.insert(_symbol);
                    break;
                }
                else
                {
                    generateFirstSetRecur(grammar, _symbol, sets);
                    set_union(
                        begin(tempSet),
                        end(tempSet),
                        begin(sets[_symbol]),
                        end(sets[_symbol]),
                        inserter(tempSet, end(tempSet))
                    );

                    if(sets[_symbol].find(epsilon) == sets[_symbol].end())
                    {
                        tempSet.erase(epsilon);
                        break;
                    }
                }
            }

            set_union(
                        begin(tempSet),
                        end(tempSet),
                        begin(sets[symbol]),
                        end(sets[symbol]),
                        inserter(sets[symbol], end(sets[symbol]))
                    );
        }
    }

    template <typename Symbol>
    void generateFollowSetRecur(Grammar<Symbol> const& grammar, Symbol symbol,unordered_map<Symbol, unordered_set<Symbol>>& sets)
    {
        
    }

} // namespace parser

#endif