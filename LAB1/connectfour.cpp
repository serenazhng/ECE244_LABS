//
//  connectfour.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file
// Programmed by: Serena Zhang

#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes
//void makeBoard(int col, int row);
void printBoard(GameState &x);
bool validCol(GameState &x, int col);
int validRow(GameState &x);

// The main function
int main() {
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds]; // object to hold info for 3 rounds

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col = 0;
  int round = 0;

  // Outer loop to loop for number of rounds
  for(round = 0; round < numOfRounds; round ++){
    int game = round + 1;
    cout << "Game " << game << endl;

    // While gameOver is false (continue playing)
    while (!game_state[round].get_gameOver()) {
      cout << "Enter column to place piece: ";
      cin >> col;
  
      if( cin.eof() ) {
        cerr << endl << "Game ended by user." << endl;
        exit( 0 );
      }
      if( cin.fail() ) {
        cin.clear() ;
        cin.ignore( 1000, '\n' );
        col = -1 ; // giving col invalid value so it will be handled as invalid input below
      }

      // Check validity of input and if not valid, handle accordingly
      // The coordinates are valid; set the selectedRow and selectedColumn
      // members of the game state to the read values

      // Call valid column function to check if column is within bounds or full
      if(validCol(game_state[round], col) == false){
        cout << "Invalid column!" << endl;
        continue;
      } else {
        game_state[round].set_selectedColumn(col); //set selectedColumn to col if valid
        cout << "column chosen: " << col << endl;
        game_state[round].set_moveValid(true); // set move to valid 
        // (since only the column chosen matters, my validRow function automatically drops the piece in a valid row)
      }

      // Check which row the selected column will fall to, set selectedRow
      // Call valid row function to drop the piece into the lowest row in selected column
      int row = validRow(game_state[round]);

      // This if statement is a bit redundant (it still works though)
      if(row > -1){
        game_state[round].set_selectedRow(row);
      } 

      // Now that we have checked that the selected column and row is valid,
      // let's update the gameboard
      int turn;

      // Update the gameboard based on who's turn it is
      bool player = game_state[round].get_turn();
      if(player == true){
        turn = R;
      } else if (player == false){
        turn = Y;
      }
      
      // Set the gameBoard
      game_state[round].set_gameBoard(row, col, turn); // set the newly inputted value

      // Call playMove
      playMove(game_state[round]);

      // Print the GameState object, as prescribed in the handout
      // print the board after every valid move
      printBoard(game_state[round]);
      cout << endl;

      // Check if a player won this round and if so handle accordingly
      int winner = game_state[round].get_winner(); // gets which player won this round
      bool over = game_state[round].get_gameOver(); // gets whether someone won the round or not
      if(over == true){
        char p;
        if(winner == 1){
          p = 'R';
        } else if(winner == -1){
          p = 'Y';
        }
        cout << p << " won this round!" << endl;
        break;

      // If no one won the round, repeat again
      } else { 
        continue;
      }

    }
    // Check if a player won this match and if so handle accordingly
    // Check if game is over by checking which player won which rounds

    //Store the winner of each round in w1, w2, w3
    int w1 = game_state[0].get_winner();
    int w2 = game_state[1].get_winner();
    int w3 = game_state[2].get_winner();

    // Check if someone won each round and store in o1, o2, o3
    bool o1 = game_state[0].get_gameOver();
    bool o2 = game_state[1].get_gameOver();
    bool o3 = game_state[2].get_gameOver();

    // Check every pairing of winners of previous rounds to determine overall winner of match

    // 1st and 2nd round
    if (round == 1) {  // must play at least 2 rounds to determine a winner
      if ((o1 == true) && (o2 == true) && (w1 == w2)) { 
        char p;
        if(w1 == 1){
          p = 'R';
        } else if (w1 == -1){
          p = 'Y';
        }
        cout << p << " won the match!" << endl;
        break;  // exit game
      } else if (o2 == false) {
        continue;  // no winner yet, continue to 3rd round
      }
    } else if (round == 2) {
      // 1st and 3rd round
      if((o1 == true) && (o3 == true) && (w1 == w3)){
        char p;
        if (w1 == 1) {
          p = 'R';
        } else if (w1 == -1) {
          p = 'Y';
        }
        cout << p << " won the match!" << endl;
        break; // exit game
        
      // 2nd and 3rd round
      } else if((o2 == true) && (o3 == true) && (w2 == w3)){
        char p;
        if (w2 == 1) {
          p = 'R';
        } else if (w2 == -1) {
          p = 'Y';
        }
        cout << p << " won the match!" << endl;
        break; // exit game
      }
    }
  }
  return 0;

}
/* FUNCTIONS */
// Checks if column chosen is out of bounds or is full
bool validCol(GameState &x, int col) {
  // if col is out of board bounds
  if (col >= boardSize || col < 0) {
    return false;
  }
  // if column is full
  bool full = true;
  for (int r = 0; r < boardSize; r++) {
    if (x.get_gameBoard(r, col) == Empty) {  // if a row in selected col is empty
      full = false;
      break;
    } else {  // else, column is full
      continue;
    }
  }
  if (full == true) {
    return false;
  } else {
    return true;
  }
}

// Finds the lowest row in column chosen
int validRow(GameState &x) {
  int col = x.get_selectedColumn();
  for (int r = boardSize - 1; r > -1; r--) {  // check from bottom row
    if (x.get_gameBoard(r, col) == Empty) {
      return r;
    } 
    // else {
    //   return -1;
    // }
  }
}

// Prints game board
void printBoard(GameState &x) {
  for (int r = 0; r < boardSize; r++) {
    for (int c = 0; c < boardSize; c++) {
      if (x.get_gameBoard(r, c) == Empty) {
        cout << '_';
        //continue;
      } else if (x.get_gameBoard(r, c) == R) {
        cout << 'R';
        //continue;
      } else if (x.get_gameBoard(r, c) == Y) {
        cout << 'Y';
        //continue;
      }
    }
    cout << endl;
  }
}
