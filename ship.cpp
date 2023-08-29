#include "ship.hpp"

/*
Constructor derived from Sprite()
Makes basic ship with size 0 and type \0
*/
Ship::Ship() :sf::Sprite()
{
	size = 0;
	/*for (int i = 0; i < 10; i++)
	{
		for(int a = 0; a < 10; a++)
		{
			positionAlive[i][a] = 0;
			positionHit[i][a] = 0;
		}
	}*/

	type = "\0";
}

/*
Constructor derived from Sprite()
Makes basic ship with size newSize and type \0
*/
Ship::Ship(int newSize) :sf::Sprite()
{
	size = newSize;
	/*for (int i = 0; i < 10; i++)
	{
		for (int a = 0; a < 10; a++)
		{
			positionAlive[i][a] = 0;
			positionHit[i][a] = 0;
		}
	}*/

	type = "\0";
}

/*
Ship Copy Assignment Operator for copying or setting ships equal to eachother
*/
Ship& Ship::operator= (Ship& lhs) {
	//Sprite copying
	this->setTexture(*lhs.getTexture());
	this->setPosition(lhs.getPosition());
	//Other sprite values assumed to be the same
	//Other copying
	this->setType(lhs.getType());

	return *this;
}