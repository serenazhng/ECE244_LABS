//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file
// Programmed by: Serena Zhang

#include "GameState.h"
#include "globals.h"
#include <iostream>
using namespace std;

// Function prototypes (if you need)
bool fourInRow(GameState &x);
bool checkHorizontal(GameState &x, int r, int c, int turn);
bool checkVertical(GameState &x, int r, int c, int turn);
bool checkNegDiagonal(GameState &x, int r, int c, int turn);
bool checkPosDiagonal(GameState &x, int r, int c, int turn);
// initialize other functions!!

// Call playMove ONLY IF the move is valid (check before calling)
void playMove(GameState &game_state) {
  GameState &x = game_state; //MUST AMPERSAND TO NOT CREATE A COPY OF GAME_STATE!!!
  
  // Assign p based on which player's turn it is
  int p;
  bool turn = x.get_turn();
  if(turn == true){
    p = R;
  } else if(turn == false){
    p = Y;
  }

  // Change winner and change gameOver
  if(fourInRow(x) == true){
    x.set_winner(p);
    x.set_gameOver(true);
    return;
  } else {
    // Once move has been played, change:
    // Change turn if move is valid,
    x.set_turn(!turn);
    return; //neither won, continue playing
  }
}

/* FUNCTIONS */
// Function to check if the player got four in a row
bool fourInRow(GameState &x) {
  int p;
  bool t = x.get_turn();
  int row = x.get_selectedRow();
  int col = x.get_selectedColumn();

  if(t == true) {  // R's turn
    p = R;
  } else if(t == false) {  // Y's turn
    p = Y;
  }

  // Check every direction based on placement
  if (checkHorizontal(x, row, col, p)) {
    return true;
  } else if (checkVertical(x, row, col, p)) {
    return true;
  } else if (checkNegDiagonal(x, row, col, p)) {
    return true;
  } else if (checkPosDiagonal(x, row, col, p)) {
    return true;
  } else {
    return false;  // no four in a row
  }
}

// Check horizontal of where they placed
bool checkHorizontal(GameState &x, int r, int c, int turn) {
  int score = 1;  // keep track of # of repeats of same colour
  int count = 1;

  // Check to the right
  while ((c + count >= 0) && (c + count < boardSize)) {
    if (x.get_gameBoard(r, c + count) == turn) {  // while it continues being the same colour, keep going
      score++;
      count++;
    } else {
      break;  // no repeats
    }
  }
  count = 1;
  // Check to the left
  while ((c - count >= 0) && (c - count < boardSize)) {
    if (x.get_gameBoard(r, c - count) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  if (score == 4) {  // counted four in a row horizontally
    return true;
  } else {
    return false;
  }
}

// Check vertically of where they placed
bool checkVertical(GameState &x, int r, int c, int turn) {
  int score = 1;
  int count = 1;

  // Check to the bottom
  while ((r + count >= 0) && (r + count < boardSize)) {
    if (x.get_gameBoard(r + count, c) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  count = 1;
  // Check to the top
  while ((r - count >= 0) && (r - count < boardSize)) {
    if (x.get_gameBoard(r - count, c) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  if (score == 4) {
    return true;
  } else {
    return false;
  }
}

// Check NW to SE diagonal of where they placed
bool checkNegDiagonal(GameState &x, int r, int c, int turn) {
  int score = 1;
  int count = 1;

  // Check down and right
  while ((r + count >= 0) && (r + count < boardSize) && (c + count >= 0) &&
         (c + count < boardSize)) {
    if (x.get_gameBoard(r + count, c + count) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  count = 1;
  // Check up and left
  while ((r - count >= 0) && (r - count < boardSize) && (c - count >= 0) &&
         (c - count < boardSize)) {
    if (x.get_gameBoard(r - count, c - count) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  if (score == 4) {
    return true;
  } else {
    return false;
  }
}

// Check SW to NE diagonal
bool checkPosDiagonal(GameState &x, int r, int c, int turn) {
  int count = 1;
  int score = 1;

  // Check up and right
  while ((c + count < boardSize) && (r - count >= 0)) {
    if (x.get_gameBoard(r - count, c + count) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  count = 1;
  // Check down and left
  while ((r + count < boardSize) && (c - count >= 0)) {
    if (x.get_gameBoard(r + count, c - count) == turn) {
      score++;
      count++;
    } else {
      break;
    }
  }
  if (score == 4) {
    return true;
  } else {
    return false;
  }
}
/* EXTRA */
// function to check if row or col is out of bounds
// bool inBounds(int row, int col){
//     bool valid = true;
//     if((row >= boardSize) || (col >= boardSize) || (row < 0) || (col < 0)){
//       valid = false;
//     }
//     return valid;
//   }
