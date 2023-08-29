#pragma once
#include "app.hpp"
using std::cout;
using std::endl;


/*
Tests the place ship function by placing a carrier on the baord
*/
void TestCase1(); 

/*
//Tests the validatePlacement function by testing placing two ships on top of eachother
*/
void TestCase2(); 

/*
//Tests converting Vecror2f points to Coordinate struct points
*/
void TestCase3();


/*
 Tests randomizeShips function by creating a test board and then randomizing it
After ships randomized, nested loop counts alphabetic characters
If there are 17 (5+4+3+3+2) then the randomize function works properly
*/
void TestCase4();

/*
Checks if attackAndUpdate fucntion processes hit/miss corectly
*/
void TestCase5();

/*
Runs all the test cases in main before App.runGame() is called
*/
void runSuite();


