#include <nfa.hpp>
#include <stack>
#define EPSILON_UNICODE "\u03F5"

namespace lexer
{
    NFA::NFA(int states) : statesCount(states)
    {
    }

    int NFA::getStatesCount() const
    {
        return statesCount;
    }

    NFA convertREToNFA(std::string str)
    {
        stack<NFA> operands;
        stack<char> operators;
        for (char c : str)
        {
            switch (c)
            {
            case '(':
            {
                operators.push(c);
                break;
            }
            case '*':
            {
                NFA starred = kleene(operands.top());
                operands.pop();
                operands.push(starred);
            }
            break;
            case '|':
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    NFA right = operands.top();
                    operands.pop();
                    NFA left = operands.top();
                    operands.pop();
                    operators.pop();
                    operands.push(orOp(left, right));
                }
                operators.push(c);
                break;
            }
            case '.':
            {
                while (!operators.empty() && operators.top() == '.')
                {
                    NFA right = operands.top();
                    operands.pop();
                    NFA left = operands.top();
                    operands.pop();
                    operators.pop();
                    operands.push(concat(left, right));
                }
                operators.push(c);
                break;
            }
            case ')':
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    char op = operators.top();
                    operators.pop();
                    NFA right = operands.top();
                    operands.pop();
                    NFA left = operands.top();
                    operands.pop();
                    if (op == '|')
                        operands.push(orOp(left, right));
                    else
                        operands.push(concat(left, right));
                }
                break;
            }
            default:
                operands.push(forSymbol(c));
            }
        }
        while (!operators.empty() && operators.top() != '(')
        {
            char op = operators.top();
            operators.pop();
            NFA right = operands.top();
            operands.pop();
            NFA left = operands.top();
            operands.pop();
            if (op == '|')
                operands.push(orOp(left, right));
            else
                operands.push(concat(left, right));
        }
        return operands.top();
    }

    NFA forSymbol(char c)
    {
        NFA nfa(2);
        nfa.setAcceptingState(1);
        nfa.addTransition(0, 1, c);
        return nfa;
    }

    unordered_set<int> NFA::getAcceptingStates() const
    {
        return acceptingStates;
    }

    void NFA::addTransition(int fromState, int toState, char symbol)
    {
        transitionTable[fromState][symbol].insert(toState);
    }

    TransitionTable NFA::getTransitionTable() const
    {
        return transitionTable;
    }

    void NFA::setAcceptingState(int s)
    {
        acceptingStates.insert(s);
    }

    NFA orOp(NFA nfa1, NFA nfa2)
    {
        int count1 = nfa1.getStatesCount();
        int count2 = nfa2.getStatesCount();
        NFA nfa(count1 + count2 + 2);
        for (auto const &[state, m] : nfa1.getTransitionTable())
        {
            for (auto const &[symbol, nextStates] : m)
            {
                for (int nextState : nextStates)
                {
                    nfa.addTransition(state + 1, nextState + 1, symbol);
                }
            }
        }

        for (auto const &[state, m] : nfa2.getTransitionTable())
        {
            for (auto const &[symbol, nextStates] : m)
            {
                for (int nextState : nextStates)
                {
                    nfa.addTransition(state + count1 + 1, count1 + nextState + 1, symbol);
                }
            }
        }

        nfa.addTransition(0, 1, EPSILON);
        nfa.addTransition(0, count1 + 1, EPSILON);
        nfa.addTransition(count1, nfa.getStatesCount() - 1, EPSILON);
        nfa.addTransition(nfa.getStatesCount() - 2, nfa.getStatesCount() - 1, EPSILON);
        nfa.setAcceptingState(nfa.getStatesCount() - 1);
        return nfa;
    }

    NFA concat(NFA left, NFA right)
    {
        NFA nfa(left.getStatesCount() + right.getStatesCount() - 1);
        int leftCount = left.getStatesCount();

        for (auto const &[state, m] : left.getTransitionTable())
        {
            for (auto const &[symbol, nextStates] : m)
            {
                for (int nextState : nextStates)
                {
                    nfa.addTransition(state, nextState, symbol);
                }
            }
        }

        for (auto const &[state, m] : right.getTransitionTable())
        {
            for (auto const &[symbol, nextStates] : m)
            {
                for (int nextState : nextStates)
                {
                    nfa.addTransition(state + leftCount - 1, leftCount + nextState - 1, symbol);
                }
            }
        }
        nfa.setAcceptingState(nfa.getStatesCount() - 1);
        return nfa;
    }

    NFA kleene(NFA nfa)
    {
        NFA result(nfa.getStatesCount() + 2);
        result.setAcceptingState(nfa.getStatesCount() + 1);
        result.addTransition(0, 1, EPSILON);
        for (auto const &[state, m] : nfa.getTransitionTable())
        {
            for (auto const &[symbol, nextStates] : m)
            {
                for (int nextState : nextStates)
                {
                    result.addTransition(state + 1, nextState + 1, symbol);
                }
            }
        }

        result.addTransition(nfa.getStatesCount(), nfa.getStatesCount() + 1, EPSILON);
        result.addTransition(0, result.getStatesCount() - 1, EPSILON);
        result.addTransition(result.getStatesCount() - 2, 1, EPSILON);

        return result;
    }

    ostream &operator<<(ostream &os, NFA const &nfa)
    {
        for (auto const &[state, m] : nfa.getTransitionTable())
        {
            for (auto const &[symbol, nextStates] : m)
            {
                for (int nextState : nextStates)
                {
                    if(symbol == EPSILON)
                    {
                        os << '('<< state << ", " << nextState << ", " << EPSILON_UNICODE  << ')' << endl;
                    }
                    else
                    os << '('<< state << ", " << nextState << ", " << symbol  << ')' << endl;
                }
            }
        }
        return os;
    }
}