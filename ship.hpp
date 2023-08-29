#pragma once
#include <SFML/Graphics.hpp>

#define CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define CRUISER_LENGTH 3
#define SUBMARINE_LENGTH 3
#define DESTROYER_LENGTH 2

#define BOARD_ROWS 10
#define BOARD_COLS 10

class Ship:public sf::Sprite {
public:

	//Constructors

	/*
	Constructor derived from Sprite()
	Makes basic ship with size 0 and type \0
	*/
	Ship();

	/*
	Constructor derived from Sprite()
	Makes basic ship with size newSize and type \0
	*/
	Ship(int newSize);

	//Destructor
	//virtual ~Ship();

	//Setter
	void setSize(int newSize);
	void setIntPosition(int n [][10]);
	void setHit(int x, int y);
	void setType(std::string type) {
		this->type = type;
	}

	//Bools
	bool checkPositionAlive(int x, int y);
	bool checkHit(int x, int y);
	bool isAlive();
		
	//Getter
	std::string getType() {
		return type;
	}
	int getSize() {
		return size;
	}

	/*
	Ship Copy Assignment Operator for copying or setting ships equal to eachother
	*/
	Ship& operator= (Ship& lhs);	
	
	/*
	Basically a setter for the ship's image texture
	*/
	void loadShipTexture(std::string str) {
		shipTexture.loadFromFile(str);
		this->setTexture(shipTexture);
	}


	
private:
	int size;
	std::string type;
	sf::Texture shipTexture;
};


