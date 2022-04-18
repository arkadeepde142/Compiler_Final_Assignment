#ifndef TNODE_H
#define TNODE_H
#include <iostream>
#include <vector>
#include <list>
using namespace std;
struct tnode {
    string n;
    list<tnode*> root;
    tnode(string data)
        : n(data)
    {
    }
    ~tnode()
    {
        for(auto x : root)
        {
            delete x;
        }
    }
};

void printNaryTree(tnode* x, vector<bool> flag, int depth = 0, bool isLast = false);


#endif