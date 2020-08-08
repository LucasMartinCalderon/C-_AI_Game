/* 
This file shows one of the main parts of the game, the intelligence of the computer. 
I have spent consirable time making an algorithm that optimises the numbers of steps 
to make the whole board the same color. The approach I have taken is by doing 3 different
steps. 
1) Grouping: the game performs a Depth Iterative First Search to look for all the islands
(and island is a group of connected nodes in the grid) present in the grid and to return 
a vector with both the vector with all the nodes (pointing to the right memory address) of the
pivot.
It does save time in the search by each node having one important bool value called visited. The island
2D matrix returned in sorted by the length of the island itself (a vector of Nodes).
2) A start minimun path search: This algorithm looks for the path between the pivot and the 
largest island taking two factors into consideration: it has to have the minimum number of steps
(nodes traversed) as well as, in case of equality, the path that has the most weight. Each node contains 
an integer of weight, that means, the number of edges (path between two nodes). This approach is very 
similar to some Artificial Intelligence Neural Networks, and I believe it is the fastest one. It means
that the algorithm will chose the shortest path with maximises the connection of the pivot through the 
weight of each individual node. Please note that I have adapted this algorithm to work in an undirected graph 
which has the shape of a 2D node grid, as this coursework requires, hence not 100% based on the A*, although close 
enough, in terms of weights and search algorithm.
3) Pivoting: making the pivot larger with every addition of nodes proposed by the A start algorithm that 
returns the optimal path described above. It will be done as many times as the vector proposed in the last 
step. Every time the pivot changes, it makes sure in case any node is left unchecked.
4) Computer tells player the minimum number of steps taken.
*/ 

#include "GameIntelligence.h"
#include <tuple>

using namespace std; 

bool GameIntelligence::visited[maxRow][maxCol] = {0}; 

// returns true if mat[row][col] is valid and hasn't been visited
bool GameIntelligence::isSafe(vector< vector<Node*> > &M, int row, int col, int c, int n, int l) {
	// If row and column are valid and element is matched and hasn't been visited the cell is safe
	return (row >= 0 && row < n) && (col >= 0 && col < l) && (M[row][col]->color == c && !GameIntelligence::visited[row][col]);
}; 

// Depth First Iterative Search Algorithm
void GameIntelligence::DFS(vector< vector<Node *> > &M, int row, int col, int c, int n, int l, vector< vector<Node *> > &solution, int &t, int s) {

  // traverse all neighbours position from each node
	int row_position[] = {-1, 1, 0, 0};
	int col_position[] = {0, 0, 1, -1};

	// mark as visited
	GameIntelligence::visited[row][col] = true;

	// recurring through all connected neighbours
	for (int k = 0; k < 4; k++) {
		if (GameIntelligence::isSafe(M, row + row_position[k], col + col_position[k], c, n, l)) {
			solution[t][s + 1] = M[row + row_position[k]][col + col_position[k]];
			DFS(M, row + row_position[k], col + col_position[k], c, n, l, solution, t, s + 1);
		};
	};
};

// sort vector function boolean to store in terms of length the vectors inside the vector
bool GameIntelligence::sort_length(vector<Node*> &e1, vector<Node*>  &e2) {
	return e1.size() > e2.size();
};

// returns a vector with one vector of vectors of connected components in the grid
tuple< vector< vector<Node*> >, vector<Node*> > GameIntelligence::grouping(vector< vector<Node*> > &M, int n) {

    // define the objects to return by the function grouping
    vector<vector<Node *>> island_groups;
  vector<Node *> pivot_group; 
  // declare some variables used in the function
  vector< vector<Node*> > solution(81, vector<Node*>(81));
  int l = M.size();
  int t = 0;
  int s = 0;


  // goes around that node checking also if it has already been visited
  for (int i = 0; i < n; i++) {
    for(int j = 0; j < l; j++) {
      if(!(GameIntelligence::visited[i][j])) {
        int c = M[i][j]->color;
        solution[t][s] = M[i][j];
        DFS(M, i, j, c, n, l, solution, t, s);
        t += 1;
      };
    };
  };

  // to create the island_group vector
  for (int i = 0; i < solution.size(); i++) {
    vector<Node *> aux;
    for (int j = 0; j < solution[i].size(); j++) {
      if (!(solution[i][j] == NULL))
      {
        aux.push_back(solution[i][j]);
      };
    };
    if(solution[i][0] == NULL) continue;
    island_groups.push_back(aux);
  };

  // this sorts the island_group from largest to shortest in terms of nodes present in each vector
  sort(island_groups.begin(), island_groups.end(), GameIntelligence::sort_length);

  for (int i = 0; i < island_groups.size(); i++) {
    for (int j = 0; j < island_groups[i].size(); j++)
    {
      if (island_groups[i][j]->isPivot && island_groups[i][j]->visited == false)
      {
        island_groups[i][j]->visited = true;
        for (int r = 0; r < island_groups[i].size(); r++) {
          island_groups[i][r]->visited = true; 
          island_groups[i][r]->isPivot = true;
          pivot_group.push_back(island_groups[i][r]);
        };
        // deletes all the elements that now belong to the pivot
        island_groups.erase(island_groups.begin() + i);
      };
    };
  };
  GameIntelligence::display_island_group(island_groups);
  GameIntelligence::display_pivot_group(pivot_group);
  return make_tuple(island_groups, pivot_group);
};

