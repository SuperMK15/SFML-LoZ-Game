#include "Button.h"

Button::Button(float xPos, float yPos, float SIZE) {

    buttonNotPushedTexture->loadFromFile("images/ButtonNotPushed.png");
    buttonPushedTexture->loadFromFile("images/ButtonPushed.png");

    buttonPushed = false;
    buttonSize = SIZE;

    buttonSprite.setSize(sf::Vector2f(buttonSize, buttonSize));
    buttonSprite.setPosition(sf::Vector2f(xPos, yPos));
    buttonSprite.setTexture(buttonNotPushedTexture);

}


void Button::updateButton(std::vector<Moveable> allMoveables) {

    buttonPushed = false;

    for(int i = 0; i < allMoveables.size(); i++) {

        if(buttonSprite.getGlobalBounds().contains(allMoveables[i].getSprite().getPosition().x+allMoveables[i].getSprite().getSize().x/2,
                allMoveables[i].getSprite().getPosition().y+allMoveables[i].getSprite().getSize().y/2)) {

            buttonPushed = true;

        }

    }

    if(buttonPushed) {
        buttonSprite.setTexture(buttonPushedTexture);
    } else {
        buttonSprite.setTexture(buttonNotPushedTexture);
    }


}


bool Button::isPressed() {
    return buttonPushed;
}


sf::RectangleShape Button::getSprite() { return buttonSprite; }
