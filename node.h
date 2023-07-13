#ifndef SEGTREE_NODE_H
#define SEGTREE_NODE_H


class Node {
private:


    friend class seg_tree;
public:
    int data;

    Node* left;
    Node* right;

    Node();
    // Overloading
    Node(int data);
    Node(Node* left, Node* right);
    ~Node();

    void addData(int add);
};


#endif //SEGTREE_NODE_H
