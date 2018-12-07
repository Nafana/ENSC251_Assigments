# Software Design and Analysis Assignments
All assignments were coded in C++, and compiled with the g++ compiler.

### Assignment 1
The task for this assignment was to implement some functions for [Linked Lists](https://en.wikipedia.org/wiki/Linked_list). The main method is in the `tests.cpp` file and preforms the Bubble Sort algorithm.
**Compilation Command**: `g++ tests.cpp Lists.cpp ListsExtra.cpp`

### Assignment 2
This assignment was to implement a simple version of the Sinking Ships game, the only task was to fit ships of different sizes onto a board of a set size randomly. It isn't the full game itself with turns, rather just the placing mechanism.
**Compilation Command**: `g++ source.cpp ShipBoard.cpp`

### Assignment 3
In this assignment we needed to implement a [heap](https://en.wikipedia.org/wiki/Heap_(data_structure)), and sort elements by inserting into the heap and then taking items out of the heap. The type of heap implemented was a max heap.
**Compilation Command**: `g++ heaps.cpp`

### Assignment 4
Similarly to Assignment 3, we needed to implement an [AATree](https://en.wikipedia.org/wiki/AA_tree) which is simpler version of the Red Black trees. We then needed to insert items into the AATree, and since it's self balancing just read the items out in sorted order by reverse traversal.

We also needed to compare the time to sort with [Heaps](https://en.wikipedia.org/wiki/Heap_(data_structure)) and [AATrees](https://en.wikipedia.org/wiki/AA_tree) hence why there are both files in this project directory.
**Compilation Command**: `g++ main.cpp heaps.cpp aatrees.cpp`

### Assignment 5
In this assignment we needed to make a [Sat Problem](https://en.wikipedia.org/wiki/Boolean_satisfiability_problem) solver, by reading in the equation set with a file of specific format. The project consists of a solver which naively gueses for the problem, and checks if they are a valid solution.
**Compilation Command**: `g++ main.cpp`

### Assignment 6 - Final Project
Our task was to implement the [ID3](https://en.wikipedia.org/wiki/ID3_algorithm) algorithm used to generate decision trees and classify objects based on certain attributes and values. This is an introductory algorithm into machine learning. Usually [ID3](https://en.wikipedia.org/wiki/ID3_algorithm) is used to classify attributes that aren't numerical, but rather categorical however this classifies numerical attributes with a similar process to the [C4.5](https://en.wikipedia.org/wiki/C4.5_algorithm) algorithm. Entropy and information gain calculations are used to determine how "good" a certain attribute is to split at for our decision tree.

Note that this algorithm is extremely prone to overfitting. This is not practical to use in the real world, however this is an introductory OOP course so.... what do you expect?

Please note that the data should be in [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) format, and the last attribute should be the class. Please also note this is a binary classifier which means it can only handle two possible classes.
**Compilation Command**: `g++ main.cpp`
To execute the program, simply add the file name to the run argument, for example if your executable was named "id3" the way to run the algorithm on a dataset in the file "data.txt" would be:
**Execute Instructions**: `./id3 data.txt` 

