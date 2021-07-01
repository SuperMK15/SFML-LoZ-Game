#include "Moveables.h"

Moveable::Moveable(float xPos, float yPos, float xSize, float ySize) {

    boulder.setSize(sf::Vector2f(xSize, ySize));
    boulder.setPosition(xPos, yPos);

    texture->loadFromFile("images/RockTexture.png");
    boulder.setTexture(texture);

}


std::string Moveable::checkInteractionForMove(Player player) {

    float playerX = player.getSprite().getPosition().x;
    float playerY = player.getSprite().getPosition().y;

    float objectXmin = boulder.getPosition().x;
    float objectYmin = boulder.getPosition().y;
    float objectXmax = objectXmin + boulder.getSize().x;
    float objectYmax = objectYmin + boulder.getSize().y;

    if(playerX >= objectXmin && playerX <= objectXmax) {

        if(playerY <= objectYmin && playerY >= objectYmin-15) {

            return "MOVE_DOWN";

        } else if(playerY >= objectYmax-player.getSprite().getSize().y && playerY <= objectYmax+15) {

            return "MOVE_UP";

        }

    } else if(playerY >= objectYmin && playerY <= objectYmax) {

        if(playerX >= objectXmax && playerX <= objectXmax+15) {

            return "MOVE_LEFT";

        } else if(playerX <= objectXmin && playerX >= objectXmin-15) {

            return "MOVE_RIGHT";

        }

    }

    return "NOTHING";

}


sf::RectangleShape Moveable::getSprite() { return boulder; }



bool Moveable::checkUpMovement(std::vector <Fixed> shapesToCheck) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if(boulder.getPosition().x >= shapesToCheck[i].getSprite().getPosition().x && boulder.getPosition().x <= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x)) {

            if(boulder.getPosition().y <= (shapesToCheck[i].getSprite().getSize().y+shapesToCheck[i].getSprite().getPosition().y) && boulder.getPosition().y >= (shapesToCheck[i].getSprite().getSize().y+shapesToCheck[i].getSprite().getPosition().y)-30) {
                return false;
            }

        }

    }

    return true;

}

bool Moveable::checkDownMovement(std::vector<Fixed> shapesToCheck, int xOffset, int yOffset) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if((boulder.getPosition().x+xOffset) >= shapesToCheck[i].getSprite().getPosition().x && (boulder.getPosition().x+xOffset) <= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x)) {

            if((boulder.getPosition().y+yOffset) >= shapesToCheck[i].getSprite().getPosition().y-30 && (boulder.getPosition().y+yOffset) <= shapesToCheck[i].getSprite().getPosition().y) {
                return false;
            }

        }

    }

    return true;

}

bool Moveable::checkLeftMovement(std::vector<Fixed> shapesToCheck) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if(boulder.getPosition().y >= shapesToCheck[i].getSprite().getPosition().y && boulder.getPosition().y <= (shapesToCheck[i].getSprite().getPosition().y+shapesToCheck[i].getSprite().getSize().y)) {

            if(boulder.getPosition().x >= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x) && boulder.getPosition().x <= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x)+30) {
                return false;
            }

        }

    }

    return true;

}

bool Moveable::checkRightMovement(std::vector<Fixed> shapesToCheck, int xOffset, int yOffset) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if((boulder.getPosition().y+yOffset) >= shapesToCheck[i].getSprite().getPosition().y && (boulder.getPosition().y+yOffset) <= (shapesToCheck[i].getSprite().getPosition().y+shapesToCheck[i].getSprite().getSize().y)) {

            if((boulder.getPosition().x+xOffset) <= shapesToCheck[i].getSprite().getPosition().x && (boulder.getPosition().x+xOffset) >= shapesToCheck[i].getSprite().getPosition().x-30) {
                return false;
            }

        }

    }

    return true;

}


void Moveable::moveBoulder(float x, float y) {

    boulder.move(x, y);

}



std::string Moveable::checkVerticalCollisionForArray(std::vector<Moveable> allMoveables, sf::RectangleShape object, int indexToSkip) {

    float objectXMin = (object.getPosition().x);
    float objectXMax = (object.getPosition().x+object.getSize().x);

    float objectY = (object.getPosition().y+(object.getSize().y/2));

    for(int i = 0; i < allMoveables.size(); i++) {

        float moveableXMin = allMoveables[i].getSprite().getPosition().x;
        float moveableXMax = allMoveables[i].getSprite().getPosition().x+allMoveables[i].getSprite().getSize().x;
        float moveableYMin = allMoveables[i].getSprite().getPosition().y;
        float moveableYMax = allMoveables[i].getSprite().getPosition().y+allMoveables[i].getSprite().getSize().y;

        if(object.getGlobalBounds().intersects(allMoveables[i].getSprite().getGlobalBounds()) && i != indexToSkip) {

            if(objectXMax >= moveableXMin && objectXMin <= moveableXMax) {

                if(objectY <= moveableYMin) {
                    return "TOP";
                } else if(objectY >= moveableYMax) {
                    return "BOTTOM";
                }

            }

        }

    }

    return "NOTHING";


}

std::string Moveable::checkHorizontalCollisionForArray(std::vector<Moveable> allMoveables, sf::RectangleShape object, int indexToSkip) {

    float objectYMin = (object.getPosition().y);
    float objectYMax = (object.getPosition().y+object.getSize().y);

    float objectX = (object.getPosition().x+(object.getSize().x/2));

    for(int i = 0; i < allMoveables.size(); i++) {

        float moveableXMin = allMoveables[i].getSprite().getPosition().x;
        float moveableXMax = allMoveables[i].getSprite().getPosition().x+allMoveables[i].getSprite().getSize().x;
        float moveableYMin = allMoveables[i].getSprite().getPosition().y;
        float moveableYMax = allMoveables[i].getSprite().getPosition().y+allMoveables[i].getSprite().getSize().y;

        if(object.getGlobalBounds().intersects(allMoveables[i].getSprite().getGlobalBounds()) && i != indexToSkip) {

            if(objectYMax >= moveableYMin && objectYMin <= moveableYMax) {

                if(objectX <= moveableXMin) {
                    return "LEFT";
                } else if(objectX >= moveableXMax) {
                    return "RIGHT";
                }

            }

        }

    }

    return "NOTHING";


}
