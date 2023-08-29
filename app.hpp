#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "ship.hpp"
#include <iostream>//for testing purposes only
#include <random>
#include "helper.hpp"
#include "BCCDS.hpp"
#include "markers.hpp"

struct Board {
    char charGameBoard[10][10]; //used to keep track of game on the back end
    BoardButton buttonGameBoard[10][10];//used to display visuals
};
class App {
public:
    App();
    //Main run game function
    void runGame();
    ~App() {
        for (int i = 0; i < 5; i++) {
            delete ships[i];
        }
    }
    

private:
    //Private member data
    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture backGroundTexture;
    sf::Font font;
    Ship* ships[5];
    sf::Text LHStext;
    sf::Text RHStext;
    sf::Text boatCollectionText[5];
    sf::Sprite boatCollection;
    sf::Texture boatCollectionTex;
    bool isPlaced[5];//Order of ships in array is Battleship,Cruiser,Submarine,Destroyer,Carrier
    //Draw hit and misses
    Marker hitMissCollection[200];
    int hitMissSum;
    int playerHitCount;
    int enemyHitCount;

    sf::Sprite winBackground;
    sf::Sprite lossBackground;
    sf::Texture winTex;
    sf::Texture lossTex;

    Board playerBoard;

    Board enemyBoard;

    //Private member functions
    //Returns the mouse position relative to a given window via two integer values
    void getClickPosition(int& x, int& y, sf::RenderWindow &window);

    //Runs loop to display startMenu until play is clicked or window is closed
    void runStartMenu();

    
    //Makes text to make title ready to be drawn
    void buildTitle(sf::Text& text, int x, int y);

    //Used to create board grid
    void buildBoard(BoardButton board[][10], int startX, int startY);

    //Used to draw board
    void drawBoard(sf::RenderWindow& window, BoardButton board[][10]);

    //Used to return the corresponding column and row of the box that got clicked
    void getClickPos(BoardButton board[][10], sf::Vector2f clickPos, int& x, int &y);

    //Sets up startMenu text label for boats
    void setBoatCollectionText(sf::Text textCollection[]);

    void drawBoatCollectionText(sf::Text textCollection[], sf::RenderWindow& window);

    void directionSelection();

    //Used to place ship on both the boards for the character and the visual display
    void placeShipPack(Ship &ship, Board &board, sf::RenderWindow& window, Coordinate coord, Direction dir);

    //Place a hit on both the character and visual display boards
    void placeHit(Board &board, int x, int y);
    
    //Place a hit on both the character and visual display boards
    void placeMiss(Board &board, int x, int y);

    //NOT IN USE
    void createWarning();

    //Gets user input to place one ship
    void getUserBoatPlacement(Board &board, Ship &ship);

    //Peeks the character board and returns a character representative of what is on the board
    char checkHit(Board &board, int x, int y);

    //Suite package that gets user input for all the ship placements
    void putShipsDown();

    void initShips();
  
    void drawShips();

    void initBoolPlacement();

    // Enemy Bot functions
	void generateEnemyBoard();
    //Simulates one round being run for the enemy bot
    //Called in response to a valid user round
	void simulateBotRound();
	bool playerRound(Coordinate coord);

    void drawMarkers();
    
    void drawWin();

    void drawLoss();


};