#include <tnode.hpp>
void printNaryTree(tnode* x, vector<bool> flag, int depth, bool isLast)
{
    // Condition when node is None
    if (x == NULL)
        return;
     
    // Loop to print the depths of the
    // current node
    for (int i = 1; i < depth; ++i) {
         
        // Condition when the depth
        // is exploring
        if (flag[i] == true) {
            cout << "| "
                << " "
                << " "
                << " ";
        }
         
        // Otherwise print
        // the blank spaces
        else {
            cout << " "
                << " "
                << " "
                << " ";
        }
    }
     
    // Condition when the current
    // node is the root node
    if (depth == 0)
        cout << x->n << '\n';
     
    // Condition when the node is
    // the last node of
    // the exploring depth
    else if (isLast) {
        cout << "+--- " << x->n << '\n';
         
        // No more childrens turn it
        // to the non-exploring depth
        flag[depth] = false;
    }
    else {
        cout << "+--- " << x->n << '\n';
    }
 
    int it = 0;
    for (auto i = x->root.begin();
    i != x->root.end(); ++i, ++it)
 
        // Recursive call for the
        // children nodes
        printNaryTree(*i, flag, depth + 1,
            it == (x->root.size()) - 1);
    flag[depth] = true;
}