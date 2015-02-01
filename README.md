# back-propagation-algorithm
To run the program follow the steps below
1.) make the program with the "make" command. An executable called "ann" will be created in the current directory.
2.) type "./ann input/train_input.txt output/train_output.txt input/test_input.txt output/test_output.txt structure/structure.txt weights/weights.txt i" into the command line...please not that "i" must be an integer, which coorelates to the number of iterations to run the back-propagation algorithm.

The result explained:

The first three numbers are weights of the links from the first node of the last hidden layer to the nodes in the output layer printed to the screen.

The percentage is how accurate classifier was (calculated by the following formula):
The number of correctly classified testing data points / Total number of testing data points

There should also be a file on your current directory that was created called "ann_output.txt." This file contains the results of the classifications.

