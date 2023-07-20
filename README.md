# segment-tree
Before compiling the program, please make sure to either create a valid input txt file, or have a valid input txt file.

To create a valid input file, you must format the input txt file as following:
[starting position longitude] [starting position latitude]
[gas station 1 gas price] [gas station 1 longitude] [gas 1 station latitude]
[gas station 2 gas price] [gas station 2 longitude] [gas 2 station latitude]
(add more gas stations using the same format)


Here is an example valid file input:

10.0 10.0

2.34 7 8

1.89 5 5

2.12 1 1"

3.45 9.2 2.8

1.52 0 22

5.67 3 0

1.01 90 1



Once you have a valid input file, you can compile the program with g++ with this command:

g++ main.cpp seg_tree.cpp node.cpp -o prog && ./prog (put input file name here)

Once you have compile the program, A list of options will be presented to you in the console like this: 

1 - change a gas price
2 - get average gas price from starting position
3 - get average gas price from specified range
4 - get lowest/highest gas price from a starting position
5 - get lowest/highest gas price from specified range

Just input the number that corresponds to the option you want

If you choose option 1, you will be presented with a list of gas station prices and their distances, along with their corresponding index number. Input the index of the gas station you want to change the price of. Then input the new price of gas. If all input was valid, then the gas price for that gas station will be updated in memory.

If you choose option 2, you will be asked to input a distance in miles. If your input was valid, the program will output the average gas price from the starting position to every gas station that falls in that inputted distance. 

If you choose option 3, you will be asked to input a minimum distance in miles, then a maximum distance in miles. If your input was valid, the program will output the average gas price in every gas station that falls between the minimum distance to the maximum distance . 

If you choose option 4, you will be asked to input a distance in miles. If your input was valid, the program will output the lowest and highest gas prices from the starting position to every gas station that falls in that inputted distance. 

If you choose option 5, you will be asked to input a minimum distance in miles, then a maximum distance in miles. If your input was valid, the program will output the lowest and highest gas prices in every gas station that falls between the minimum distance to the maximum distance.

After completing the inputs for any of the options, you can input ‘yes’ in order to exit the program. If The user chooses to exit the program, a dot file will be created named (name of input file)_output.dot and the program will exit.
