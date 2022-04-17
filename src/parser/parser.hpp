#ifndef PARSER_H
#define PARSER_H
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>
#include <iostream>

namespace parser
{
    using namespace std;

    template <typename Symbol>
    using Production = pair<vector<Symbol>, unordered_map<int, function<void(Symbol, vector<Symbol *>)>>>;

    template <typename Symbol>
    using ParseTable = unordered_map<Symbol, unordered_map<Symbol, Production<Symbol>>>;

    template <typename Symbol>
    using Grammar = unordered_map<Symbol, vector<Production<Symbol>>>;

    template <typename Symbol>
    unordered_map<Symbol, unordered_set<Symbol>> generateFirstSet(Grammar<Symbol> const &grammar, Symbol const &epsilon);

    template <typename Symbol>
    void generateFirstSetRecur(Grammar<Symbol> const &grammar, Symbol symbol, unordered_map<Symbol, unordered_set<Symbol>> &sets, Symbol const &epsilon);

    template <typename Symbol>
    unordered_map<Symbol, unordered_set<Symbol>> generateFollowSet(Grammar<Symbol> const &grammar, Symbol const &epsilon, unordered_map<Symbol, unordered_set<Symbol>> const &firstSets, Symbol start);

    template <typename Symbol>
    void generateFollowSetRecur(Grammar<Symbol> const &grammar,
                                Symbol symbol,
                                unordered_map<Symbol, unordered_set<Symbol>> &sets,
                                Symbol epsilon,
                                unordered_map<Symbol, unordered_set<Symbol>> const &firstSets,
                                Symbol start);

    template <typename Symbol>
    unordered_set<Symbol> firstSetOf(vector<Symbol> const &production, unordered_map<Symbol, unordered_set<Symbol>> const &firstSets, Symbol epsilon);

    template <typename Symbol>
    ParseTable<Symbol> createParseTable(Grammar<Symbol> const &grammar, Symbol epsilon, Symbol startSymbol);

    template <typename Symbol>
    class Parser
    {

    private:
        const ParseTable<Symbol> parseTable;
        const Symbol startSymbol;
        const Symbol epsilon;

    public:
        Parser(Grammar<Symbol> grammar, Symbol epsilon, Symbol start);
        vector<Production<Symbol>> getLMD(vector<Symbol> const &symbols) const;
        void parse(vector<Symbol> const &symbols) const;

    private:
        int parseUtil(vector<Symbol> const &, Symbol symbol, int index) const;
    };

    template <typename Symbol>
    Parser<Symbol>::Parser(Grammar<Symbol> grammar, Symbol epsilon, Symbol start) : parseTable(createParseTable(grammar, epsilon, start)), epsilon(epsilon), startSymbol(start)
    {
    }

    template <typename Symbol>
    vector<Production<Symbol>> Parser<Symbol>::getLMD(vector<Symbol> const &symbols) const
    {
    }

    template <typename Symbol>
    void Parser<Symbol>::parse(vector<Symbol> const &symbols) const
    {
        vector<Symbol> s(symbols);
        s.push_back(Symbol());
        int val = parseUtil(s, startSymbol, 0);
    }

    template <typename Symbol>
    int Parser<Symbol>::parseUtil(vector<Symbol> const &symbols, Symbol symbol, int index) const
    {
        if (symbols[index] == symbol)
        {
            return index + 1;
        }
        else if (parseTable.find(symbol) == parseTable.end())
        {
            if (symbol == epsilon)
            {
                return index;
            }
            return -1;
        }
        else if (parseTable.at(symbol).find(symbols[index]) == parseTable.at(symbol).end())
        {
            return -1;
        }
        else
        {
            int curr = index;
            cout << symbol;
            cout << " -> ";

            for (auto s : parseTable.at(symbol).at(symbols[index]).first)
                cout << s << " ";
            cout << endl;
            auto const &prod = parseTable.at(symbol).at(symbols[index]).first;
            auto const &actions = parseTable.at(symbol).at(symbols[index]).second;

            vector<Symbol> siblings(prod);
            for (int i = 0; i < prod.size(); ++i)
            {
                if (actions.find(i) != actions.end())
                {
                    vector<Symbol *> siblingPointers(i + 1);
                    for (int j = 0; j <= i; ++j)
                    {
                        siblingPointers[j] = &siblings[j];
                    }
                    actions.at(i)(symbol, siblingPointers);
                }

                curr = parseUtil(symbols, prod[i], curr);
                if (curr == -1)
                {
                    return -1;
                }
            }
            return curr;
        }
    }

    template <typename Symbol>
    unordered_map<Symbol, unordered_set<Symbol>> generateFirstSet(Grammar<Symbol> const &grammar, Symbol const &epsilon)
    {
        unordered_map<Symbol, unordered_set<Symbol>> sets;
        for (auto [s, _] : grammar)
        {
            generateFirstSetRecur(grammar, s, sets, epsilon);
        }
        // for(auto const& [s,a] : sets ){
        //     cout<< s << " => ";
        //     for (auto x : a){
        //         cout<<x<<", ";
        //     }
        //     cout<<endl;
        // }
        return sets;
    }

