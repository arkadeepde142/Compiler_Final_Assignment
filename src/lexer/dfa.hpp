#ifndef DFA_HPP
#define DFA_HPP
#include <vector>
#include <string>
#include <nfa.hpp>

namespace lexer
{
    using DFATransitionTable = unordered_map<int, unordered_map<char, int>>;
    class DFA
    {
    private:
        vector<int> m_acceptingStates;
        DFATransitionTable transitionTable;
        int states;

    public:
        DFA(vector<NFA> nfas);
    };
}
#endif