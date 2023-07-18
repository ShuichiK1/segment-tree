#include "node.h"

// Default constructor
Node::Node(){
    this->gasPrice = 0.0;
    this->lowPrice = 0.0;
    this->highPrice = 0.0;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(double allPrice){
    this->gasPrice = allPrice;
    this->lowPrice = allPrice;
    this->highPrice = allPrice;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(double lowPrice, double highPrice, Node* left, Node* right){
    this->gasPrice = 0.00;
    this->lowPrice = lowPrice;
    this->highPrice = highPrice;
    this->left = left;
    this->right = right;
}

Node::~Node(){

}

void Node::addGasPrice(double add) {
    this->gasPrice += add;
}
