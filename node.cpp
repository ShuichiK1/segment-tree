//Group 3
//James McCaffrey
//Shuichi Kameda
//Evan Ung
//Michael Gilkeson
//Segment Trees
//7/24/23
#include "node.h"

// Default constructor
Node::Node(){
    this->gasPrice = 0.0;
    this->lowPrice = 0.0;
    this->highPrice = 0.0;
    this->left = nullptr;
    this->right = nullptr;
}

//constructor for leaf nodes
Node::Node(double allPrice){
    this->gasPrice = allPrice;
    this->lowPrice = allPrice;
    this->highPrice = allPrice;
    this->left = nullptr;
    this->right = nullptr;
}

//constructor used in gentree
Node::Node( Node* left, Node* right){
    this->gasPrice = 0.00;
    this->lowPrice = 0.0;
    this->highPrice = 0.0;
    this->left = left;
    this->right = right;
}

//default destructor
Node::~Node(){

}

//function for updating gas price
void Node::addGasPrice(double add) {
    this->gasPrice += add;
}
