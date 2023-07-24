//Group 3
//James McCaffrey
//Shuichi Kameda
//Evan Ung
//Michael Gilkeson
//Segment Trees
//7/24/23
#include "seg_tree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <iostream>

//function that converts degrees to radians
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

//function that approximates the distance between
//2 longitude latitude degree coordinates in miles
//reference https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator
double calcDistance(double lat1, double lon1, double lat2, double lon2) {
    //approximation of the radius of earth in miles
    double earthRadius = 3958.8;

    //Haversine formula
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
               cos(toRadians(lat1)) * cos(toRadians(lat2)) *
               sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    return earthRadius * c;
}

//this is an aux function for quickSort
//it sorts the vector by its distance from
//the starting position
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

//this is a quickSort function
//it sorts the vector by its distance from
//the starting position
//reference https://www.geeksforgeeks.org/cpp-program-for-quicksort/
void quickSort(std::vector<std::vector<double>> * sortVector, int low, int high){
    if (low < high) {
        int pi = partition(sortVector, low, high);

        quickSort(sortVector, low, pi - 1);
        quickSort(sortVector, pi + 1, high);
    }
}

//function for reading in the input file
//into a 2d double vector and calculating
//the distance between
std::vector <std::vector<double>> readVector(std::string fname) {
    //initializes some variables
    std::vector <std::vector<double>> inputVec;
    std::string inputString;
    std::string element;

    //starts file streaming
    std::ifstream infile{fname};
    while (infile.fail()) {
        std::cout << fname << " doesn't exist, input a valid file name (Enter 'Q' to exit program): ";
        std::cin >> fname;
        if (fname.length() == 1) {
            if (fname[0] == 'Q') {
                exit(0);
            }
        }
        infile.open(fname);
    }
    std::getline(infile, inputString);

    //starts string streaming and gets starting
    //position longitude and latitude
    std::stringstream stream(inputString);
    stream >> element;
    double latitude = std::stod(element);
    stream >> element;
    double longitude = std::stod(element);

    //initializes variables that hold
    //a gas stations longitude/latitude coordinates
    double stationLong;
    double stationLat;

    //while loop goes through the entire input file
    //and puts data from it into the input vector
    std::vector<double> lineVector;
    while (std::getline(infile, inputString)){
        std::stringstream stream(inputString);

        //this pushes the gas price to the vector
        stream >> element;
        lineVector.push_back(std::stod(element));

        //this stores the gas station longitude/latitude
        //coordinates
        stream >> element;
        stationLat = std::stod(element);
        stream >> element;
        stationLong = std::stod(element);


        //this calculates the distance between the starting
        //position and the gas station position in miles
        //and pushes back that distance to the vector
        lineVector.push_back(calcDistance(latitude, longitude, stationLat, stationLong));

        //pushes back the temporary vector
        //into the input vector and empties
        //the temp vector for the next gas station
        inputVec.push_back(lineVector);
        lineVector = {};
    }

    //sorts the input vector in ascending order
    //based on distance to starting position
    quickSort(&inputVec, 0, inputVec.size()-1);

    return inputVec;
}

//function for asking the user
//if they want to exit
bool exit(){
    std::string input;
    std::cout << "\nInput 'yes' to exit, otherwise enter any key to return to menu: ";
    std::cin >> input;

    //changes any uppercase characters to lowercase
    for (int i = 0; i < input.length(); i++) {
        if (isupper(input[i])) {
            input[i] += 32;
        }
    }

    if (input == "yes") {return true;}
    else{return false;}
}

//function for printing out
//the options the program has
void printOptions(){
    std::cout
            << "\n====================================================================\n\n"
            << "[1] - Change a gas price\n"
            << "[2] - Get average gas price from starting position\n"
            << "[3] - Get average gas price from specified range\n"
            << "[4] - Get lowest/highest gas price from a starting position\n"
            << "[5] - Get lowest/highest gas price from specified range\n"
            << "[6] - Exit the program write the DOT file\n\n"
            << "Please input your choice:";
}

//function for changing a gas price
//this will update the segment tree
//as well as the input vector
//in the object
void choice1(seg_tree *st){
    //prints out the vector
    std::cout << "\n";
    st->printVector();

    //initializes input variables
    std::string stationChoice;
    std::string newPrice;

    //gets inputs
    std::cout << "Please input the index of which gas price you would like to update:";
    std::cin >> stationChoice;
    std::cout << "Please input the new gas price:";
    std::cin >> newPrice;

    //tries to do the insert function with
    //inputted variables catches error
    //if inputs cannot convert to double
    try{
        st->insert(std::stoi(stationChoice), std::stod(newPrice));
    }
    catch(std::exception &err) {
        std::cout << "\nInvalid input\n";
    }
}

