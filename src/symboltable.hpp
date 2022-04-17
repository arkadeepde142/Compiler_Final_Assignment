#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct Row {
    string type;
    unordered_set<string> details;
};

struct Node {
    int parent = -1;
    unordered_map<string, Row> variableMap;
};

struct SymbolTable
{
    size_t currScope = 0;
    vector<Node> nodes;
public:
    SymbolTable();
    void openScope();
    void endScope();
    bool isDeclaredInScope(string variableName) const;
    Row* resolveVariable(string variableName);
    bool canBeResolvedVariable(string variableName) const;
    void declareVariable(string variableName, Row row);
};
#endif