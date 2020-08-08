/* 
This file defines the nodes that will be represented by each element in the 2D matrix. The nodes 
have color, weight, both integers, and the booleans isPivot and visited, to make the Depth Iterative 
First Seach algorithm possible. 
*/

#include "Node.h"

using namespace std; 

bool Node::onCorner(vector< vector<int> > &matrix_2D, int i, int j) {
  return (((i == (matrix_2D.size() - 1)) && (j == (matrix_2D.size() - 1))) || ((i == 0) && (j == matrix_2D.size() - 1)) || ((i == matrix_2D.size() - 1) && (j == 0)));
};

// returns true if the element is located on the sides, without including the corners above
bool Node::onVector(vector< vector<int> > &matrix_2D, int i, int j) {
  return ((i == 0) || (j == 0) || (i == matrix_2D.size() - 1) || (j == matrix_2D.size() - 1));
}; 

// returns true if the element (i, j) is the initial pivot, located on the (0, 0) position
bool Node::onPivot(int i, int j) {
  return ((i == 0) && (j == 0));
};

// creates a 2D node grid, returning the address of the mentioned vector
vector< vector<Node*> > Node::create_2D_node_grid(vector< vector<int> > &matrix_2D) {
  vector< vector<Node*> > solution(matrix_2D.size(), vector<Node*>(matrix_2D.size()));
  for (int i = 0; i < matrix_2D.size(); i++) {
    for (int j = 0; j < matrix_2D.size(); j++) {
      if(Node::onCorner(matrix_2D, i, j)) {
        Node *node = new Node(matrix_2D[i][j], 2, false, false);
        solution[i][j] = node; 
      } else if(Node::onVector(matrix_2D, i, j)) {
        if(Node::onPivot(i, j)) {
          Node *node2 = new Node(matrix_2D[i][j], 5, true, false);
          solution[i][j] = node2;
          continue; 
        }
          Node *node3 = new Node(matrix_2D[i][j], 3, false, false);
          solution[i][j] = node3; 
      } else {
        Node *node4 = new Node(matrix_2D[i][j], 4, false, false);
        solution[i][j] = node4;
      };
    };
  };
  return solution;
};

// display the 2D node grid
void Node::display_2D_node_grid(vector < vector<Node *> > &node_2D_grid) {
  cout << "Displaying node matrix: " << endl; 
  for (int i = 0; i < node_2D_grid.size(); i++) {
    for (int j = 0; j < node_2D_grid.size(); j++) {
      cout << node_2D_grid[i][j]->color;
    };
    cout << endl; 
  };
}; 

