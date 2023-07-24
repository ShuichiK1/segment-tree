#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

// supplementary file for generating datasets with valid random values
// referenced from https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
double random_double(double min, double max) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = max - min;
    double result = random * diff;
    return min + result;
}

int main() {
    // random seed
    srand(time(0));

    double initial_lat = 0.0;
    double initial_lon = 0.0;
    int max_num = 0;

    std::cout
            << "Input starting latitude, longitude, and number\n"
            << "of lines in dataset in the following order:\n"
            << "<latitude> <longitude> <data>\n";

    std::cin >> initial_lat >> initial_lon >> max_num;

    std::string outputName = "dataset_" + std::to_string(max_num) + ".txt";
    std::ofstream file;
    file.open(outputName);

    file << std::fixed << std::setprecision(14) << initial_lat << " " << initial_lon << "\n";

    // generates max_num numbers of lines
    for (int i = 0; i < max_num; ++i) {
        file << std::fixed << std::setprecision(2) << random_double(2.5, 5.0) << " "
             << std::fixed << std::setprecision(14) << random_double(-90, 90) << " "
             << std::fixed << std::setprecision(14) << random_double(-180, 180) << "\n";
    }

    file.close();

    return 0;
}
