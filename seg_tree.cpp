//Group 3
//James McCaffrey
//Shuichi Kameda
//Evan Ung
//Michael Gilkeson
//Segment Trees
//7/24/23
#include "seg_tree.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>

//constructor initializes data members
//and generates tree with the input vector
seg_tree::seg_tree(std::vector <std::vector<double>> inputVec) {
    this->inputVec = inputVec;
    this->root = new Node();
    this->root = genTree(0, inputVec.size()-1);
}

//function generates the segment tree
//with the input vector being the intervals
//segment tree holds sum of gas prices and
//low/min gas price
Node* seg_tree::genTree(int low, int high){
    //if this is an external leaf node
    //then set node low/high/sum to price
    //and return
    if (low == high){
        Node *returnNode;

        returnNode = new Node(inputVec[low][0] );
        return returnNode;
    }

    //calculates the mid point between
    //high and low
    int mid = std::ceil((high + low) / 2.0);

    //initialize a new node and recursively
    //generate its left/right children
    Node* returnNode = new Node(genTree(low, mid-1), genTree(mid, high));
    //sets sum gas price to the sum of its children's sum gas price
    returnNode->addGasPrice(returnNode->left->gasPrice + returnNode->right->gasPrice);

    //branchless way of setting the return node's low price
    //to the lowest of its children's low price;
    returnNode->lowPrice +=
            returnNode->left->lowPrice *
            (returnNode->left->lowPrice < returnNode->right->lowPrice);
    returnNode->lowPrice +=
            returnNode->right->lowPrice *
            (returnNode->left->lowPrice >= returnNode->right->lowPrice);

    //branchless way of setting the return node's high price
    //to the lowest of its children's high price;
    returnNode->highPrice +=
            returnNode->left->highPrice *
            (returnNode->left->highPrice > returnNode->right->highPrice);
    returnNode->highPrice +=
            returnNode->right->highPrice *
            (returnNode->left->highPrice <= returnNode->right->highPrice);

    return returnNode;
}

//loops through the input vector and
//prints out its contents
void seg_tree::printVector() {
    int pageNum = 1;
    int pageStart = 0;
    int pageEnd = 10;

    std::cout << "Insert '>' to view next page, otherwise insert '.' to stop.\n\n";
    std::cout << "----- [Page " << pageNum << "] -----\n";

    for (pageStart; pageStart < pageEnd; pageStart++) {
        std::cout
                << "[" << pageStart << "] - $" << std::fixed << std::setprecision(2) <<inputVec[pageStart][0]
                << "\t" << std::setprecision(4) << inputVec[pageStart][1] << " mi.\n";
        if ((inputVec.size() > pageEnd) && (pageStart >= (pageEnd - 1))) {
            bool loop = true;

            while (loop) {
                char input;
                std::cin >> input;

                switch (input) {
                    case '>':
                        pageNum += 1;
                        pageStart = pageEnd - 1;
                        pageEnd += 10;

                        if (inputVec.size() <= pageEnd) {
                            pageEnd = inputVec.size();
                        }

                        loop = false;
                        std::cout << "----- [Page " << pageNum << "]-----\n";

                    case '.':
                        loop = false;
                        break;

                    default:
                        loop = true;
                }
            }
        }
    }
    std::cout <<"\n";
}

//binary search for getting index number
//based on the target distance. "rounds"
//up or down depending on mode
int seg_tree::binarySearch(bool mode, int low, int high, double target)
{
    int m;
    while (low <= high) {
        m = std::ceil((high + low) / 2.0);

        if (inputVec[m][1] == target)
            return m;

        if (inputVec[m][1] < target)
            low = m + 1;

        else
            high = m -1;
    }

    if (mode){
        if (inputVec[m+1][1] >= target && inputVec[m][1] < target){return m + 1;}
        else{return m;}
    }
    else{
        //TODO POTENTIALLY A PROBLEM HERE
        //NEEDS MORE TESTING TO BE SURE
        if (inputVec[m][1] <= target){return m;}
        else{return m-1;}
    }
}

