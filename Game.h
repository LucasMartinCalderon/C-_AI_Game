/*
This file defines the blueprints of the class Game, where the player chooses the next color of the pivot, the optimal path as well as 
displaying every state of the game on the console screen. 
*/ 

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std; 

class Game {
  public:
    // display the screen in every state
    void static display_1D_matrix(vector<int> &);
    // display the 2D matrix
    void static display_2D_matrix(vector< vector<int> > &);
    // to clear all input
    void static input_clear(); 
    // creates a random 2D matrix by letting the user choose its NxN size
    void static create_random_matrix(vector<int> &);
    // converts a 2D matrix to 1D matrix
    vector<int> static matrix_1D_convert(vector< vector<int> > &);
    // converts a 1D matrix into 2D
    vector< vector<int> > static matrix_2D_convert(vector<int> &);
    // the user plays with the matrix, choosing the next move
    // void static start(vector<int> &);
  private:
    vector<int> matrix; 
};

#endif // !GAME_H
