# back-propagation-algorithm
To run the program follow the steps below
1.) make the program with the "make" command. An executable called "ann" will be created in the current directory.
2.) type "./ann input/train_input.txt output/train_output.txt input/test_input.txt output/test_output.txt structure/structure.txt weights/weights.txt i" into the command line...please not that "i" must be an integer, which coorelates to the number of iterations to run the back-propagation algorithm.

example results:  

0.0240335091303705  
0.0464925601605351  
-0.0064631570339245  
  
35.00%  
  
results explained:

The first three numbers are weights of the links from the first node of the last hidden layer to the nodes in the output layer printed to the screen.  
  
The percentage shown is how accurate the classifier was (calculated by the following formula):  
The number of correctly classified testing data points / Total number of testing data points  
  
There will also be a new file on your current directory called "ann_output.txt." This file contains the results of the classifications.

