#include <symboltable.hpp>
#include <iostream>
#include<iomanip>
SymbolTable::SymbolTable() : nodes{vector<Node>(1)}
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

Row *SymbolTable::resolveVariable(string variableName)
{
    size_t curr = currScope;
    while (curr != -1)
    {
        if (nodes[curr].variableMap.find(variableName) != nodes[curr].variableMap.end())
        {
            return &(nodes[curr].variableMap.at(variableName));
        }
        curr = nodes[curr].parent;
    }
    return nullptr;
}

bool SymbolTable::canBeResolvedVariable(string variableName) const
{
    size_t curr = currScope;
    while (curr != -1)
    {
        if (nodes[curr].variableMap.find(variableName) != nodes[curr].variableMap.end())
        {
            return true;
        }
        curr = nodes[curr].parent;
    }
    return false;
}

bool SymbolTable::declareVariable(string variableName, Row row)
{
    if (isDeclaredInScope(variableName))
    {
        return false;
    }
    nodes[currScope].variableMap[variableName] = row;
    return true;
}

void SymbolTable::printSymbolTable()
{
    cout<<"*************    SYMBOL TABLE    *****************"<<endl;
    std::cout << std::setw(40);
    int i = 1;
    for(auto node : nodes){
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
        cout<<"TABLE FOR SCOPE : "<<i<<"\n";
        cout<<"PARENT SCOPE : "<<node.parent<<"\n";
        cout<<"lexeme\t\ttype\t\tdetails"<<"\n";
        cout<<"----------------------------------------------------------------\n";
        for(auto r : node.variableMap){
            cout<<r.first<<"\t\t"<<r.second.type<<"\t\t";
            for(auto detail : r.second.details)
            cout<<detail<<" ";
            cout<<endl;
        }

        cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n";
        i++;
    }
    
}