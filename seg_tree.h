#include <string>
#include "vector"
#include "node.h"

#ifndef SEGTREE_SEG_TREE_H
#define SEGTREE_SEG_TREE_H


class seg_tree {
private:
    Node* root;
    std::vector <std::vector<double>> inputVec;

    double getAvg(int low, int high, int currentNodeLow, int currentNodeHigh, Node* currentNode);

    int binarySearch(bool mode, int low, int high, double target);

    void writeNode(int low, int high, Node* node, std::ofstream& outfile);

    void insert(int pos, int low, int high, double add, Node* currentNode);

    std::string getNodeString(Node* node, int low, int high);
public:
    seg_tree(std::vector <std::vector<double>> inputVec);

    Node* genTree(int low, int high);

    void insert(int pos, double value);

    void writeFile(std::string fname);

    double getAvg(double low, double high);
    double getAvg(double high);

    void printVector();
};


#endif //SEGTREE_SEG_TREE_H