//function for getting average
//gas price from starting position
//to inputted distance
void choice2(seg_tree *st){
    //gets input from user
    std::string high;
    std::cout << "\nInput the maximum distance from the starting point (in miles):";
    std::cin >> high;

    //tries to call average function
    //catches error if input cannot
    //be converted to double
    try{
        //if the input is negative
        //then input is invalid
        if (std::stod(high) < 0.0){
            std::cout << "\nInvalid input\n";
        }
        else {
            double average = st->getAvg(std::stod(high));
            if (average == -999){
                std::cout << "\nMaximum distance too small\n";
            }
            else{
                std::cout
                        << "\nThe average gas price in this area is: $" << std::fixed << std::setprecision(2)
                        << average << "\n";
            }
        }
    }
    catch(std::exception &err){
        std::cout << "\nInvalid input\n";
    }
}

//function for getting average gas price
//between 2 inputted distances from the
//starting position
void choice3(seg_tree *st){
    //gets user input
    std::string low;
    std::string high;

    std::cout << "\nInput the minimum distance from the starting point (in miles):";
    std::cin >> low;
    std::cout << "Input the maximum distance from the starting point (in miles):";
    std::cin >> high;

    //tries to call average function
    //catches error if input cannot
    //be converted to double
    try {
        //if either input is negative
        //then input(s) is invalid
        if (std::stod(high) < 0.0 || std::stod(low) < 0.0) {
            std::cout << "\nInvalid input\n";
        }
        else {
            double average = st->getAvg(std::stod(low), std::stod(high));
            if (average != -999){
                std::cout << "\nThe average gas price in this area is: $" << std::fixed << std::setprecision(2)
                          << average << "\n";
            }
            else {
                std::cout << "\nNo stations found between distances\n";
            }
        }
    }
    catch (std::exception &err){
        std::cout << "\nInvalid input\n";
    }
}

//function for finding the lowest/highest
//gas price from starting point to an inputted distance
void choice4(seg_tree *st){
    //gets input
    std::string high;

    std::cout << "\nInput the maximum distance from the starting point (in miles):";
    std::cin >> high;

    //tries to do getHighLow function with
    //inputted variables catches error
    //if inputs cannot convert to double
    try{
        //if input is negative
        //then input is invalid
        if (std::stod(high) < 0.0){
            std::cout << "\nInvalid input\n";
        }
        else {
            std::pair<double,double> lowHigh = st->getLowHigh(std::stod(high));
            if (lowHigh.first == -999 && lowHigh.second == -999) {
                std::cout << "\nNo stations found within that distance\n";
                return;
            }
            std::cout
                    << "\nThe lowest gas price in this area is: $" << std::fixed << std::setprecision(2)
                    << lowHigh.first << "\n";
            std::cout
                    << "\nThe highest gas price in this area is: $" << std::fixed << std::setprecision(2)
                    << lowHigh.second << "\n";
        }
    }
    catch(std::exception &err){
        std::cout << "\nInvalid input\n";
    }
}

void choice5(seg_tree *st){
    //gets input
    std::string low;
    std::string high;

    std::cout << "\nInput the minimum distance from the starting point (in miles):";
    std::cin >> low;
    std::cout << "Input the maximum distance from the starting point (in miles):";
    std::cin >> high;

    //tries to call getHighLow function
    //catches error if input cannot
    //be converted to double
    try {
        //if either input is negative
        //then input(s) is invalid
        if (std::stod(high) < 0.0 || std::stod(low) < 0.0) {
            std::cout << "\nInvalid input\n";
        }
        else {
            std::pair<double,double> lowHigh = st->getLowHigh(std::stod(low), std::stod(high));
            if (lowHigh.first == -999 && lowHigh.second == -999) {
                std::cout << "\nNo stations found within that distance\n";
                return;
            }
            std::cout
                    << "\nThe lowest gas price in this area is: $" << std::fixed << std::setprecision(2)
                    << lowHigh.first << "\n";
            std::cout
                    << "\nThe highest gas price in this area is: $" << std::fixed << std::setprecision(2)
                    << lowHigh.second << "\n";
        }
    }
    catch (std::exception &err){
        std::cout << "\nInvalid input\n";
    }
}

//function for getting user input
//to call other functions
void options(seg_tree st){
    //loops getting the choice
    //until user exits
    bool loop = true;
    while (loop) {
        //prints out options
        printOptions();

        //gets inputted choice
        std::string choice;
        std::cin >> choice;

        if (choice.size() == 1) {
            char cchoice = choice.at(0);

            //calls function
            //based on user's choice
            switch (cchoice) {
                case '1':
                    choice1(&st);
                    break;
                case '2':
                    choice2(&st);
                    break;
                case '3':
                    choice3(&st);
                    break;
                case '4':
                    choice4(&st);
                    break;
                case '5':
                    choice5(&st);
                    break;
                case '6':
                    loop = false;
                    break;
                default:
                    std::cout << "Invalid input\n";
                    break;
            }
        } else {
            std::cout << "Invalid input\n";
        }

        //checks if the user wants to exit
        if (loop) {
            loop = !exit();
        }
    }
}

//main function
int main(int argc, char*argv[]) {
    std::vector<std::vector<double>> intervalVec = readVector(argv[1]);
    seg_tree* st = new seg_tree(intervalVec);
    options(*st);
    st->writeFile(argv[1]);
    std::cout << "\nDOT file has been written\n";
    return 0;
}
