#include "Orb.h"

Orb::Orb(float xPosition, float yPosition, float spriteSize) {

    activatedTexture->loadFromFile("images/OrbTrue.png");
    deactivatedTexture->loadFromFile("images/OrbFalse.png");

    orbSprite.setSize(sf::Vector2f(spriteSize, spriteSize));
    orbSprite.setOrigin(spriteSize/2, spriteSize/2);
    orbSprite.setPosition(xPosition, yPosition);

    orbActivated = false;

    orbTimer.restart().asSeconds();

}


void Orb::update(Player &player, sf::RenderWindow &window) {

    if(player.isAttacking() && orbSprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {

        if(orbTimer.getElapsedTime().asSeconds() >= 0.5) {

            orbActivated = !orbActivated;
            orbTimer.restart().asSeconds();

        }

    }

    if(orbActivated) {

        orbSprite.setTexture(activatedTexture);

    } else {

        orbSprite.setTexture(deactivatedTexture);

    }

}


bool Orb::isActivated() {

    return orbActivated;

}


sf::RectangleShape Orb::getSprite() {

    return orbSprite;

}