//function that calls overloaded getAvg function
//while getting the low/high indexes
//and handling a possible error
double seg_tree::getAvg(double low, double high){
    //gets low/high indexes
    int lowIndex = binarySearch(true, 0, inputVec.size()-1, low);
    int highIndex = binarySearch(false, 0, inputVec.size()-1, high);

    //if index is invalid the input is invalid
    if (highIndex == -1){return -999;}

    //calls overloaded function
    return getAvg(0,inputVec.size()-1 ,lowIndex, highIndex, root) / (highIndex - lowIndex + 1);
}

// //function that calls overloaded getAvg function
// //while getting the high indexes
// //and handling a possible error
// //low index is 0 since start is starting point in this case
// double seg_tree::getAvg(double high){
//     //gets high index
//     int highIndex = binarySearch(0, 0, inputVec.size()-1, high);

//     //if index is invalid the input is invalid
//     if (highIndex == -1){return -999;}

//     //calls overloaded function
//     return getAvg(0,inputVec.size()-1 ,0, highIndex, root) / (highIndex+1);
// }

//function that gets the average gas price
//between the inputted low/high indexes
//traverses the segment tree for this query
double seg_tree::getAvg(int currentNodeLow, int currentNodeHigh, int searchLow, int searchHigh, Node* currentNode){
    //if the current high/low is out of range or
    //current node is null then return
    if (searchHigh < currentNodeLow || currentNodeHigh < searchLow || !currentNode){
        return 0;
    }

    //if current high/low fall in between
    //search high/low add it to the sum
    if (searchLow <= currentNodeLow && currentNodeHigh <= searchHigh){
        return currentNode->gasPrice;
    }

    //calculates mid
    int mid = std::ceil((currentNodeHigh + currentNodeLow) / 2.0);

    //recursively traverses the tree
    //and adds up the sum price
    return getAvg(currentNodeLow, mid-1, searchLow, searchHigh, currentNode->left)
           + getAvg(mid, currentNodeHigh, searchLow, searchHigh, currentNode->right);
}

//function that calls overloaded getHighLow function
//while getting the low/high indexes
//and handling a possible error
std::pair<double, double> seg_tree::getHighLow(double low, double high){
    //gets high/low indexes
    int lowIndex = binarySearch(true, 0, inputVec.size()-1, low);
    int highIndex = binarySearch(false, 0, inputVec.size()-1, high);

    //if high index is not possible
    //the invalid input
    if (highIndex == -1){return {-999, -999};}

    //calls overloaded function
    return getHighLow(0,inputVec.size()-1 ,lowIndex, highIndex, root, {999, -999});
}

//function that calls overloaded getHighLow function
//while getting the high indexes
//and handling a possible error
//low index is 0 since start is starting point in this case
std::pair<double, double> seg_tree::getHighLow(double high){
    //gets high index
    int highIndex = binarySearch(false, 0, inputVec.size()-1, high);

    //if high index is not possible
    //the invalid input
    if (highIndex == -1){return {-999, -999};}

    //calls overloaded function
    return getHighLow(0,inputVec.size()-1 ,0, highIndex, root, {999, -999});
}

//function that gets the lowest/highest gas price
//between the inputted low/high indexes
//traverses the segment tree for this query
std::pair<double, double> seg_tree::getHighLow(int currentNodeLow, int currentNodeHigh, int searchLow, int searchHigh, Node *currentNode, std::pair<double, double> highLow) {
    //if the current high/low is out of range or
    //current node is null then return
    if (searchHigh < currentNodeLow || currentNodeHigh < searchLow || !currentNode) {
        return highLow;
    }

    //updates the current low/high price
    //if it needs to be
    if (searchLow <= currentNodeLow && currentNodeHigh <= searchHigh){
        if (currentNode->lowPrice < highLow.first){
            highLow.first = currentNode->lowPrice;
        }
        if (currentNode->highPrice > highLow.second){
            highLow.second = currentNode->highPrice;
        }
        return highLow;
    }

    //gets mid point
    int mid = std::ceil((currentNodeHigh + currentNodeLow) / 2.0);

    //recursively traverses the tree
    //and gets the high/low prices
    highLow = getHighLow(currentNodeLow, mid-1, searchLow, searchHigh, currentNode->left, highLow);
    highLow = getHighLow(mid, currentNodeHigh, searchLow, searchHigh, currentNode->right, highLow);

    return highLow;
}

