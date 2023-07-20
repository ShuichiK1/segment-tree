# segment-tree
Before compiling the program, please make sure to either create a valid input txt file, or have a valid input txt file.

To create a valid input file, you must format the input txt file as following:

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/06d7d50f-64de-42c0-a8fa-74be2421f4aa)



Here is an example valid file input:

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/d25bad01-22fd-4bef-aa91-2011b28ee9bf)




Once you have a valid input file, you can compile the program with g++ with this command:

g++ main.cpp seg_tree.cpp node.cpp -o prog && ./prog (put input file name here)

Once you have compile the program, A list of options will be presented to you in the console like this: 

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/d6cffa00-13a6-41a2-85f9-e7dd5827d99e)


Just input the number that corresponds to the option you want

If you choose option 1, you will be presented with a list of gas station prices and their distances, along with their corresponding index number. 
![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/a9b6484c-9d79-4d9e-a6e6-44ec32d487fb)

Input the index of the gas station you want to change the price of. Then input the new price of gas. If all input was valid, then the gas price for that gas station will be updated in memory.

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/f51305d9-9150-466d-9782-010ead8ab4fa)


If you choose option 2, you will be asked to input a distance in miles. If your input was valid, the program will output the average gas price from the starting position to every gas station that falls in that inputted distance. 

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/fbf1daee-09f7-4d2a-9381-31446be725d7)


If you choose option 3, you will be asked to input a minimum distance in miles, then a maximum distance in miles. If your input was valid, the program will output the average gas price in every gas station that falls between the minimum distance to the maximum distance.

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/821b2900-39d9-4bde-8480-7ca3b3aa928e)


If you choose option 4, you will be asked to input a distance in miles. If your input was valid, the program will output the lowest and highest gas prices from the starting position to every gas station that falls in that inputted distance. 

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/711c113e-bae5-4d94-81e3-a2a2b389c167)


If you choose option 5, you will be asked to input a minimum distance in miles, then a maximum distance in miles. If your input was valid, the program will output the lowest and highest gas prices in every gas station that falls between the minimum distance to the maximum distance.

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/293e9005-1c2b-4d6f-b1e3-a3ad6734c39b)


After completing the inputs for any of the options, you can input ‘yes’ in order to exit the program. If The user chooses to exit the program, a dot file will be created named (name of input file)_output.dot and the program will exit.

![image](https://github.com/ShuichiK1/segment-tree/assets/136614316/1295d415-c801-4d76-bb98-66c2b1b55c49)
