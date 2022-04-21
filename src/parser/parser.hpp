#ifndef PARSER_H
#define PARSER_H
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <vector>
#include <tnode.hpp>
#include <iomanip>
#include <iostream>
#include <tabulate.hpp>

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
        tnode root;
        int nv = 1;

    public:
        Parser(Grammar<Symbol> grammar, Symbol epsilon, Symbol start);
        vector<Production<Symbol>> getLMD(vector<Symbol> const &symbols) const;
        bool parse(vector<Symbol> const &symbols);
        void printParseTable() const;
        void drawParseTree();

    private:
        int parseUtil(vector<Symbol> const &, Symbol *symbolPtr, int index, tnode* curr);
    };

    template <typename Symbol>
    Parser<Symbol>::Parser(Grammar<Symbol> grammar, Symbol epsilon, Symbol start) : parseTable(createParseTable(grammar, epsilon, start)), epsilon(epsilon), startSymbol(start),
    root{tnode(startSymbol.tokenName)}
    {
        
    }

    template <typename Symbol>
    vector<Production<Symbol>> Parser<Symbol>::getLMD(vector<Symbol> const &symbols) const
    {
    }

    template <typename Symbol>
    bool Parser<Symbol>::parse(vector<Symbol> const &symbols)
    {
        auto start = startSymbol;
        vector<Symbol> s(symbols);
        s.push_back(Symbol());
        int val = parseUtil(s, &start, 0, &root);
        return val == s.size() - 1;
    }

    template <typename Symbol>
    int Parser<Symbol>::parseUtil(vector<Symbol> const &symbols, Symbol *symbolPtr, int index, tnode* currPtr)
    {
        if (symbols[index] == *symbolPtr)
        {
            *symbolPtr = symbols[index];
            return index + 1;
        }
        else if (parseTable.find(*symbolPtr) == parseTable.end())
        {
            if (*symbolPtr == epsilon)
            {
                return index;
            }
            cerr << "Error at line: " << symbols[index].lineNum;
            cerr << " and column: " << symbols[index].colNum;
            cerr << endl;
            return -1;
        }
        else if (parseTable.at(*symbolPtr).find(symbols[index]) == parseTable.at(*symbolPtr).end())
        {
            cerr << "Error at line: " << symbols[index].lineNum;
            cerr << " and column: " << symbols[index].colNum;
            cerr << endl;
            return -1;
        }
        else
        {
            int curr = index;
            cout << *symbolPtr;
            cout << " -> ";

            for (auto s : parseTable.at(*symbolPtr).at(symbols[index]).first)
                cout << s << " ";
            cout << endl;
            auto const &prod = parseTable.at(*symbolPtr).at(symbols[index]).first;
            auto const &actions = parseTable.at(*symbolPtr).at(symbols[index]).second;

            vector<Symbol> siblings(prod);
            for (int i = 0; i < siblings.size(); ++i)
            {
                if (actions.find(i) != actions.end())
                {
                    vector<Symbol *> siblingPointers(i + 1);
                    for (int j = 0; j <= i; ++j)
                    {
                        siblingPointers[j] = &siblings[j];
                    }
                    actions.at(i)(*symbolPtr, siblingPointers);
                }
                tnode *nextPointer = new tnode(string(siblings[i]));
                currPtr->root.push_back(nextPointer);
                nv += 1;
                curr = parseUtil(symbols, &siblings[i], curr, nextPointer);
                if (curr == -1)
                {
                    return -1;
                }
            }
            if (actions.find(siblings.size()) != actions.end())
            {
                vector<Symbol *> siblingPointers(siblings.size());
                for (int j = 0; j < siblings.size(); ++j)
                {
                    siblingPointers[j] = &siblings[j];
                }
                actions.at(siblings.size())(*symbolPtr, siblingPointers);
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

        cout << "FIRST SET\n";
        tabulate::Table table;
        vector<vector<string>> tableValues = {{"Non-Terminal", "First Set"}};
        // cout<< "\n****************     FIRST SETS    ******************\n\n";
        for(auto const& [s,set] : sets ){
            // cout<<"first set of ( "<< s << " )   =>   { ";
            string setString;
            for (auto x : set){
                string temp = "\"" +string(x)+"\"";
                setString += ( temp + ", ");
            }
            setString.pop_back();
            setString.pop_back();
            setString = "{ " + setString + " }";
            vector<string> temp = {s, setString};
            tableValues.push_back(temp);
        }
        for (auto const &_row : tableValues)
        {
            vector<variant<std::string, const char *, std::string_view, tabulate::Table>> row;
            for (string x : _row)
            {
                row.push_back(x);
            }
            table.add_row(row);
        }
        cout << table << '\n' << endl;
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
        // cout<<"\n\n****************     FOLLOW SETS    ******************\n\n";
        // for(auto const& [s,a] : sets ){
        //     cout<<"follow set of ( "<< s << " )   =>   { ";
        //     for (auto x : a){
        //         cout<<x<<", ";
        //     }
        //     cout<<" } , "<<endl;
        // }
        // cout<<"\n\n";
        cout << "FOLLOW SET\n";
        tabulate::Table table;
        vector<vector<string>> tableValues = {{"Non-Terminal", "Follow Set"}};
        // cout<< "\n****************     FIRST SETS    ******************\n\n";
        for(auto const& [s,set] : sets ){
            // cout<<"first set of ( "<< s << " )   =>   { ";
            string setString;
            for (auto x : set){
                string temp = "\"" +(string(x).empty() ? "$"s : string(x))+"\"";
                setString += ( temp + ", ");
            }
            setString.pop_back();
            setString.pop_back();
            setString = "{ " + setString + " }";
            vector<string> temp = {s, setString};
            tableValues.push_back(temp);
        }
        for (auto const &_row : tableValues)
        {
            vector<variant<std::string, const char *, std::string_view, tabulate::Table>> row;
            for (string x : _row)
            {
                row.push_back(x);
            }
            table.add_row(row);
        }
        cout << table << "\n" << endl;
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

    template <typename Symbol>
    void Parser<Symbol>::printParseTable() const
    {
        tabulate::Table table;
        unordered_set<Symbol> terminals;
        vector<Symbol> nonTerminals;

        for (auto const &[_, val] : parseTable)
        {
            nonTerminals.push_back(_);
            for (auto const &[key, _] : val)
            {
                terminals.insert(key);
            }
        }

        vector<Symbol> terminalsOrdered;
        for (auto x : terminals)
        {
            if (x != Symbol())
                terminalsOrdered.push_back(x);
        }
        terminalsOrdered.push_back(Symbol());

        vector<vector<string>> tableValues(nonTerminals.size() + 1,
                                           vector<string>(terminals.size() + 1, "Error"));
        tableValues[0][0] = "";
        for (int i = 1; i < tableValues.size(); ++i)
        {
            tableValues[i][0] = nonTerminals[i - 1];
        }

        for (int i = 1; i < tableValues[0].size(); ++i)
        {
            tableValues[0][i] = terminalsOrdered[i - 1];
        }

        tableValues[0].back() = "$";

        for (int i = 1; i < tableValues.size(); ++i)
        {
            for (int j = 1; j < tableValues[0].size(); ++j)
            {
                if (parseTable.at(nonTerminals[i - 1]).find(terminalsOrdered[j - 1]) != parseTable.at(nonTerminals[i - 1]).end())
                {
                    tableValues[i][j] = nonTerminals[i - 1];
                    tableValues[i][j] += " ->";
                    for (auto p : parseTable.at(nonTerminals[i - 1]).at(terminalsOrdered[j - 1]).first)
                    {
                        tableValues[i][j] += " ";
                        tableValues[i][j] += p;
                    }
                }
            }
        }

        for (auto const &_row : tableValues)
        {
            vector<variant<std::string, const char *, std::string_view, tabulate::Table>> row;
            for (string x : _row)
            {
                row.push_back(x);
            }
            table.add_row(row);
        }

        cout << table << endl;
    }

    template <typename Symbol>
    void Parser<Symbol>::drawParseTree()
    {
        vector<bool> flag(nv, true);
        printNaryTree(&root, flag);
    }

} // namespace parser

#endif