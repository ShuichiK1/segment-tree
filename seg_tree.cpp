#include "seg_tree.h"
#include "vector"
#include "iostream"
#include "fstream"
#include "cmath"
#include <iomanip>

seg_tree::seg_tree(std::vector <std::vector<double>> inputVec) {
    this->inputVec = inputVec;
    this->root = new Node();
    this->root = genTree(0, inputVec.size()-1);
}

int seg_tree::binarySearch(bool mode, int low, int high, int target)
{
    int m;
    while (low <= high) {
        m = low + (high - low) / 2;

        if (inputVec[m][1] == target)
            return m;

        if (inputVec[m][1] < target)
            low = m + 1;

        else
            high = m - 1;
    }

    //TODO
    //POTENTIALLY OPTIMIZE THIS
    if (mode){
        if (inputVec[m][1] >= target){return m;}
        else{return m+1;}
    }
    else{
        if (inputVec[m][1] <= target){return m;}
        else{return m-1;}
    }
}

Node* seg_tree::genTree(int low, int high){
    if (low == high){
        Node *returnNode;

        returnNode = new Node(inputVec[low][0] );
        return returnNode;
    }

    //TODO OPTIMIZE
    double lowPrice = inputVec[low][0];
    double highPrice = inputVec[low][0];
    for (int i = low; i < high+1; i++){
        if (inputVec[i][0] > highPrice){
            highPrice = inputVec[i][0];
        }
        if (inputVec[i][0] < lowPrice){
            lowPrice = inputVec[i][0];
        }
    }
    //TODO OPTIMIZE

    int mid = std::ceil((high + low) / 2.0);

    Node* returnNode = new Node( lowPrice, highPrice, genTree(low, mid-1), genTree(mid, high));
    returnNode->addGasPrice(returnNode->left->gasPrice + returnNode->right->gasPrice);
    return returnNode;
}

//TODO probably going to get rid of this
//since the getAvg function is like our search
bool seg_tree::search(int target, Node* tempNode){
    if (target == tempNode->gasPrice){return true;}

    if (tempNode->left != nullptr){return search(target, tempNode->left);}

    if (tempNode->right != nullptr){return search(target, tempNode->right);}

    return false;
}

void seg_tree::insert(int pos, int low, int high, double add, Node* currentNode){
    if (!currentNode){return;}
    currentNode->addGasPrice(add);

    int mid = std::ceil((low + high) / 2.0);

    if (low >= pos && mid-1 >= pos){
        return insert(pos, low, mid-1, add, currentNode->left);
    }
    else{
        return insert(pos, mid, high, add, currentNode->right);
    }
}

void seg_tree::insert(int pos, double value){
    insert(pos, 0, inputVec.size()-1, value - inputVec[pos][0], root);
}

double seg_tree::getAvg(double low, double high){
    int lowIndex = binarySearch(1, 0, inputVec.size()-1, low);
    int highIndex = binarySearch(0, 0, inputVec.size()-1, high);
    if (highIndex == -1){return -999;}
    return getAvg(0,inputVec.size()-1 ,lowIndex, highIndex, root) / (highIndex - lowIndex + 1);
}

double seg_tree::getAvg(double high){
    int highIndex = binarySearch(0, 0, inputVec.size()-1, high);
    if (highIndex == -1){return -999;}
    return getAvg(0,inputVec.size()-1 ,0, highIndex, root) / (highIndex+1);
}

//TODO OPTIMIZE THIS FUNCTION
double seg_tree::getAvg(int currentNodeLow, int currentNodeHigh, int searchLow, int searchHigh, Node* currentNode){
    if (currentNodeLow == searchLow && currentNodeHigh<= searchHigh){
        if (currentNodeHigh == searchHigh){
            return currentNode->gasPrice;
        }
        return currentNode->gasPrice + getAvg(0,inputVec.size()-1, currentNodeHigh + 1, searchHigh, root);
    }

    int mid = std::ceil((currentNodeHigh + currentNodeLow) / 2.0);

    if (currentNodeLow <= searchLow && mid-1 >= searchLow){
        return getAvg(currentNodeLow, mid-1, searchLow, searchHigh, currentNode->left);
    }
    else{
        return getAvg(mid, currentNodeHigh, searchLow, searchHigh, currentNode->right);
    }
}

void seg_tree::writeNode(int low, int high, Node* node, std::ofstream& outfile)
{
    std::setprecision(2);
    int mid = std::ceil((low + high) / 2.0);
    std::string nodeString = getNodeString(node, low, high);
    if (node->left != nullptr)
    {
        std::string left = getNodeString(node->left, low, mid-1);
        outfile << "\t"<< nodeString << " -> " << left << ";\n";
        writeNode(low, mid-1,node->left, outfile);
    }

    if (node->right != nullptr)
    {
        std::string right = getNodeString(node->right, mid, high);
        outfile << "\t" << nodeString <<  " -> " << right << ";\n";
        writeNode(mid, high, node->right, outfile);
    }
}

void seg_tree::writeFile(std::string ifname){
    std::string ofname = ifname.substr(0, ifname.rfind('.')) + "_output.dot";
    std::ofstream outfile;
    outfile.open(ofname);

    outfile <<"digraph BST {\n";

    std::string rootString = getNodeString(root, 0, inputVec.size()-1);
    //std::string rootString = ("\"" + std::to_string(0) + "to" + std::to_string(inputVec.size()-1) + "\\n" + std::to_string(root->gasPrice) + "\\n " + std::to_string(root->lowPrice) + "\\n"+ std::to_string(root->highPrice) + "\"");
    if (root == nullptr){
        outfile<< "\n";
    }
    else if (root->right == nullptr && root->left == nullptr){
        outfile<< "\t" << rootString << ";\n" ;
    }
    else{
        writeNode(0, inputVec.size()-1, root, outfile);
    }
    outfile<<"}\n";
}

std::string seg_tree::getNodeString(Node* node, int low, int high){
    std::ostringstream sumPrice;
    sumPrice << std::fixed << std::setprecision(2) << node->gasPrice;
    std::ostringstream lowPrice;
    lowPrice << std::fixed << std::setprecision(2) << node->lowPrice;
    std::ostringstream highPrice;
    highPrice << std::fixed << std::setprecision(2) << node->highPrice;

    std::string nodeString = "\"" + std::to_string(low) + "to" + std::to_string(high) + "\\nSum Price:" + sumPrice.str() + "\\nLow Price:" + lowPrice.str() + "\\nHigh Price:"+ highPrice.str() + "\"";

    return nodeString;
}
