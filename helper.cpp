#include "helper.hpp"

//This function places two integers to a coord struct and returns it
Coordinate mouseToCoord(int x, int y)
{
	Coordinate coord;

	coord.column = x;
	coord.row = y;

	return coord;
}

//This function initializes the board with the SEA character
void initBoard(char board[][10], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index] = SEA;
		}
	}
}

//For testing character board in console
void printBoard(char board[][10], int num_rows, int num_cols) 
{
	int row_index = 0, col_index = 0;
	putchar('\n');

	printf("%3d%2d%2d%2d%2d%2d%2d%2d%2d%2d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

	for (; row_index < num_rows; ++row_index)
	{
		printf("%d", row_index);
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			printf("%2c", board[row_index][col_index]);
		}

		putchar('\n');
	}
}

//This function generates a direction for a ship to be placed
Direction genDir(void)
{
	return (Direction)(rand() % 2);
}

//Generates a valid random start point based on the input of ship length and direction 
Coordinate genStartPt(int ship_length, Direction dir, int num_rows, int num_cols)
{
	Coordinate start_pt = { -1, -1 };

	if (dir == HORIZ)
	{
		start_pt.row = rand() % num_rows; // 0 - 9
		start_pt.column = rand() % (num_cols - ship_length + 1); // 0 - 9
	}
	else
	{
		start_pt.column = rand() % (num_rows - ship_length + 1); // 0 - 9
		start_pt.row = rand() % num_cols;  // 0 - 9
	}

	return start_pt;
}

//Places a ship on the board
// precondition: the placement has already been validated - no overlapping can happen
void placeShip(char board[][10], int num_rows, int num_cols, char symbol, int length,
	Direction dir, Coordinate start_pt)
{
	int count = 0;

	if (dir == VERT)
	{
		for (count = 0; count < length; ++count)
		{
			board[start_pt.row + count][start_pt.column] = symbol;
		}
	}
	else
	{
		for (count = 0; count < length; ++count)
		{
			board[start_pt.row][start_pt.column + count] = symbol;
		}
	}
}

//Takes inputs for where a ship is going to be placed and returns true if it can be placed there
//and returns false if it cannot be placed there due to overlap
bool validatePlacement(char board[][10], int length, Direction dir, Coordinate start_pt)
{

	if (dir == HORIZ)
	{
		if (start_pt.column+length>9)
		{
			return false;
		}
		for (int count_horiz = 0; count_horiz < length; count_horiz++)
		{
			if (board[start_pt.row][start_pt.column + count_horiz] != SEA)
			{
				return false;
			}
		}
	}
	else if (dir == VERT)
	{
		if (start_pt.row + length > 9) {
			return false;
		}
		for (int count_vert = 0; count_vert < length; count_vert++)
		{
			if (board[start_pt.row + count_vert][start_pt.column] != SEA)
			{
				return false;
			}
		}
	}
	else
	{
		return true;
	}
}

//Randomly places all ships on the board
void placeShipsRandomly(char board[][BOARD_COLS])
{
	int validation;
	Direction dir;
	Coordinate start_pt;
	//Place the Carrier
	do
	{
		dir = genDir();
		start_pt = genStartPt(CARRIER_LENGTH, dir, BOARD_ROWS, BOARD_COLS);
	} while (validatePlacement(board, CRUISER_LENGTH, dir, start_pt) == 0);
	placeShip(board, BOARD_ROWS, BOARD_COLS, CARRIER, CARRIER_LENGTH, dir, start_pt);

	//Place the Submarine
	do
	{
		dir = genDir();
		start_pt = genStartPt(SUBMARINE_LENGTH, dir, BOARD_ROWS, BOARD_COLS);
	} while (validatePlacement(board, CRUISER_LENGTH, dir, start_pt) == 0);
	placeShip(board, BOARD_ROWS, BOARD_COLS, SUBMARINE, SUBMARINE_LENGTH, dir, start_pt);

	//Place the Destroyer
	do
	{
		dir = genDir();
		start_pt = genStartPt(DESTROYER_LENGTH, dir, BOARD_ROWS, BOARD_COLS);
	} while (validatePlacement(board, CRUISER_LENGTH, dir, start_pt) == 0);
	placeShip(board, BOARD_ROWS, BOARD_COLS, DESTROYER, DESTROYER_LENGTH, dir, start_pt);

	//Place the Battleship
	do
	{
		dir = genDir();
		start_pt = genStartPt(BATTLESHIP_LENGTH, dir, BOARD_ROWS, BOARD_COLS);
	} while (validatePlacement(board, CRUISER_LENGTH, dir, start_pt) == 0);
	placeShip(board, BOARD_ROWS, BOARD_COLS, BATTLESHIP, BATTLESHIP_LENGTH, dir, start_pt);

	//Place the Cruiser
	do
	{
		dir = genDir();
		start_pt = genStartPt(CRUISER_LENGTH, dir, BOARD_ROWS, BOARD_COLS);
	} while (validatePlacement(board, CRUISER_LENGTH, dir, start_pt) == 0);
	placeShip(board, BOARD_ROWS, BOARD_COLS, CRUISER, CRUISER_LENGTH, dir, start_pt);
}

//Takes an attack coordinate and checks if it is a hit, miss, or needs to be redone
bool attackAndUpdate(char player_board[][BOARD_COLS], char board_copy[][BOARD_COLS], Coordinate attack, int* redo_ptr)
{
	bool hitOrMiss = false;

	if (board_copy[attack.column][attack.row] == HIT || board_copy[attack.column][attack.row] == MISS) 
	{
		*redo_ptr = 1;
		goto skip;
	}

	if (player_board[attack.column][attack.row] != SEA)
	{
		hitOrMiss = true;
		board_copy[attack.column][attack.row] = HIT;
	}
	else if (player_board[attack.column][attack.row] == SEA)
	{
		hitOrMiss = false;
		board_copy[attack.column][attack.row] = MISS;
	}

	*redo_ptr = 0;
	return hitOrMiss;
skip:;
}
//Generates a random attack coordinate on the board
Coordinate genAttackCoord(void)
{
	Coordinate attack;
	attack.row = rand() % BOARD_ROWS;
	attack.column = rand() % BOARD_COLS;
	return attack;
}

//Checks if there is a winner by seeing how many hits have been made on the entire board
int checkWinner(char player_board[][BOARD_COLS])
{
	int count = 0, win = 0;
	for (int i = 0; i < BOARD_COLS; i++)
	{
		for (int j = 0; j < BOARD_ROWS; j++)
		{
			if (player_board[j][i] == HIT)
			{
				count++;
			}
			if (count == 17) //17 is the sum of all ship lengths
			{
				win = 1;
			}
		}
	}
	return win;
}
