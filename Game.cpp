/*
This file defines the member functions of the class Game, where the player chooses the next color of the pivot, the optimal path as well as 
displaying every state of the game on the console screen. 
*/ 

#include "Game.h"
#include <math.h>
#include <vector>

using namespace std; 

// converts a 2D matrix into a single dimension matrix
vector<int> Game::matrix_1D_convert(vector< vector<int> > &matrix_2D) {
  vector<int> solution; 
  for(int i = 0; i < matrix_2D[0].size(); i++) {
    for (int j = 0; j < matrix_2D.size(); j++) {
      solution.push_back(matrix_2D[i][j]);
      cout << matrix_2D[i][j];
    }
    cout << endl; 
  }; 
  return solution;
};

// tranforms a 1D vector into a 2D vector returning the address of this returned object 
vector< vector<int> > Game::matrix_2D_convert(vector<int> &matrix) {
  vector< vector<int> > solution(sqrt(matrix.size()), vector<int>(sqrt(matrix.size()))); 
  int t = 0, value;
  for (int i = 0; i < sqrt(matrix.size()); i++) {
    for (int j = 0; j < sqrt(matrix.size()); j++) {
      value = matrix[t];
      solution[i][j] = value;
      t++; 
    };
  };
  return solution;
};

// display the matrix on the screen on every single state
void Game::display_1D_matrix(vector<int> &matrix){
  int counter = 1; 
  cout << "The size of the matrix is: " << sqrt(matrix.size()) << " and the matrix displays as follows: " << endl; 
  for (auto i = matrix.begin(); i != matrix.end(); i++) {
    cout << *i; 
    if (counter == sqrt(matrix.size())) {
      cout << endl;
      counter = 0;
    };
   counter++;
  };
  cout << endl << endl;
};

// display 2D matrix
void Game::display_2D_matrix(vector< vector<int> > &matrix_2D) {
  for(int i = 0; i < matrix_2D[0].size(); i++) {
    for (int j = 0; j < matrix_2D[0].size(); j++) {
      cout << matrix_2D[i][j];
    };
    cout << endl;
  };
};

// to clear all user input
void Game::input_clear() {
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}; 

// creates random 2D matrix with specified size
void Game::create_random_matrix(vector<int> &matrix){
  int size = 0; 
  do {
    // clear input to avoid any infinite loop
    Game::input_clear(); 
    cout << "Please enter the desired size of your random matrix: " << endl;
    cin >> size;
  } while ((size < 3 || size > 9));
  for (int i = 0; i < size * size; i++) {
    matrix.push_back((rand() % 6) + 1);
  };
};


// makes groups (islands) of elements in the vector that are connected, that means, 
// elements that have the same color and are adjacent of one another. Create a vector of 
// those different islands and return it
// vector< vector< Node> > Game::grouping(vector< vector<int> > &matrix_2D){
  
// };  

// // to ask the user to play the game, fill the pivot and finish the game, as well as displaying the state of the matrix
// void Game::start(vector<int> &matrix) {
//   // ask the user which color he wants to choose
//   int color_int_choice; 
//   // 2D matrix declaration
//   vector< vector<int> > matrix_2D; 
//   // check for any run-time errors
//   vector< vector< vector<int> > > islands; 
//   do {
//     Game::input_clear(); 
//     cout << "Please select new color for the pivot that you would like to choose, from 1 to 6, excluding " << matrix[0] << " since the pivot already has this color" << endl;
//     cin >> color_int_choice;
//   } while (color_int_choice == matrix[0] || (color_int_choice < 3 && color_int_choice > 9));
//   // covert the 1D matrix into 2D matrix
//   matrix_2D = Game::matrix_2D_convert(matrix);
//   // fill the selected color with all the connecting nodes as well as changing the color of the pivot
//   islands = Game::grouping(matrix_2D);
// };

