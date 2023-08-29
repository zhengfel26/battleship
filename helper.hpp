#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <random>

enum Direction {
	HORIZ, VERT
};

struct Coordinate {
	int row;
	int column;
};

//Not in use
//Used to randomly generate a shot that hasn't already been taken for the bot
//void generateShot(int* x, int* y, char board[][10]);
//void randomizeShips(char board[][10]);

#define BOARD_ROWS 10
#define BOARD_COLS 10

#define SEA        '-'
#define HIT        'X'
#define MISS       'O'

#define CARRIER    'C'
#define BATTLESHIP 'B'
#define CRUISER    'c'
#define SUBMARINE  'S'
#define DESTROYER  'D'

#define CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define CRUISER_LENGTH 3
#define SUBMARINE_LENGTH 3
#define DESTROYER_LENGTH 2

//This function initializes the board with the SEA character
void initBoard(char board[][10], int num_rows, int num_cols); 


//For testing character board in console
void printBoard(char board[][10], int num_rows, int num_cols); 


//This function generates a direction for a ship to be placed
Direction genDir(void); 


//Generates a valid random start point based on the input of ship length and direction 
Coordinate genStartPt(int ship_length, Direction dir, int num_rows, int num_cols);


//Generates a random attack coordinate on the board
Coordinate genAttackCoord(void);


//Takes inputs for where a ship is going to be placed and returns true if it can be placed there
//and returns false if it cannot be placed there due to overlap
bool validatePlacement(char board[][10], int length, Direction dir, Coordinate start_pt); //Optimize


//Places a ship on the board
// precondition: the placement has already been validated - no overlapping can happen
void placeShip(char board[][10], int num_rows, int num_cols, char symbol, int length, //Places a ship on a board
	Direction dir, Coordinate start_pt);


//Places all the ships randomly on the board
void placeShipsRandomly(char board[][BOARD_COLS]);


//Takes an attack coordinate and checks if it is a hit, miss, or needs to be redone
bool attackAndUpdate(char player_board[][BOARD_COLS], char board_copy[][BOARD_COLS], Coordinate attack, int* redo); //Checks if a ship is hit on the board and updates the board


//Checks if there is a winner by seeing how many hits have been made on the entire board
int checkWinner(char player_board[][BOARD_COLS]); 


//This function places two integers to a coord struct and returns it
Coordinate mouseToCoord(int x, int y);