    template <typename Symbol>
    void generateFirstSetRecur(Grammar<Symbol> const &grammar, Symbol symbol, unordered_map<Symbol, unordered_set<Symbol>> &sets, Symbol const &epsilon)
    {
        if (sets.find(symbol) == sets.end())
        {
            for (auto const &[production, _] : grammar.at(symbol))
            {
                unordered_set<Symbol> tempSet;
                for (auto const &_symbol : production)
                {
                    if (grammar.find(_symbol) == grammar.end() || _symbol == epsilon)
                    {
                        if (_symbol != epsilon)
                            tempSet.erase(epsilon);
                        tempSet.insert(_symbol);
                        break;
                    }
                    else
                    {
                        generateFirstSetRecur(grammar, _symbol, sets, epsilon);
                        set_union(
                            begin(tempSet),
                            end(tempSet),
                            begin(sets[_symbol]),
                            end(sets[_symbol]),
                            inserter(tempSet, end(tempSet)));

                        if (sets[_symbol].find(epsilon) == sets[_symbol].end())
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
                    inserter(sets[symbol], end(sets[symbol])));
            }
        }
    }

    template <typename Symbol>
    void generateFollowSetRecur(Grammar<Symbol> const &grammar,
                                Symbol symbol,
                                unordered_map<Symbol, unordered_set<Symbol>> &sets,
                                Symbol epsilon,
                                unordered_map<Symbol, unordered_set<Symbol>> const &firstSets,
                                Symbol start)
    {
        if (sets.find(symbol) == sets.end() || symbol == start)
        {
            for (auto const &[_symbol, productions] : grammar)
            {
                for (auto const &[production, _] : productions)
                {
                    unordered_set<Symbol> tempSet;
                    auto match = find(begin(production), end(production), symbol);

                    if (match != production.end())
                    {
                        while (true)
                        {
                            ++match;
                            if (match == production.end())
                            {
                                if (symbol != _symbol)
                                {
                                    generateFollowSetRecur(grammar, _symbol, sets, epsilon, firstSets, start);
                                    set_union(
                                        begin(tempSet),
                                        end(tempSet),
                                        begin(sets.at(_symbol)),
                                        end(sets.at(_symbol)),
                                        inserter(tempSet, end(tempSet)));
                                }
                                break;
                            }
                            else
                            {
                                if (grammar.find(*match) == grammar.end())
                                {
                                    tempSet.insert(*match);
                                    break;
                                }
                                else
                                {
                                    set_union(
                                        begin(tempSet),
                                        end(tempSet),
                                        begin(firstSets.at(*match)),
                                        end(firstSets.at(*match)),
                                        inserter(tempSet, end(tempSet)));

                                    tempSet.erase(epsilon);

                                    if (firstSets.at(*match).find(epsilon) == firstSets.at(*match).end())
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    set_union(
                        begin(tempSet),
                        end(tempSet),
                        begin(sets[symbol]),
                        end(sets[symbol]),
                        inserter(sets[symbol], end(sets[symbol])));
                }
            }
        }
    }

    template <typename Symbol>
    unordered_map<Symbol, unordered_set<Symbol>> generateFollowSet(Grammar<Symbol> const &grammar,
                                                                   Symbol const &epsilon, unordered_map<Symbol, unordered_set<Symbol>> const &firstSets,
                                                                   Symbol start)
    {
        unordered_map<Symbol, unordered_set<Symbol>> sets;
        sets[start].insert(Symbol());
        for (auto [s, _] : grammar)
        {
            generateFollowSetRecur(grammar, s, sets, epsilon, firstSets, start);
        }
        return sets;
    }

    template <typename Symbol>
    unordered_set<Symbol> firstSetOf(vector<Symbol> const &production, unordered_map<Symbol, unordered_set<Symbol>> const &firstSets, Symbol epsilon)
    {
        unordered_set<Symbol> result;
        for (Symbol symbol : production)
        {
            if (firstSets.find(symbol) == firstSets.end())
            {
                result.erase(epsilon);
                result.insert(symbol);
                break;
            }

            set_union(
                begin(firstSets.at(symbol)),
                end(firstSets.at(symbol)),
                begin(result),
                end(result),
                inserter(result, end(result)));

            if (firstSets.at(symbol).find(epsilon) == firstSets.at(symbol).end())
            {
                result.erase(epsilon);
                break;
            }
        }
        return result;
    }

    template <typename Symbol>
    ParseTable<Symbol> createParseTable(Grammar<Symbol> const &grammar, Symbol epsilon, Symbol startSymbol)
    {
        ParseTable<Symbol> parseTable;

        auto firstSets = generateFirstSet(grammar, epsilon);
        auto followSets = generateFollowSet(grammar, epsilon, firstSets, startSymbol);

        for (auto const &[symbol, productions] : grammar)
        {
            for (auto const &[production, action] : productions)
            {
                auto firstSymbols = firstSetOf(production, firstSets, epsilon);
                if (firstSymbols.find(epsilon) != firstSymbols.end())
                {
                    for (auto const &followSymbol : followSets.at(symbol))
                    {
                        parseTable[symbol][followSymbol] = {production, action};
                    }
                    firstSymbols.erase(epsilon);
                }
                for (auto const &firstSymbol : firstSymbols)
                {
                    parseTable[symbol][firstSymbol] = {production, action};
                }
            }
        }
        return parseTable;
    }

} // namespace parser

#endif