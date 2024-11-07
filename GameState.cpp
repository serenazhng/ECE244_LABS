//
//  GameState.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "GameState.h"
#include "globals.h"

// ECE244 Student: add your code below
// Programmed by: Serena Zhang

// Initialize GameState() to default 'settings'
GameState::GameState(){ // CONSTRUCTOR
    selectedRow = 0;
    selectedColumn = 0;
    moveValid = false;
    gameOver = false;
    turn = true; // true: Red (Red starts so set to true first)
    winner = Empty;
    for(int r = 0; r < boardSize; r ++){ // initialize gameboard to be empty
        for(int c = 0; c < boardSize; c++){
          gameBoard[r][c] = Empty;
        }
    }

}

/* CLASS FUNCTIONS */

// To CHANGE a private data member from main, use SET function
// To READ a private data member from main, use GET function
int GameState::get_selectedRow(){
    return selectedRow;
}

int GameState::get_selectedColumn(){
    return selectedColumn;
}


// Set the selected row to value in the range (in the range 0..boardSize - 1)
// An out of range value is ignored and the function just returns
void GameState::set_selectedRow(int value){
    if(value <= boardSize-1){
        selectedRow = value;
    } else {
        return;
    }
}

// Set the selected column in the range (in the range 0..boardSize - 1)
// An out of range value is ignored and the function just returns
void GameState::set_selectedColumn(int value){
    if(value <= boardSize -1){
        selectedColumn = value;
    } else {
        return;
    }

}

// Get the moveValid value
bool GameState::get_moveValid(){
    return moveValid;
}

// Set the moveValid variable to value
void GameState::set_moveValid(bool value){
    moveValid = value;
    return;
}

// Get the gameOver value
bool GameState::get_gameOver(){
    return gameOver;
}

// Set the gameOver variable to value
void GameState::set_gameOver(bool value){
    gameOver = value;
    return;
}

// Get the value of turn
bool GameState::get_turn(){
    return turn;
}

// Set the value of turn
void GameState::set_turn(bool value){
    turn = value;
    return;
}

// Get the value of winner
int GameState::get_winner(){
    return winner;
}

// Set the value of winner;
void GameState::set_winner(int value){
    winner = value;
    return;
}

// Get the game board value at the board location at row and col
// This method checks that row, col and value are in range/valid
// and if not it returns Empty
int GameState::get_gameBoard(int row, int col){
    //Check if row and/or col is within board size
    if (row >= boardSize || row < 0 || col >= boardSize || col < 0) {
      return Empty;
      // If it is, get the game board value
    } else {
      return gameBoard[row][col];
    }
}

// Set the game board value at the board location at row and col to value
// This method checks that row, col and value are in range/valid and if not it
// just returns
void GameState::set_gameBoard(int row, int col, int value){
    if(row > boardSize - 1){
        return;
    } else if(col > boardSize - 1){
        return;
    } else if(gameBoard[row][col] != Empty){
        return;
    } else {
        gameBoard[row][col] = value;
        return;
    }
}
