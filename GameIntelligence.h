/* 
This file shows one of the main parts of the game, the intelligence of the computer. 
I have spent consirable time making an algorithm that optimises the numbers of steps 
to make the whole board the same color. The approach I have taken is by doing 3 different
steps. 
1) Grouping: the game performs a Depth Iterative First Search to look for all the islands
(and island is a group of connected nodes in the grid) present in the grid and to return 
a tuple with both the vector with all the nodes (pointing to the right memory address) of the
pivot and another vector of vectors of all the islands apart from the pivot itself. It does 
save time in the search by each node having one important bool value called visited. The island
2D matrix returned in sorted by the length of the island itself (a vector of Nodes).
2) A start minimun path search: This algorithm looks for the path between the pivot and the 
largest island taking two factors into consideration: it has to have the minimum number of steps
(nodes traversed) as well as, in case of equality, the path that has the most weight. Each node contains 
an integer of weight, that means, the number of edges (path between two nodes). This approach is very 
similar to some Artificial Intelligence Neural Networks, and I believe it is the fastest one. It means
that the algorithm will chose the shortest path with maximises the connection of the pivot through the 
weight of each individual node. 
3) Pivoting: making the pivot larger with every addition of nodes proposed by the A start algorithm that 
returns the optimal path described above. It will be done as many times as the vector proposed in the last 
step. Every time the pivot changes, it makes sure in case any node is left unchecked. Important to notice 
that all weights of the nodes of the pivot are 0, therefore I can always start from the position (0,0) and 
simplify the shortest path algorithm. 
4) Computer tells the player the minimum number of steps taken.
*/ 

#ifndef GAMEINTELLIGENCE_H
#define GAMEINTELLIGENCE_H

#include "Node.h"
#include "Game.h"
#include <tuple>     // to return two object from a function
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm> // remove and remove_if
#include <fstream>
#include <unistd.h> // to get the current path in both Linux and macOS (POSIX Compliant)
#include <stdexcept>
#include <typeinfo> // for testing, to get the type of any variable with typeid(variable).name();
#include <stdlib.h> // for atoi() function, to transform char to integers without modifying its represented integer value
#include <math.h> // to use sqrt() later on in the code
#include <time.h> // to create a random number

#define maxRow 81    // since the max is a matrix 9x9 of size
#define maxCol 81    // since the max is a matrix 9x9 of size

using namespace std; 

class GameIntelligence {

  public:

    // constructor set to default
    GameIntelligence() = default; 
    // to establish if the node in question has been visited or not
    bool static visited[maxRow][maxCol];

    // returns true if mat[row][col] is valid and hasn't been visited
    bool static isSafe(vector< vector<Node*> > &, int, int, int, int, int); 

    // Depth First Iterative Search Algorithm
    void static DFS(vector< vector<Node *> > &, int, int, int, int, int, vector< vector<Node *> > &, int &, int);

    // sort vector function to sort in terms of length of each individual island vector
    bool static sort_length(vector<Node *> &, vector<Node *> &); 

    // returns a tuple with one vector of vectors of connected components in the grid and another element with the elements in the pivot
    tuple< vector< vector<Node*> > , vector<Node*> > static grouping(vector< vector<Node *> > &, int); 

    // displays the current island_group matrix
    void static display_island_group(vector< vector<Node*> > &); 

    // displays the current pivot vector
    void static display_pivot_group(vector<Node *> &); 

    // finds the coordinates of the first element in the islands group
    tuple<int, int> static find_coordinates(vector< vector<Node *> > &, Node *);

    // finds the optimal path described at the beginning of the file
    vector<Node*> static optimal_path(vector< vector<Node*> > &, Node *, vector< vector<Node*> > &, int);

    // changing the values of each node to turn into a pivot
    void static pivoting(vector<vector <Node *> > &, Node *, vector<Node *> &);

    // to know if node might belong to the pivot group
    bool static adjacent_pivot(Node *, vector<Node *> &, vector< vector<Node *> > &);

    // same as grouping but made for every time after pivoting is called
    void static regrouping(vector< vector<Node *> > &, vector<Node *> &, vector< vector<Node *> > &);

    // displays the path
    void static display_path(vector<Node *> &);
};

#endif //!GAMEINTELLIGENCE_H