#include "Fixed.h"

Fixed::Fixed(float xSize, float ySize, float xPos, float yPos, std::string filePath) {

    sprite.setSize(sf::Vector2f(xSize, ySize));
    sprite.setPosition(xPos, yPos);

    texture->loadFromFile(filePath);
    sprite.setTexture(texture);

}


sf::RectangleShape Fixed::getSprite() { return sprite; }
