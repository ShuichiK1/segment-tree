#include <iostream>
#include "vector"
#include "seg_tree.h"
#include "fstream"
#include "sstream"

int getSum(int low, int high, std::vector<int> test){
    int count = 0;
    for ( int i = low; i < high+1; i ++){
        count += test[i];
    }
    return count;
}

std::vector <int> readVector(std::string fname) {
    std::vector <int> inputVec;
    std::ifstream infile{fname};

    std::string inputString;

    std::string element;

    std::getline(infile, inputString);
    std::stringstream stream(inputString);
    while (stream >> element){
        inputVec.push_back(std::stoi(element));
    }

    return inputVec;
}

int main(int argc, char*argv[]) {
    std::vector<int> test = readVector(argv[1]);
    seg_tree* ss = new seg_tree(test);
    ss->root = new Node();
    ss->root = ss->genTree(0, test.size()-1);

    //SUMMATION TEST
    for (int i = 0; i < test.size(); i++){
        for (int j = 0; j < test.size(); j++){
            if (i <= j){
                std::cout <<getSum(i, j, test)<< " " << ss->getValue(i,j) << "\n";
                if(getSum(i, j, test) != ss->getValue(i,j)){

                }
            }
        }
    }
    //SUMMATION TEST

    //random insertions
    ss->insert(6, 999999);
    ss->insert(2, 99999);
    ss->insert(3, 10);
    ss->insert(4, 1);
    ss->insert(5, 1);
    ss->insert(6, 1);
    ss->writeFile("test.dot", ss->root);
    return 0;
}