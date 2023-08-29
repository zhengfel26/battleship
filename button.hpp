#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>

class Button:public sf::RectangleShape {
public:
	Button() {}

	Button(sf::Vector2f size, sf::Color color);

	void setButtonPosition(int x, int y);
	
	void setButtonColor(sf::Color color);

	void drawTo(sf::RenderWindow &window);

	bool isClicked(int mouseX, int mouseY);

private:
	
};

class StartButton :public Button {

public:
	StartButton();
	
private:

};

class BoardButton : public Button {

public:
	BoardButton(int x, int y);
	BoardButton();

	void setType(char c) {
		type = c;
	}

	char getType() {
		return type;
	}
private:
	char type;
};

/*class DirectionButton : public Button {
public:
	DirectionButton(int x, int y);
	
	void setDirection(Direction dir) { 
		direction = dir; 
	}
	Direction getDirection() { 
		return direction; 
	}

private:
	Direction direction;
};*/