#include "seg_tree.h"
#include "vector"
#include "iostream"
#include "fstream"
#include "cmath"

seg_tree::seg_tree(std::vector<int> inputVec) {
    this->inputVec = inputVec;
}

Node* seg_tree::genTree(int low, int high){
    if (low == high){
        Node *returnNode;
        returnNode = new Node(inputVec[low]);
        return returnNode;
    }

    int mid = std::ceil((high + low) / 2.0);

    Node* returnNode = new Node( genTree(low, mid-1), genTree(mid, high));
    returnNode->addData(returnNode->left->data + returnNode->right->data);
    return returnNode;
}

bool seg_tree::search(int target, Node* tempNode){
    if (target == tempNode->data){return true;}

    if (tempNode->left != nullptr){return search(target, tempNode->left);}

    if (tempNode->right != nullptr){return search(target, tempNode->right);}

    return false;
}

void seg_tree::insert(int pos, int low, int high, int data, Node* currentNode){
    if (!currentNode){return;}
    currentNode->addData(data);

    int mid = std::ceil((low + high) / 2.0);

    if (low >= pos && mid-1 >= pos){
        return insert(pos, low, mid-1, data, currentNode->left);
    }
    else{
        return insert(pos, mid, high, data, currentNode->right);
    }
}

void seg_tree::insert(int pos, int value){
    insert(pos, 0, inputVec.size()-1, value - inputVec[pos], root);
}

int seg_tree::getValue(int low, int high){
    return getValue(0,inputVec.size()-1 ,low, high, root);
}

int seg_tree::getValue(int currentNodeLow, int currentNodeHigh, int searchLow, int searchHigh, Node* currentNode){
    if (currentNodeLow == searchLow && currentNodeHigh<= searchHigh){
        if (currentNodeHigh == searchHigh){
            return currentNode->data;
        }
        return currentNode->data + getValue(0,inputVec.size()-1, currentNodeHigh + 1, searchHigh, root);
    }

    int mid = std::ceil((currentNodeHigh + currentNodeLow) / 2.0);

    if (currentNodeLow <= searchLow && mid-1 >= searchLow){
        return getValue(currentNodeLow, mid-1, searchLow, searchHigh, currentNode->left);
    }
    else{
        return getValue(mid, currentNodeHigh, searchLow, searchHigh, currentNode->right);
    }
}

void seg_tree::writeNode(int low, int high, Node* node, std::ofstream& outfile)
{
    int mid = std::ceil((low + high) / 2.0);
    std::string nodeString = "\"" + std::to_string(low) + "to" + std::to_string(high) + "\\n" + std::to_string(node->data) + "\"";
    if (node->left != nullptr)
    {
        std::string left = "\"" + std::to_string(low) + "to" + std::to_string(mid-1) + "\\n" + std::to_string(node->left->data) + "\"";
        outfile << "\t"<< nodeString << " -> " << left << ";\n";
        writeNode(low, mid-1,node->left, outfile);
    }

    if (node->right != nullptr)
    {
        std::string right = "\"" + std::to_string(mid) + "to" + std::to_string(high) + "\\n" + std::to_string(node->right->data) + "\"";
        outfile << "\t" << nodeString <<  " -> " << right << ";\n";
        writeNode(mid, high, node->right, outfile);
    }
}

void seg_tree::writeFile(std::string fname, Node* tree){
    std::ofstream outfile;
    outfile.open("test.dot");

    outfile <<"digraph BST {\n";

    std::string rootString = ("\"" + std::to_string(0) + "to" + std::to_string(inputVec.size()-1) + "\\n" + std::to_string(tree->data) +"\"");
    if (tree == nullptr){
        outfile<< "\n";
    }
    else if (tree->right == nullptr && tree->left == nullptr){
        outfile<< "\t" << rootString << ";\n" ;
    }
    else{
        writeNode(0, inputVec.size()-1, tree, outfile);
    }
    outfile<<"}\n";
}