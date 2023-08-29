#include "markers.hpp"

//Overloaded assignment operator for Marker class	
Marker& Marker::operator= (Marker& lhs) {
	texture = *lhs.getTexture();
	this->setTexture(texture);
	this->setPosition(lhs.getPosition());

	return *this;

}