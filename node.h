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
    // Overloading
    Node(double allPrice);
    Node(Node* left, Node* right);
    ~Node();

    void addGasPrice(double add);
};


#endif //SEGTREE_NODE_H
