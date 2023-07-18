#include "vector"
#include "seg_tree.h"
#include "fstream"
#include "sstream"
#include <cmath>

//TODO
//THIS IS JUST TEMPORARY
//WILL UPDATE WITH A BETTER SORTING ALGORITHM
std::vector<std::vector<double>> insertionSort(std::vector<std::vector<double>> vec, int n) {
    int i, j;
    std::vector<double> key;
    for (i = 1; i < n; i++) {
        key = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j][1] > key[1]) {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
    return vec;
}

std::vector <std::vector<double>> readVector(std::string fname) {
    std::vector <std::vector<double>> inputVec;

    std::ifstream infile{fname};

    std::string inputString;

    std::string element;

    int depth = 0;

    std::getline(infile, inputString);

    std::stringstream stream(inputString);
    stream >> element;
    double longitude = std::stod(element);
    stream >> element;
    double latitude = std::stod(element);

    double stationLong;
    double stationLat;

    std::vector<double> lineVector;
    while (std::getline(infile, inputString)){
        std::stringstream stream(inputString);

        stream >> element;
        lineVector.push_back(std::stod(element));

        stream >> element;
        stationLong = std::stod(element);
        stream >> element;
        stationLat = std::stod(element);

        lineVector.push_back(std::sqrt(std::pow(stationLong - longitude, 2) + std::pow(stationLat - latitude, 2)));

        depth++;
        inputVec.push_back(lineVector);
        lineVector = {};
    }

    inputVec = insertionSort(inputVec, inputVec.size());

    return inputVec;
}

int main(int argc, char*argv[]) {
    std::vector<std::vector<double>> intervalVec = readVector(argv[1]);
    seg_tree* ss = new seg_tree(intervalVec);

    ss->writeFile(argv[1]);
    return 0;
}
