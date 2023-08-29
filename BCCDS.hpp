#include "Ship.hpp"

// Carrier
class Carrier : public Ship
{
public:
	Carrier();

	~Carrier();

};

//Battleship
class Battleship : public Ship
{
public:
	Battleship();

	~Battleship();
};

//Cruiser
class Cruiser : public Ship
{
public:

	Cruiser();

	~Cruiser();
};

// Submarine
class Submarine : public Ship
{
public:
	Submarine();

	~Submarine();
};

// Destroyer
class Destroyer : public Ship
{
public:
	Destroyer();

	~Destroyer();
};

