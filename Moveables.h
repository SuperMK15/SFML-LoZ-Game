#ifndef MOVEABLES_H
#define MOVEABLES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Fixed.h"

class Moveable {

    sf::RectangleShape boulder;
    sf::Texture *texture = new sf::Texture;

public:
    Moveable(float, float, float = 200, float = 130);

    std::string checkInteractionForMove(Player);

    bool checkUpMovement(std::vector <Fixed>);
    bool checkDownMovement(std::vector <Fixed>, int, int);
    bool checkRightMovement(std::vector <Fixed>, int, int);
    bool checkLeftMovement(std::vector <Fixed>);

    sf::RectangleShape getSprite();

    void moveBoulder(float, float);

    static std::string checkVerticalCollisionForArray(std::vector<Moveable>, sf::RectangleShape, int = -1);

    static std::string checkHorizontalCollisionForArray(std::vector<Moveable>, sf::RectangleShape, int = -1);

};

#endif // MOVEABLES_H
