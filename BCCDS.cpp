#include "BCCDS.hpp"

Carrier::Carrier() : Ship(CARRIER_LENGTH) {
//Sprite building
	loadShipTexture("Carrier.png");
	this->setType("Carrier");
}
Carrier::~Carrier() {}

Battleship::Battleship() : Ship(BATTLESHIP_LENGTH) {
	loadShipTexture("Battleship.png");
	this->setType("Battleship");
}
Battleship::~Battleship() {

}

Cruiser::Cruiser() : Ship(CRUISER_LENGTH) {
	loadShipTexture("Cruiser.png");
	this->setType("Cruiser");
}
Cruiser::~Cruiser() {}

Submarine::Submarine() : Ship(SUBMARINE_LENGTH) {
	loadShipTexture("Submarine.png");
	this->setType("Submarine");
}
Submarine::~Submarine() {}

Destroyer::Destroyer() : Ship(DESTROYER_LENGTH) {
	loadShipTexture("Destroyer.png");
	this->setType("Destroyer");
}
Destroyer::~Destroyer() {}
