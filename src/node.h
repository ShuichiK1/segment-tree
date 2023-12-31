//Group 3
//James McCaffrey
//Shuichi Kameda
//Evan Ung
//Michael Gilkeson
//Segment Trees
//7/24/23
#ifndef SEGTREE_NODE_H
#define SEGTREE_NODE_H


class Node {
private:
    friend class seg_tree;
    double gasPrice;
    double lowPrice;
    double highPrice;

    Node* left;
    Node* right;
public:
    Node();
    Node(double allPrice);
    Node(Node* left, Node* right);
    ~Node();

    void addGasPrice(double add);
};


#endif //SEGTREE_NODE_H
