#ifndef NFA_HPP
#define NFA_HPP
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#define EPSILON '#'

namespace lexer
{
    using namespace std;
    using NFATransitionTable = unordered_map<int, unordered_map<char, unordered_set<int>>>;
    class NFA
    {
    private:
        unordered_set<int> acceptingStates;
        NFATransitionTable transitionTable;
        const int statesCount;

    public:
        NFA(int states);
        void addTransition(int fromState, int toState, char symbol);
        void setAcceptingState(int s);
        unordered_set<int> getAcceptingStates() const;
        int getStatesCount() const;
        NFATransitionTable getTransitionTable() const;
    };

    ostream& operator<<(ostream& os, NFA const& nfa);
    NFA convertREToNFA(string RE);
    NFA kleene(NFA nfa);
    NFA orOp(NFA nfa1, NFA nfa2);
    NFA concat(NFA left, NFA right);
    NFA forSymbol(char c);
}

#endif