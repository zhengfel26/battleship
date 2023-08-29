#include "button.hpp"

Button::Button(sf::Vector2f size, sf::Color color) : sf::RectangleShape(size) {
	this->setFillColor(color);
}


void Button::setButtonPosition(int x, int y) {
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;
	this->setPosition(pos);

}

bool Button::isClicked(int mouseX, int mouseY) {
	int buttonXUpperBound = this->getPosition().x+this->getLocalBounds().width;
	int buttonYUpperBound = this->getPosition().y+this->getLocalBounds().height;
	int buttonXLowerBound = this->getPosition().x;
	int buttonYLowerBound = this->getPosition().y;
	if (mouseX<buttonXUpperBound && mouseX>buttonXLowerBound && mouseY > buttonYLowerBound && mouseY < buttonYUpperBound) {
		return true;
	}
	
	return false;
}

void Button::setButtonColor(sf::Color color) {
	this->setFillColor(color);
}


void Button::drawTo(sf::RenderWindow &window) {
	window.draw((Button) * this);
}

StartButton::StartButton() :Button({ 200,50 }, sf::Color::Red) {
}

BoardButton::BoardButton(int x, int y) : Button({50,50}, sf::Color::Transparent) {
	this->setPosition(x, y);
	this->setOutlineThickness(2);
	this->setOutlineColor(sf::Color::Black);
	type = '-';

}

BoardButton::BoardButton() : Button({ 50,50 }, sf::Color::Transparent) {
	this->setOutlineThickness(2);
	this->setOutlineColor(sf::Color::Black);
	type = '-';
}

/*DirectionButton::DirectionButton(int x, int y) : Button({200, 50}, sf::Color::Red) {
	this->setPosition(x, y);
	this->setOutlineThickness(2);
	this->setOutlineColor(sf::Color::Black);

	direction = HORIZ;
}

*/