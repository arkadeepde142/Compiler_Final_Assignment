#include <dfa.hpp>
#include <stack>
#include <set>
#include <iostream>
#include <algorithm>
#define EPSILON '$'

namespace lexer
{

    struct NodeState
    {
        set<int> firstPos;
        set<int> lastPos;
        bool nullable = false;
    };

    NodeState concat(NodeState left, NodeState right, unordered_map<int, set<int>> &followPos);
    NodeState kleene(NodeState value, unordered_map<int, set<int>> &followPos);
    NodeState orOp(NodeState left, NodeState right);
    NodeState forSymbol(char c, int index);
    NodeState generateStateForRegex(string str, unordered_map<int, set<int>> &followPos, unordered_map<char, set<int>> &charMap);

    string convertRegexToOperatorFormat(string s)
    {
        string result;
        s = "(" + s + ")";
        for (int i = 0; i < s.size(); ++i)
        {
            switch (s[i])
            {
            case '\\':
                result.push_back(s[i]);
                result.push_back(s[++i]);
                result.push_back('.');
                break;
            case '*':
            case ')':
                if (!result.empty() && result.back() == '.')
                {
                    result.pop_back();
                }
                result.push_back(s[i]);
                result.push_back('.');
                break;
            case '(':
                result.push_back(s[i]);
                break;
            case '.':
                result.push_back('\\');
                result.push_back(s[i]);
                result.push_back('.');
                break;
            case '|':
                if (!result.empty() && result.back() == '.')
                {
                    result.pop_back();
                }
                result.push_back(s[i]);
                break;
            default:
                result.push_back(s[i]);
                result.push_back('.');
            }
        }
        if (!result.empty() && result.back() == '.')
            result.pop_back();
        return result;
    }

    DFATransitionTable DFA::getTransitionTable() const
    {
        return transitionTable;
    }

    unordered_set<int> DFA::getAcceptingStates() const
    {
        return acceptingStates;
    }

    DFA::DFA(string regex)
    {
        unordered_map<char, set<int>> charMap;
        unordered_map<int, set<int>> followPos;

        NodeState result = generateStateForRegex(regex, followPos, charMap);

        unordered_map<int, set<int>> states;
        unordered_map<int, bool> marked;

        int count = 0;
        int end = 0;

        for (auto const &[_, indices] : charMap)
            end = max(end, *max_element(indices.begin(), indices.end()));

        ++end;

        states[0] = result.firstPos;

        while (any_of(states.begin(), states.end(), [&](auto p)
                      { return !marked[p.first]; }))
        {
            auto const &state = *find_if(states.begin(), states.end(), [&](auto p)
                                         { return !marked[p.first]; });

            marked[state.first] = true;

            if (state.second.find(end) != state.second.end())
            {
                acceptingStates.insert(state.first);
            }

            for (auto const &[symbol, indices] : charMap)
            {
                set<int> newState;
                for (int i : indices)
                {
                    if (state.second.find(i) != state.second.end())
                    {
                        set_union(followPos[i].begin(),
                                  followPos[i].end(),
                                  newState.begin(),
                                  newState.end(), inserter(newState, newState.end()));
                    }
                }
                auto x = find_if(states.begin(), states.end(), [&](auto const &p)
                                 { return p.second == newState; });
                if (x == states.end())
                {
                    count++;
                    states[count] = newState;
                    transitionTable[state.first][symbol] = count;
                }
                else
                {
                    transitionTable[state.first][symbol] = x->first;
                }
            }
        }
    }

    NodeState forSymbol(char c, int index)
    {
        NodeState nodeState;

        if (c != EPSILON)
        {
            nodeState.firstPos.insert(index);
            nodeState.lastPos.insert(index);
        }
        else
        {
            nodeState.nullable = true;
        }

        return nodeState;
    }

    NodeState orOp(NodeState left, NodeState right)
    {
        NodeState result;

        set_union(
            left.firstPos.begin(),
            left.firstPos.end(),
            right.firstPos.begin(),
            right.firstPos.end(),
            inserter(result.firstPos, result.firstPos.end()));

        set_union(
            left.lastPos.begin(),
            left.lastPos.end(),
            right.lastPos.begin(),
            right.lastPos.end(),
            inserter(result.lastPos, result.lastPos.end()));

        result.nullable = left.nullable || right.nullable;

        return result;
    }