//function for calling the overloaded insertion function
//just handles a possible error and updates
//the input vector
void seg_tree::insert(int pos, double value){
    //if position index is not valid
    //then input is invalid
    if (pos < 0 || pos > inputVec.size()-1){
        std::cout << "invalid input\n";
        return;
    }

    //calls overloaded function
    insert(pos, 0, inputVec.size()-1, value, root);
    //updates the input vector
    inputVec[pos][0] = value;
}

//function for updating the segment tree's
//gas prices
void seg_tree::insert(int pos, int low, int high, double add, Node* currentNode){
    //if current node doesnt exist return
    if (!currentNode){return;}

    //change the current nodes gas price to updated price
    currentNode->addGasPrice(add - inputVec[pos][0]);

    //calculates mid point
    int mid = std::ceil((low + high) / 2.0);

    //goes to the next node that contains
    //the position that is being updated
    if (low <= pos && mid-1 >= pos){
        insert(pos, low, mid-1, add, currentNode->left);

    }
    else{
        insert(pos, mid, high, add, currentNode->right);
    }

    //if current node is a leaf node
    //set low and high price to the only
    //possible value
    if (low == high){
        currentNode->lowPrice = add;
        currentNode->highPrice = add;
    }
    else {
        //variables to hold left/right children's
        //low/high prices to update current node's
        //low/high later
        double tempLeftLow = currentNode->left->lowPrice;
        double tempLeftHigh = currentNode->left->highPrice;

        double tempRightLow = currentNode->right->lowPrice;
        double tempRightHigh = currentNode->right->highPrice;

        //updates current nodes high/low price
        if (tempLeftLow < tempRightLow){
            currentNode->lowPrice = tempLeftLow;
        }
        else{
            currentNode->lowPrice = tempRightLow;
        }

        if (tempLeftHigh > tempRightHigh){
            currentNode->highPrice = tempLeftHigh;
        }
        else{
            currentNode->highPrice = tempRightHigh;
        }

    }
    return;
}

//function for writing the dot file
void seg_tree::writeFile(std::string ifname){
    //uses inputted file name to make the output
    //file name
    std::string ofname = ifname.substr(0, ifname.rfind('.')) + "_output.dot";
    std::ofstream outfile;
    outfile.open(ofname);

    //start of the dot file
    outfile <<"digraph BST {\n";

    //stringifies root node for dot file
    std::string rootString = getNodeString(root, 0, inputVec.size()-1);
    //if the tree is empty then write empty line
    if (root == nullptr){
        outfile<< "\n";
    }
    //if root has no children then just
    //write the root
    else if (root->right == nullptr && root->left == nullptr){
        outfile<< "\t" << rootString << ";\n" ;
    }
    //else write the entire tree
    else{
        writeNode(0, inputVec.size()-1, root, outfile);
    }
    outfile<<"}\n";
}

//function for writing all the nodes
//of a segment tree to a dot file
void seg_tree::writeNode(int low, int high, Node* node, std::ofstream& outfile)
{
    //calculates mid point
    int mid = std::ceil((low + high) / 2.0);
    //stringifies current node
    std::string nodeString = getNodeString(node, low, high);

    //if current node has a left child then write that left child
    if (node->left != nullptr)
    {
        std::string left = getNodeString(node->left, low, mid-1);
        outfile << "\t"<< nodeString << " -> " << left << ";\n";
        writeNode(low, mid-1,node->left, outfile);
    }

    //if node has right child then write that right child
    if (node->right != nullptr)
    {
        std::string right = getNodeString(node->right, mid, high);
        outfile << "\t" << nodeString <<  " -> " << right << ";\n";
        writeNode(mid, high, node->right, outfile);
    }
}

//stringifies the data of a node
//for the dot file
std::string seg_tree::getNodeString(Node* node, int low, int high){
    std::ostringstream sumPrice;
    sumPrice << std::fixed << std::setprecision(2) << node->gasPrice;
    std::ostringstream lowPrice;
    lowPrice << std::fixed << std::setprecision(2) << node->lowPrice;
    std::ostringstream highPrice;
    highPrice << std::fixed << std::setprecision(2) << node->highPrice;

    std::string nodeString =
            "\"" + std::to_string(low) + "to" + std::to_string(high) +
            "\\nSum Price:" + sumPrice.str() + "\\nLow Price:" + lowPrice.str() +
            "\\nHigh Price:"+ highPrice.str() + "\"";

    return nodeString;
}
