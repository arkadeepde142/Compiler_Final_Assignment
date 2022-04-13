#ifndef DFA_HPP
#define DFA_HPP
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace lexer
{
    using namespace std;
    using DFATransitionTable = unordered_map<int, unordered_map<char, int>>;

    class DFA
    {
    private:
        int currState = 0;
        bool valid = true;
        unordered_set<int> acceptingStates;
        DFATransitionTable transitionTable;
    public:
        DFA(string regex);
        DFATransitionTable getTransitionTable() const;
        unordered_set<int> getAcceptingStates() const;
        void move(char c);
        bool isAccepting();
        void reset();
    };

    ostream& operator<<(ostream& os, DFA const& dfa);
}
#endif