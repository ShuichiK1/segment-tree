#include <string>
#include "vector"
#include "node.h"

#ifndef SEGTREE_SEG_TREE_H
#define SEGTREE_SEG_TREE_H


class seg_tree {
private:
    std::vector<int> inputVec;

    int getValue(int low, int high, int currentNodeLow, int currentNodeHigh, Node* currentNode);

public:
    Node* root;
    seg_tree(std::vector<int> inputVec);

    Node* genTree(int low, int high);

    bool search(int target, Node* tempNode);

    void insert(int pos, int low, int high, int data, Node* currentNode);
    void insert(int pos, int value);

    void writeFile(std::string fname, Node* tree);
    void writeNode(int low, int high, Node* node, std::ofstream& outfile);

    int getValue(int low, int high);

};


#endif //SEGTREE_SEG_TREE_H
