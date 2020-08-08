/* 
This file is the main file of the game, executing every function declared and define in the workspace 
in order to produce the desired result.
*/

#include "Game.h"
#include "Node.h"
#include "GameIntelligence.h"
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

// to get the current path in both Linux and macOS (POSIX Compliant)
#define get_path getcwd

using namespace std; 

void intro_display(bool first = true) {
  // displays "Welcome back to the game!" whe the user has already played at least once before in the same round
  cout << "****************************************" << endl; (first) ? 
  cout << "*         Welcome to the game!         *" << endl : cout << "*         Welcome back to the game!    *" << endl;
  cout << "****************************************" << endl;
  cout << endl << endl;
  cout << "Please select your option: " << endl;
  cout << "Enter (1) in the command line to manually input the size of the matrix from 3 to 9 both inclusive" << endl;
  cout << "Enter (2) in the command line to be able to enter the name of your selected file" << endl;
  cout << "Enter (3) for game instructions" << endl;
  cout << "Enter (4) to exit the game" << endl; 
};

void instuctions_display() {
  cout << "You will start from the top left node (named as the pivot). At each step of the game, you will choose one of the 6 colours"  << endl
       << "to change all the nodes connected with the pivot to this color. The definition of connection means: there is a path between" << endl
       << "the two nodes under the condition that each pair of adjacent nodes on this path is in the same color and shares an edge."    << endl
       << "In this way the player can paint the board from the pivot step by step until all nodes are in the same color. "              << endl;
  do {
    cout  << '\n'
          << "Press and enter any key to continue..." << endl
          << endl
          << endl;
} while (cin.get() != '\n');
};

string get_path_function( void ) {
  char buffer[FILENAME_MAX]; // stdio.h includes this functionality 
  get_path(buffer, FILENAME_MAX ); // named before getcwd (current working directory)
  string path(buffer);
  return path;
};

tuple<int, vector<int> > input_function() {
  // ask the user to input the name of the file
  string file_name;
  // read_file read object in C++
  ifstream read_file;
  // size will be the integer read from the file and matrix an vector with all the values in the vector in the file
  int matrix_size;
  vector<int> matrix_array; 
  // each line read by the programme
  string numberString;
  // opening the read_file and running Run-time checks for any user or system input error
  do {          
    cout << "Please input the name of the file: " << endl;
    // in this case, cin replaces the last value of cin that was 2, for another type
    cin >> file_name; 
    // adds .txt at the end of the file name
    file_name += ".txt";
    // name of the file object
    read_file.open(file_name); 
    if(!read_file) {
      cout << "The system cannot open the file, please make sure you have written the right name and that the file can" << endl
          << "be found on the same directory as this one: " << get_path_function() << endl
          << endl
          << endl;
    };
  } while(!read_file);
  // once it has successfully found and opened the file read the file
  while(getline(read_file, numberString)) {
    if(numberString.length() == 1) {
      //convert to integer from a string
      matrix_size = stoi(numberString);
      continue;
    };
    // stores each element in the matrix as it reads it
    for (int i = 0, j = 0; i < numberString.length(); i++) {
      if(isnumber(numberString[i])) {
        // this little trick turns characters into integers
        matrix_array.push_back((numberString[i] - '0'));
      };
    };
  };
  // closes the file that has been previously open, in order to avoid any memory leaks or problems
  read_file.close();
  return make_tuple(matrix_size, matrix_array);
};

// creates a random matrix at the desired size
void create_random_matrix(vector<int> &matrix){
  int size = 0; 
  do {
    Game::input_clear(); 
    // clears the input to be entered again
    cout << "Please enter the desired size of your random matrix: " << endl;
    cin >> size;
  } while ((size < 3 || size > 9));
  for (int i = 0; i < size * size; i++) {
    matrix.push_back((rand() % 6) + 1);
  };
};

