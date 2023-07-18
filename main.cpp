#include "vector"
#include "seg_tree.h"
#include "fstream"
#include "sstream"
#include <cmath>
int partition(std::vector<std::vector<double>> * sortVector, int low, int high){
    double pivot = (*sortVector)[high][1];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if ((*sortVector)[j][1] < pivot) {
            i++;
            std::vector<double> temp;

            temp = (*sortVector)[i];
            (*sortVector)[i] = (*sortVector)[j];
            (*sortVector)[j] = temp;
        }
    }
    std::vector<double> temp;
    temp = (*sortVector)[i+1];
    (*sortVector)[i+1] = (*sortVector)[high];
    (*sortVector)[high] = temp;
    return (i + 1);
}

void quickSort(std::vector<std::vector<double>> * sortVector, int low, int high){
    if (low < high) {
        int pi = partition(sortVector, low, high);

        quickSort(sortVector, low, pi - 1);
        quickSort(sortVector, pi + 1, high);
    }
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

    quickSort(&inputVec, 0, inputVec.size()-1);

    return inputVec;
}

int main(int argc, char*argv[]) {
    std::vector<std::vector<double>> intervalVec = readVector(argv[1]);
    seg_tree* ss = new seg_tree(intervalVec);

    ss->writeFile(argv[1]);
    return 0;
}
