#ifndef DFA_HPP
#define DFA_HPP
#include <vector>
#include <string>
#include <nfa.hpp>

namespace lexer
{
    class DFA
    {
    private:
        vector<char> m_alphabets;
        vector<int> m_acceptingStates;
        vector<vector<int>> transitionTable;
        int states;

    public:
        DFA(NFA nfa);
    };
}
#endif