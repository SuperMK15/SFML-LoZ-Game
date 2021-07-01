#ifndef ORB_H
#define ORB_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Orb {

    sf::RectangleShape orbSprite;

    sf::Texture* activatedTexture = new sf::Texture;
    sf::Texture* deactivatedTexture = new sf::Texture;

    bool orbActivated;

    sf::Clock orbTimer;


public:
    Orb(float, float, float = 100);

    void update(Player&, sf::RenderWindow&);

    bool isActivated();

    sf::RectangleShape getSprite();

};


#endif // ORB_H