    NodeState concat(NodeState left, NodeState right, unordered_map<int, set<int>> &followPos)
    {
        NodeState result;
        result.nullable = left.nullable && right.nullable;

        if (left.nullable)
        {
            set_union(
                left.firstPos.begin(),
                left.firstPos.end(),
                right.firstPos.begin(),
                right.firstPos.end(),
                inserter(result.firstPos, result.firstPos.end()));
        }
        else
        {
            result.firstPos = left.firstPos;
        }

        if (right.nullable)
        {
            set_union(
                left.lastPos.begin(),
                left.lastPos.end(),
                right.lastPos.begin(),
                right.lastPos.end(),
                inserter(result.lastPos, result.lastPos.end()));
        }
        else
        {
            result.lastPos = right.lastPos;
        }

        for (int i : left.lastPos)
        {
            followPos[i].insert(right.firstPos.begin(), right.firstPos.end());
        }

        return result;
    }

    NodeState kleene(NodeState nodeState, unordered_map<int, set<int>> &followPos)
    {
        NodeState result;
        result = nodeState;
        result.nullable = true;

        for (int i : result.lastPos)
        {
            followPos[i].insert(result.firstPos.begin(), result.firstPos.end());
        }
        return result;
    }

    NodeState generateStateForRegex(
        string str, unordered_map<int, set<int>> &followPos,
        unordered_map<char, set<int>> &charMap)
    {
        str = convertRegexToOperatorFormat(str) + ".#";
        int count = 0;
        stack<NodeState> operands;
        stack<char> operators;
        for (int i = 0; i < str.size(); ++i)
        {
            switch (str[i])
            {
            case '\\':
            {
                charMap[str[i + 1]].insert(++count);
                followPos[count];
                operands.push(forSymbol(str[++i], count));
                break;
            }
            case '(':
            {
                operators.push(str[i]);
                break;
            }
            case '*':
            {
                NodeState starred = kleene(operands.top(), followPos);
                operands.pop();
                operands.push(starred);
            }
            break;
            case '|':
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    NodeState right = operands.top();
                    operands.pop();
                    NodeState left = operands.top();
                    operands.pop();
                    if (operators.top() == '|')
                        operands.push(orOp(left, right));
                    else
                        operands.push(concat(left, right, followPos));
                    operators.pop();
                }
                operators.push(str[i]);
                break;
            }
            case '.':
            {
                while (!operators.empty() && operators.top() == '.')
                {
                    NodeState right = operands.top();
                    operands.pop();
                    NodeState left = operands.top();
                    operands.pop();
                    operators.pop();
                    operands.push(concat(left, right, followPos));
                }
                operators.push(str[i]);
                break;
            }

            case ')':
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    char op = operators.top();
                    operators.pop();
                    NodeState right = operands.top();
                    operands.pop();
                    NodeState left = operands.top();
                    operands.pop();
                    if (op == '|')
                        operands.push(orOp(left, right));
                    else
                        operands.push(concat(left, right, followPos));
                }
                operators.pop();
                break;
            }
            default:
                charMap[str[i]].insert(++count);
                followPos[count];
                operands.push(forSymbol(str[i], count));
            }
        }

        while (!operators.empty() && operators.top() != '(')
        {
            char op = operators.top();
            operators.pop();
            NodeState right = operands.top();
            operands.pop();
            NodeState left = operands.top();
            operands.pop();
            if (op == '|')
                operands.push(orOp(left, right));
            else
                operands.push(concat(left, right, followPos));
        }
        charMap.erase('#');
        return operands.top();
    }

    ostream &operator<<(ostream &os, DFA const &dfa)
    {
        for (auto const &[state, m] : dfa.getTransitionTable())
        {
            for (auto const &[symbol, nextState] : m)
            {
                os << '(' << state << ", " << nextState << ", " << symbol << ')' << endl;
            }
        }
        return os;
    }

    void DFA::move(char c)
    {
        if (transitionTable.at(currState).find(c) == transitionTable.at(currState).end())
        {
            valid = false;
        }
        else
            currState = transitionTable.at(currState).at(c);
    }

    bool DFA::isAccepting()
    {
        if (!valid)
            return false;
        return acceptingStates.find(currState) != acceptingStates.end();
    }

    void DFA::reset()
    {
        currState = 0;
        valid = true;
    }

}