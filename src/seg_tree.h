//Group 3
//James McCaffrey
//Shuichi Kameda
//Evan Ung
//Michael Gilkeson
//Segment Trees
//7/24/23
#include <string>
#include "vector"
#include "node.h"

#ifndef SEGTREE_SEG_TREE_H
#define SEGTREE_SEG_TREE_H


class seg_tree {
private:
    Node* root;
    std::vector <std::vector<double>> inputVec;

    int binarySearch(bool mode, int low, int high, double target);

    double getAvg(int currentNodeLow, int currentNodeHigh, int searchLow, int searchHigh, Node* currentNode);
    std::pair<double, double> getLowHigh(int currentNodeLow, int currentNodeHigh, int searchLow, int searchHigh, Node* currentNode, std::pair<double, double> lowHigh);

    void insert(int pos, int low, int high, double add, Node* currentNode);

    void writeNode(int low, int high, Node* node, std::ofstream& outfile);
    std::string getNodeString(Node* node, int low, int high);

public:
    seg_tree(std::vector <std::vector<double>> inputVec);

    Node* genTree(int low, int high);

    void printVector();

    double getAvg(double low, double high);
    double getAvg(double high);

    std::pair<double, double> getLowHigh(double low, double high);
    std::pair<double, double> getLowHigh(double high);

    void insert(int pos, double value);

    void writeFile(std::string fname);
};


#endif //SEGTREE_SEG_TREE_H