int manual_play(int counter) {
  // better UI and UE
  cout << "Please enter any key to continue..." << endl; 
  // clear all previous input
  Game::input_clear();
  vector<int> matrix;
  vector< vector<int> > matrix_2D;
  vector< vector<Node *> > node_2D_grid;
  vector< vector<Node *> > island_groups;
  vector< Node *> pivot_group;
  int counter_user = 0;
  int i, j; 

  // clears all previous matrices
  matrix.clear();
  matrix_2D.clear();
  node_2D_grid.clear();
  island_groups.clear(); 
  pivot_group.clear(); 

  // generate random matrix for user
  create_random_matrix(matrix);
  matrix_2D = Game::matrix_2D_convert(matrix);
  // convert it into a node grid
  node_2D_grid = Node::create_2D_node_grid(matrix_2D);
  Node::display_2D_node_grid(node_2D_grid);

  while (pivot_group.size() < node_2D_grid.size() * node_2D_grid.size())
  {
    int ij, ji; 
    do
    {
      cout << "Please enter two integers, separated by a single whitespace (space bar) specifying the location on the 2D matrix" << endl 
          << "of the element that you want to select, from 0 - 5 both included. Please not that of "
          << " the pivot, since that is the color of the pivot, and has automatically been grouped already" << endl;
      cin >> ij >> ji;
      cout << "You selected number: " << node_2D_grid[ij][ji]->color << endl; 
      counter_user++;
    } while (node_2D_grid[ij][ji] == NULL);
    GameIntelligence::pivoting(node_2D_grid, node_2D_grid[ij][ji], pivot_group);
    Node::display_2D_node_grid(node_2D_grid);
    if(counter_user > counter - 1){
      cout << "Too many moves already! The computer has bit you! Try again!" << endl; 
      break; 
    }
  }
  return counter_user;
}

