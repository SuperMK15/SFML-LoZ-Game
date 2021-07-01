#ifndef FIXED_H
#define FIXED_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Fixed {

    sf::RectangleShape sprite;
    sf::Texture *texture = new sf::Texture;

public:
    Fixed(float, float, float, float, std::string);

    sf::RectangleShape getSprite();

};

#endif // FIXED_H
