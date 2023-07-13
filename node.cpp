#include "node.h"


// Default constructor
Node::Node(){
    this->data = 0;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(Node* left, Node* right){
    this->data = 0;
    this->left = left;
    this->right = right;
}

Node::~Node(){

}

void Node::addData(int add){
    this->data += add;
}
