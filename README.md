# segment-tree
A C++ implementation of a segment tree for the CSC212-Su23 DSA project.

## Overview
Our project allows for the querying of minimum, maximum, and average gas prices of a specified range from a given dataset. It also lets the user update the gas prices at specific gas stations. The project involves using a segment tree, which is a tree data structure that is useful for allowing efficient range queries and quick modifications over an array.

To begin, the user will require at least C++11 and a valid dataset. No additional installations are required, and the program is compatible with any operating software.

### Dataset
The dataset must be a text file with the following format:
```
<initial_latitude> <initial_longitude>
<gas_price ($/gal)> <latitude> <longitude>
...
...
...
```
Where ```initial_latitude``` and ```initial_longitude``` are determined by the user before compilation. The subsequent lines hold three items: ```gas_price```, ```latitude```, and ```longitude```. The gas price corresponds to the price of gas in USD per gallon at a gas station located at the latitude and longitude coordinate. The dataset can be of any size. You may use ```rand_data.cpp``` to generate a dataset containing usable random values.

To use the dataset generator, you can run it with an iteration of the following command:
```
g++ rand_data.cpp -o <file_name> && ./<file_name>
```

You can enter the initial coordinate as well as the desired size of the dataset within the terminal during runtime. Feel free to use any of the supplied data if you don't want to use the supplementary program.

## Compilation Instructions
To compile the main program, you must have access to ``main.cpp``, ``seg_tree.cpp``, ``node.cpp`` and the corresponding header files. To compile and run, you must provide an iteration of the following command:
```
g++ main.cpp seg_tree.cpp node.cpp -o <file_name> && ./<file_name> <data.txt>
```

The program only accepts one command line argument ``data.txt``, which is the name of the dataset. We will be using ``test.txt`` throughout the upcoming explanations.

## Runtime Instructions
Once the program is running, the user will be prompted with a terminal UI, allowing you to choose from several options. 
To choose an option, you must input the corresponding value, initiating a new process.
```
====================================================================

[1] - Change a gas price
[2] - Get average gas price from starting position
[3] - Get average gas price from specified range
[4] - Get lowest/highest gas price from a starting position
[5] - Get lowest/highest gas price from specified range
[6] - Exit the program write the DOT file

Please input your choice:
```
The user will be given the option to exit the program at the end of every process.
```
Input 'yes' to exit, otherwise enter any key to return to menu:
```

### [1] Change gas price
If the user enters **1**, the console will display, in a paginated format, the gas price and the calculated distance from the initial latitude and longitude values in ascending order. Each page will display 10 lines for an easier viewing experience, with each line showing their index. The user can "flip" the page by inputting **>** into the terminal, otherwise they can input **.** to stop flipping.
```
Please input your choice:**1**

Insert '>' to view next page, otherwise insert '.' to stop.

----- [Page 1] -----
[0] - $3.39     13.9932 mi.
[1] - $3.50     16.0063 mi.
[2] - $3.40     18.1993 mi.
[3] - $3.37     19.2406 mi.
[4] - $3.46     20.7851 mi.
[5] - $3.46     21.3774 mi.
[6] - $3.36     24.3799 mi.
[7] - $3.44     26.8181 mi.
[8] - $3.43     26.8326 mi.
[9] - $3.50     26.9842 mi.
.
```
Afterwards, the user can input the index at which they would like to update the gas price. 
```
Please input the index of which gas price you would like to update:5
Please input the new gas price:3.50
```
Once the price has been updated, the user may either exit the program or return to the menu.

### [2] Get average price from starting position
If the user enters **2**, they will be asked to provide a maximum distance. The terminal will then provide the average price of gas between the initial coordinates and the maximum distance. 
```
Please input your choice:2

Input the maximum distance from the starting point (in miles):50

The average gas price in this area is: $3.51
```
The user may either exit or return to menu afterwards.

### [3] Get average price from specified range
If the user enters **3**, they will be asked to provided a minimum distance and a maximum distance. By the same process as option 2, the program will retrieve the average price within the range.
```
Please input your choice:3

Input the minimum distance from the starting point (in miles):0
Input the maximum distance from the starting point (in mil
es):50

The average gas price in this area is: $3.51
```
The user may either exit or return to menu afterwards.

### [4] Get lowest/highest gas price from starting position
If the user enters **4**, they will be asked to provided a maximum distance. After which, the terminal will display the lowest and highest price of gas within the range.
```
Please input your choice:4

Input the maximum distance from the starting point (in miles):50

The lowest gas price in this area is: $3.36

The highest gas price in this area is: $3.70
```
The user may either exit or return to menu afterwards.

### [5] Get lowest/highest gas price from specified range
If the user enters **5**, they will be asked to provide a minimum distance and a maximum distance. Similar to option 4, the terminal will display the lowest and highest gas price withing the specified range.
```
Please input your choice:5

Input the minimum distance from the starting point (in miles):0
Input the maximum distance from the starting point (in miles):50

The lowest gas price in this area is: $3.36

The highest gas price in this area is: $3.70
```
The user may either exit or return to menu afterwards.

### [6] Exit the program and write DOT file
If the user enters **6**, the program will exit and a DOT file will be generated and written to the project directory. A DOT file will always be created upon successful closure of the program.
```
DOT file has been written
```

For ``test.txt``, the DOT file, when visualized, will look like the following:
![graph](https://github.com/ShuichiK1/segment-tree/assets/78115987/a92d3182-9e3c-4f2e-8a12-79ef209af4ca)

