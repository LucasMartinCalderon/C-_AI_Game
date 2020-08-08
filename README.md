# README: C++ AI-based GAME

First of all, at the start of the game, the layout is based on a graph, which connect nodes and super-nodes. The graph will be represented by a NxN matrix of nodes. Also, vectors of vectors of nodes, representing such Graph, were chosen due to their Big O properties of O(1) access and given that we can know beforehand the maximum size of the vector. Therefore, no resizing is necessary, which takes a lot of memory and space to compute automatically. Each node is an object, which replaces each element in the NxN matrix, with the following attributes:
1.	Edges: These point to other nodes, establishing the edges among them (links) in our NxN grid. There is one for each direction: right, left, up and down.
2.	Weight: The integer value of the weight if the node is connected to another node is 1. A node is connected if it is adjacent to another node that also has the same color. If the node is not connected to another node, then the total value of weight equals the number of edges that it has.
3.	Visited: A Boolean value to represent whether the node has already been visited by any kind of search during the execution of the game.
4.	Color: This is an integer value that ranges from [1, 6] representing one of the 6 different colors.
5.	IsPivot: Another Boolean value that represents whether this node belongs to the pivot chain.

Furthermore, a group of nodes is called a super-node. These nodes are connected to each other: they share an edge and a color, as mentioned above. One particularity of the super-nodes is that, although all the node attributes remain the same, is has the same memory allocation for all the nodes that have a common edge to this super-node but are not in the island_group. The vector island_groups is an example of such. More specifically, it holds vectors of vectors of nodes, arranged according to the size of the groups of nodes that are connected, that means, they share a common edge and are the same color. Nodes belonging to the pivot will not be included here.

Furthermore, in order to take full advantage of the nature of C++ in terms of memory management, the coursework presents the values and its references extensively. Although working with pointers and values might sometimes be risky, in this case it saves the game from creating new objects both in space and memory.

In order to compile it and link it, as well as creating the executable, please enter in the command line, in the same current working directory, containing all the files, the following line:


And in the same directory, I have:


And to execute it, please type or type make (recommended):

 
The game can be simplified to the following steps:
1.	Grouping: All nodes that share the same edge and have the same color become super-nodes groups. In a normal layout of the game, there can be several or none super-node at the very beginning. Each group is stored in a sorted array of super-nodes as well, called island_groups.
2.	DFS Searching: By using an adaptation of the Deep First Iterative Search Algorithm, the game finds in each iteration the best path from the pivot to the biggest island_group. The best path that this coursework proposes is an algorithm that finds the shortest path (minimum number of edges to cross) with the greater weight. That means that, if there are several paths with the same number of steps, the one crossing the nodes with the more amount of edges will be given higher priority and chosen first. In the case of having all the same values, the first path that was found will be used, given the nature of the island_groups data structure together will the path vector. It is also used to find the optimal path from the node located at origin (0, 0) to the first nodes of the first vector of nodes in island_groups.
3.	Pivoting: The process of adding more nodes or super-nodes (from the path previously found) to the pivot super-node is also known as pivoting. When pivoting occurs, all the color values of the nodes in the super-node change to that particular, chosen color. Please not that, given a new pivot super-node, some nodes that previously did not belong to the pivot and were not visited might be connected to it, and hence the importance to include step 1 (Grouping) again in each iteration of the pivoting process. Important step to do before expanding the pivot to the following node proposed by the DFS algorithm.
4.	Step 2 and 3 repeat continuously until the pivot contains NxN nodes, which will all be the same color.
5.	All these steps repeat until the vector of optimal_path is completed for each vector of nodes the island_group vector, given that it contains all the nodes of the grid.
6.	Returns the count of the computer and let’s the user play.

To complete this game, the following assumptions were made:
1.	The random function included in the C++ library is perfectly random.
2.	The file to be open if selected must be in the same directory as the original executable.
3.	The user has permission to read this file.
4.	C++17 version was used to test this game, hence assumed to be graded under the same version too. Please make sure you use << g++ -std=c++17 >> when compiling
5.	The size of the grid is 3x3 up to 9x9.
6.	Also, please note that I return several objects in from a function using tuples, and this has proven to fail in some systems, such as two virtual machines that I have executed this code on running Linux. I have however made sure that this library is Linux-compatible since then.

For compiling and linking the programme, a MakeFile will be provided. In order to maximise the potential of a Object-Oriented Design approach, this coursework presents the code in a very reusable structure, since all headers contain the general blueprints of the classes used and the .cpp files contain their definitions. The main.cpp file contains the general flow of the game. To start with, the project is divided into 10 different files, including the headers. The headers provide the overall blueprints of the data structures and design of the game. For each file, please find the comments for further information. Finally, main.cpp makes the game run as desired in the coursework.

Given the importance of memory management and Big O notation, along with the capabilities and strengths of the C++ programming language, Graphs were used due to their space usage proportional to V + E, being V and E being the nodes and their respective edges. Secondly, since the user will input an indefinite number of times a matrix or a new file, this data structure takes a constant time to add an edge to the graph, which is essential if the graphs become very long. Finally, it takes also constant time per adjacent vertex that has been visited.

The flow of the programme is as follows. First of all, the user will be prompted to select two modes: random NxN matrix or selected file. On one hand, if the user chooses the former, the user will be asked to introduce an integer equal or greater than 3 or equal or smaller than 9, which will represent the size of the square matrix. After the user input, the user will be able to play, step by step the game manually, without the computer automating the task. That means, the user will be able to select at each step of the game the color too. 