void GameIntelligence::display_island_group(vector< vector<Node*> > &island_group) {
  cout << "Displaying island group matrix, sorted from largest to shortest, without including the pivot:"  << endl << endl;
  cout << "[ ";
  for (int i = 0; i < island_group.size(); i++)
  {
    for (int j = 0; j < island_group[i].size(); j++) {
      cout << island_group[i][j]->color; 
    };
    cout << " ";
  };
  cout << "]" << endl; 
};

// displays the current pivot vector
void GameIntelligence::display_pivot_group(vector<Node*> &pivot_group) {
  cout << "The pivot vector is: [ ";
  for (int i = 0; i < pivot_group.size(); i++)
    cout << pivot_group[i]->color << " ";
  cout << "]";
  cout << endl; 
};

// // finds the coordinates of the first element in the islands group
tuple<int, int> GameIntelligence::find_coordinates(vector< vector<Node*> > &node_2D_grid, Node *destination) {
  for (int i = 0; i < node_2D_grid.size(); i++) {
    for (int j = 0; j < node_2D_grid.size(); j++) {
      if(node_2D_grid[i][j] == destination)
        return make_tuple(i, j);
    }
  }
  return make_tuple(0, 0);
};

// to find the optimal path between pivot and destination node
vector<Node*> GameIntelligence::optimal_path(vector< vector<Node*> > &node_2D_grid, Node *destination, vector< vector<Node*> > &island_groups, int island_row_number) {
  vector<Node *> path;
  int i, j;
  tie(i, j) = GameIntelligence::find_coordinates(node_2D_grid, destination);
  while(!((i == 0) && (j == 0))) {
    if(i == 0) {
      path.push_back(node_2D_grid[i][j - 1]);
      j--;
    } else if(j == 0) {
      path.push_back(node_2D_grid[i - 1][j]);
      i--;
    } else if (node_2D_grid[i][j - 1]->weight >= node_2D_grid[i - 1][j]->weight) {
      path.push_back(node_2D_grid[i][j - 1]);
      j--;
    } else {
      path.push_back(node_2D_grid[i - 1][j]);
      i--;
    };
  }
  reverse(begin(path), end(path));
  // erase the nodes of the path that already belong to the pivot group
  for (int i = 0; i < path.size(); i++) {
    if(path[i]->isPivot) {
      path.erase(path.begin());
    }
  };

  for (int i = 0; i < island_groups[island_row_number].size(); i++) {
    path.push_back(island_groups[island_row_number][i]);
  };
  island_groups.erase(island_groups.begin() + island_row_number);

  return path;
};

// changing the values of each node to turn into a pivot 
void GameIntelligence::pivoting(vector< vector<Node *> > &node_2D_grid, Node *next_node, vector<Node*> &pivot_group) {
  next_node->isPivot = true;
  pivot_group.push_back(next_node);
  for (int i = 0; i < node_2D_grid.size(); i++)
  {
    for (int j = 0; j < node_2D_grid[i].size(); j++) {
      if(node_2D_grid[i][j]->isPivot) {
        node_2D_grid[i][j]->color = next_node->color;
      }
    }
  }
}; 

// to know if node might belong to the pivot group
bool GameIntelligence::adjacent_pivot(Node *island_node, vector<Node*> &pivot_group, vector< vector<Node*> > &node_2D_grid) {
  int i, j;
  int row_position[] = {-1, 1, 0, 0};
	int col_position[] = {0, 0, 1, -1};
  tie(i, j) = GameIntelligence::find_coordinates(node_2D_grid, island_node);

  for (int k = 0; k < 4; k++) {
    if (((i + row_position[k]) >= 0) && ((i + row_position[k]) < node_2D_grid.size()) && ((j + col_position[k]) >= 0) && ((j + col_position[k]) < node_2D_grid.size())) {
      if(node_2D_grid[i + row_position[k]][j + col_position[k]]->isPivot) {
        return true; 
      }
    }
  }
  return false;
}; 

// same as grouping but made for every time after pivoting is called
void GameIntelligence::regrouping(vector <vector<Node*> > &node_2D_grid, vector<Node*> &pivot_group, vector< vector<Node*> > &island_groups) {
  for (int i = 0; i < island_groups.size(); i++) {
    if((island_groups[i][0]->color == node_2D_grid[0][0]->color) && !(island_groups[i][0]->isPivot) && adjacent_pivot(island_groups[i][0], pivot_group, node_2D_grid)) {
      for(int r = 0; r < island_groups[i].size(); r++) {
        island_groups[i][r]->isPivot = true;
        pivot_group.push_back(island_groups[i][r]);
      };
      island_groups.erase(island_groups.begin() + i);
    }
  }
};

// displays the path
void GameIntelligence::display_path(vector<Node*> &path) {
  cout << "The optimal path is: [";
  for (int i = 0; i < path.size(); i++) {
    cout << path[i]->color << " "; 
  };
  cout << "]" << endl;
};

