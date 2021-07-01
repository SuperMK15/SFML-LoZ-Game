#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Moveables.h"

class Button {

    bool buttonPushed;

    sf::RectangleShape buttonSprite;

    sf::Texture *buttonPushedTexture = new sf::Texture;
    sf::Texture *buttonNotPushedTexture = new sf::Texture;

    float buttonSize;

public:
    Button(float, float, float);

    void updateButton(std::vector<Moveable>);

    bool isPressed();

    sf::RectangleShape getSprite();

};

#endif // BUTTON_H