int main(int argc, const char** argv) {
  // Initilize other classes and functions
  // Game* game = new Game();
  // input of the user
  int input_choice;
  // boolean to know if the game has already played once
  bool first = true; 
  // integer value with the size of the matrix
  int size; 
  // vector of integers representing each element in the matrix
  GameIntelligence *game_intelligence = new GameIntelligence();
  do {
    vector< int > matrix;
    vector<int> matrix_aux; 
    vector< vector<int> > matrix_2D;
    vector< vector<Node *> > node_2D_grid;
    vector< vector<Node *> > island_groups;
    vector< Node *> pivot_group;
    vector<Node *> path;
    int t = 0;
    int s = 0;
    int i, j;
    int counter = 0;
    int counter_user = 0; 

    // intro to the game
    intro_display(first);
    // get the input choice of the user
    cin >> input_choice;
    // to make the user interface in the command line simpler 
    system("clear");

    switch (input_choice) {
    /* 
    The user inputs the size of the matrix and starts playing step by step, until they finish and
    are compared to the optimal algorithm of the computer. 
    */
    case 1:
      // create random matrix
      create_random_matrix(matrix);
      // convert into a 2D matrix
      matrix_2D = Game::matrix_2D_convert(matrix);
      // convert it into a node grid
      node_2D_grid = Node::create_2D_node_grid(matrix_2D);
      // display the 2D node grid
      Node::display_2D_node_grid(node_2D_grid);
      // let's the user play at first
      cout << endl;
      tie(island_groups, pivot_group) = GameIntelligence::grouping(node_2D_grid, node_2D_grid.size());
      cout << endl;
      while(island_groups.size() != 0) {
        for (int p = 0; p < island_groups.size(); p++) {
          path = GameIntelligence::optimal_path(node_2D_grid, island_groups[p][0], island_groups, p);
          GameIntelligence::regrouping(node_2D_grid, pivot_group, island_groups);
          for (int i = 0; i < path.size(); i++) {
            GameIntelligence::pivoting(node_2D_grid, path[i], pivot_group);
            GameIntelligence::regrouping(node_2D_grid, pivot_group, island_groups);
            cout << "(Step " << counter << ") - ";
            Node::display_2D_node_grid(node_2D_grid);
            GameIntelligence::display_island_group(island_groups);
            cout << endl;
            GameIntelligence::display_pivot_group(pivot_group);
            cout << endl; 
            GameIntelligence::display_path(path);
          };
          counter++;
        };
      };
      cout << endl; 
      cout << "*****************************Computer Final Result***************************************" << endl
          << "The computer was able to finish it in " << counter << " steps, if you have done fewer, congratulations!" << endl; 
      cout << "**************************************YOUR TURN!*****************************************" << endl;
      counter_user = manual_play(counter);
      (counter > counter_user) ? (cout << "You did better than the computer, congratulations!" << endl) : (cout << "The computer performed " << counter - counter_user << " fewer steps than you did, try again soon!" << endl);
      break;
    /* 
      The user inputs the size of the matrix and starts playing step by step, until they finish and
      are compared to the optimal algorithm of the computer. 
      */
    case 2:
      /* 
        The user inputs the size of the matrix and starts playing step by step, until they finish and
        are compared to the optimal algorithm of the computer. 
        Switch statements in C++ are not able to work if there is a transfer of program flow (the nature of switches) 
        if it bypasses in any of its cases a variable initialization in its scope. Hence, to make sure that the ifstream
        object initialization is not in the same scope, a pair of curly brackets is used.
        */
      {
        // store the tuple value from input_function into the local variables size and matrix
        tie(size, matrix) = input_function();
        // display the matrix and its size
        // convert into a 2D matrix
        matrix_2D = Game::matrix_2D_convert(matrix);
        // convert it into a node grid
        node_2D_grid = Node::create_2D_node_grid(matrix_2D);
        // display the 2D node grid
        Node::display_2D_node_grid(node_2D_grid);
        // let's the user play at first
        cout << endl;
        tie(island_groups, pivot_group) = GameIntelligence::grouping(node_2D_grid, node_2D_grid.size());
        cout << endl;
        while(island_groups.size() != 0) {
          for (int p = 0; p < island_groups.size(); p++) {
            path = GameIntelligence::optimal_path(node_2D_grid, island_groups[p][0], island_groups, p);
            GameIntelligence::regrouping(node_2D_grid, pivot_group, island_groups);
            for (int i = 0; i < path.size(); i++) {
              GameIntelligence::pivoting(node_2D_grid, path[i], pivot_group);
              GameIntelligence::regrouping(node_2D_grid, pivot_group, island_groups);
              cout << "(Step " << counter << ") - ";
              Node::display_2D_node_grid(node_2D_grid);
              GameIntelligence::display_island_group(island_groups);
              cout << endl;
              GameIntelligence::display_pivot_group(pivot_group);
              cout << endl; 
              GameIntelligence::display_path(path);
            };
            counter++;
          };
        };
        cout << endl; 
        cout << "*****************************Computer Final Result***************************************" << endl
            << "The computer was able to finish it in " << counter << " steps, if you have done fewer, congratulations!" << endl; 
        cout << "**************************************YOUR TURN!*****************************************" << endl;
        counter_user = manual_play(counter);
        (counter > counter_user) ? (cout << "You did better than the computer, congratulations!" << endl) : (cout << "The computer performed " << counter - counter_user << " fewer steps than you did, try again soon!" << endl);
        break;
       }
      case 3:
        instuctions_display();
        break;
      /* 
      Good-bye message from the computer after the users decides to exit the game and right before the 
      programme ends. 
      */
      case 4:
        cout << "Sorry to see you go!" << endl; 
        break; 
      /* 
      Run-time check, if the user does not input the right option, 
      the user is prompted the same intiial intructions message.
      */
      default:
        intro_display(false);
        cin >> input_choice;
        break;
      }
      // to display the right intro screen to the user while on the loop
      matrix.clear();
      node_2D_grid.clear();
      pivot_group.clear();
      island_groups.clear(); 
      // clear input so as not to create any infinite loops
      Game::input_clear();
  } while (input_choice != 4 || input_choice == 0);

  // return to finsish the game correctly and let the user knnow the game has terminated correctly
  return 0;
};
