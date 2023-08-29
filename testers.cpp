#include "testers.hpp"




void TestCase1()
{
	//Tests the character placeShip Function by placing the carrier horizontally at 2,2

	int carrierCount = 0;
	char testBoard[10][10];
	initBoard(testBoard, 10, 10);

	Coordinate StartPoint = { 2, 2 };
	Direction Dir = HORIZ;

	placeShip(testBoard, 10, 10, CARRIER, CARRIER_LENGTH, Dir, StartPoint);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (testBoard[i][j] == CARRIER)
			{
				carrierCount++;
			}
		}
	}

	if (carrierCount == CARRIER_LENGTH)
	{
		cout << "Test Case 1 Passed" << endl
			 << "\t\"placeShip()\" functions correctly" << endl;
	}
	else
	{
		cout << "Test Case 1 Failed" << endl;
	}
}





void TestCase2()
{
	//Tests the validatePlacement function by placing two ships on top of eachother


	int valid = -1;
	char testBoard[10][10];
	initBoard(testBoard, 10, 10);

	Coordinate StartPoint = { 5, 5 };
	Direction Dir = VERT;

	//Places a sbmarine at 3,3 vertically
	placeShip(testBoard, 10, 10, SUBMARINE, SUBMARINE_LENGTH, Dir, StartPoint);

	//Checks if you can place a destroyer at 3,3 vertically
	valid = validatePlacement(testBoard, DESTROYER_LENGTH, Dir, StartPoint);
	if (valid == 0)
	{
		cout << "Test Case 2 Passed" << endl
			<< "\tvalidatePlacement() function successful" << endl;
	}
	else
	{
		cout << "Test Case 2 Failed" << endl;

	}
}

//Tests converting Vecror2f points to Coordinate struct points
void TestCase3()
{
	

	Coordinate coord = { 0,0 };
	sf::Vector2f d{ 100,25 };

	coord = mouseToCoord(d.x, d.y);

	if (coord.column == d.x && coord.row == d.y)
	{
		cout << "Test Case 3 Passed" << endl
			<< "\tValid x Conversion & Valid y Conversion" << endl;
	}
	else
	{
		cout << "Test Case 3 Failed" << endl;
	}
}


// Tests randomizeShips function by creating a test board and then randomizing it
// After ships randomized, nested loop counts alphabetic characters
// If there are 17 (5+4+3+3+2) then the randomize function works properly
void TestCase4()
{
	char testBoard[10][10];
	int alphaCount = 0;
	initBoard(testBoard, 10, 10);
	placeShipsRandomly(testBoard);

	for (int i = 0; i < 10; i++)
	{
		for (int a = 0; a < 10; a++)
		{
			if (isalpha(testBoard[i][a]))
			{
				alphaCount++;
			}
		}
	}

	if (alphaCount == 17)
	{
		cout << "Test Case 4 Passed" << endl << "\t\"randomizeShips()\" places ships randomly with no overlap" << endl;
	}
	else
	{
		cout << "Test Case 4 Failed" << endl;
	}

}

/*
Checks if attackAndUpdate fucntion processes hit/miss corectly
*/
void TestCase5()
{
	Coordinate coord = { 5,5 };
	char board[10][10];
	char boardCopy[10][10];
	int* redo = new int(1);
	initBoard(board, 10, 10);
	initBoard(boardCopy,10,10);

	attackAndUpdate(board, board, coord, redo);

	if(board[coord.column][coord.row] == MISS)
	{
		cout << "Test Case 5 Passed" << endl
			<< "\t\"attackAndUpdate()\" processes attacks and checks for hit or miss" << endl;
	}
	else
	{
		cout << "Test Case 5 Failed" << endl;
	}
}

//Runs all the test cases in main before App.runGame() is called
void runSuite() 
{
	TestCase1();
	TestCase2();
	TestCase3();
	TestCase4();
	TestCase5();
}