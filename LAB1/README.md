This lab is the classic connect four game coded using C++. 
It is a best-of-3 game of Connect Four - meaning that one player needs to win 2 individual games of Connect Four to win the match. Players do not switch sides/colours
after each round and draws are not considered. The class GameState is defined in GameState.h and outlines the environment for the game: the board, variables the player
would input like the row and column for the move to be played, and boolean variables like moveValid, gameOver, and turn.

The function playMove() in playMove.cpp is called each time a player makes a move. It updates the GameState object passed by reference to the function. 
It updates all the boolean variables: gameOver, turn, and winner. 

The game controller is defined in the main() function in connectfour.cpp. It creates and initializes 3 game boards, and interacts with the players directly. 
It prints the boards after each move and announces the winner, if there is one.