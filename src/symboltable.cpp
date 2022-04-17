#include <symboltable.hpp>

SymbolTable::SymbolTable(): nodes{vector<Node>(1)}
{
}

void SymbolTable::openScope()
{
    Node node;
    node.parent = currScope;
    nodes.push_back(node);
    currScope = nodes.size() - 1;
}

void SymbolTable::endScope()
{
    currScope = nodes[currScope].parent;
}

bool SymbolTable::isDeclaredInScope(string variableName) const
{
    return nodes[currScope].variableMap.find(variableName) != nodes[currScope].variableMap.end();
}

Row* SymbolTable::resolveVariable(string variableName)
{
    size_t curr = currScope;
    while(curr != -1)
    {
        if(nodes[curr].variableMap.find(variableName) != nodes[curr].variableMap.end())
        {
            return &(nodes[curr].variableMap.at(variableName)); 
        }
    }
    return nullptr;
}

bool SymbolTable::canBeResolvedVariable(string variableName) const
{
    size_t curr = currScope;
    while(curr != -1)
    {
        if(nodes[curr].variableMap.find(variableName) != nodes[curr].variableMap.end())
        {
            return true;
        }
    }
    return false;
}

void SymbolTable::declareVariable(string variableName, Row row)
{
    nodes[currScope].variableMap[variableName] = row;
}