/* 
This file introduces the nodes that will be represented by each element in the 2D matrix. The nodes 
have color, weight, both integers, and the booleans isPivot and visited, to make the Depth Iterative 
First Seach algorithm possible. 
*/

#ifndef NODE_H
#define NODE_H

#include <tuple>
#include <string>
#include <fstream>
#include <unistd.h> // to get the current path in both Linux and macOS (POSIX Compliant)
#include <vector>
#include <stdexcept>
#include <typeinfo> // for testing, to get the type of any variable with typeid(variable).name();
#include <stdlib.h> // for atoi() function, to transform char to integers without modifying its represented integer value
#include <math.h> // to use sqrt() later on in the code
#include <time.h> // to create a random number
#include <stdio.h>
#include <iostream>

using namespace std;

// each element on the 2D node grid will be of type class with the following attributes
class Node {
  public:
   // declares the tailored contructor 
   Node(int color, int weight, bool isPivot, bool visited) : color(color), weight(weight), isPivot(isPivot), visited(visited) {};
   // declares the default constructor
   Node(){};
   // color is represented from an integer between [1, 6] and weight is 
   // the number of connections that each node has
   int color, weight; 
   // boolean values to determine whether the node belongs to be pivot or
   // has already been visited
   bool isPivot, visited;

   // returns true if the position (i, j) corresponds to one of the 4 outmost vertices
   bool static onCorner(vector< vector<int> > &, int, int); 

   // returns true if the element is located on the sides, without including the corners above
   bool static onVector(vector< vector<int> > &, int, int); 

   // returns true if the element (i, j) is the initial pivot, located on the (0, 0) position
   bool static onPivot(int, int);

   // creates a 2D node grid, returning the address of the mentioned vector
   vector< vector<Node *> > static create_2D_node_grid(vector< vector<int> > &);

   // display the 2D node grid
   void static display_2D_node_grid(vector < vector<Node *> > &);
};

#endif //!GAME_H