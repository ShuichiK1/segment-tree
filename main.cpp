#include "vector"
#include "seg_tree.h"
#include "fstream"
#include "sstream"
#include <cmath>
#include "iostream"

double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double calcDistance(double lat1, double lon1, double lat2, double lon2) {
    //approximation of the radius of earth in miles
    double earthRadius = 3960.0;

    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(toRadians(lat1)) * cos(toRadians(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return earthRadius * c;
}

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

        lineVector.push_back(calcDistance(latitude, longitude, stationLat, stationLong));

        depth++;
        inputVec.push_back(lineVector);
        lineVector = {};
    }

    quickSort(&inputVec, 0, inputVec.size()-1);

    return inputVec;
}

bool exit(){
    std::string input;
    std::cout << "\ninput 'yes' to exit: ";
    std::cin >> input;
    if (input == "yes") {return true;}
    else{return false;}
}

void options(seg_tree ss){
    bool loop = true;
    while (loop){
        std::cout
        << "please input your choice:\n"
        << "1 - change a gas price\n"
        << "2 - get average gas price from staring position\n"
        << "3 - get average gas price from specified range\n";
        std::string choice;
        std::cin >> choice;
        if (choice == "1"){
            ss.printVector();
            std::string stationChoice;
            std::string newPrice;

            std::cout << "please input the index of which gas price you would like to update:";
            std::cin >> stationChoice;
            std::cout << "please input the new gas price";
            std::cin >> newPrice;
            try{
                ss.insert(std::stoi(stationChoice), std::stod(newPrice));
            }
            catch(std::exception &err) {
                std::cout << "invalid input";
            }
        }
        else if (choice == "2"){
            std::string high;
            std::cout << "input the maximum distance: ";
            std::cin >> high;
            std::cout << "\nthe average gas price in this area is: $" << ss.getAvg(std::stod(high)) << "\n";
        }
        else if (choice == "3"){
            std::string low;
            std::string high;
            std::cout << "input the minumum distance: ";
            std::cin >> low;
            std::cout << "\ninput the maximum distance: ";
            std::cin >> high;
            std::cout << "\nthe average gas price in this area is: $" << ss.getAvg(std::stod(low),std::stod(high)) << "\n";
        }
        else {
            std::cout << "invalid input\n";
        }
        loop = !exit();
    }
}

int main(int argc, char*argv[]) {
    std::vector<std::vector<double>> intervalVec = readVector(argv[1]);
    seg_tree* ss = new seg_tree(intervalVec);
    options(*ss);
    ss->writeFile(argv[1]);
    std::cout << "dot file has been written\n";
    return 0;
}
