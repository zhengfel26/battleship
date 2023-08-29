#include <SFML/Graphics.hpp>

//User to make Marker objects to contain a sprite of an X hit marker or a water spalsh miss marker
class Marker:public sf::Sprite {
public:
	Marker() :sf::Sprite() {}
	Marker& operator= (Marker& lhs);

private:
	sf::Texture texture;
};

