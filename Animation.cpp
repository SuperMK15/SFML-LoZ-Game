#include "Animation.h"

Animation::Animation() {}

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {

    this -> imageCount = imageCount;
    this -> switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);

}


void Animation::update(int row, float deltaTime, unsigned int maxIterations) {

    currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= maxIterations) {

            currentImage.x = 0;

        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;

}


void Animation::changeSwitchTime(float newSwitchTime) {

    switchTime = newSwitchTime;

}


float Animation::getSwitchTime() {

    return switchTime;

}


sf::IntRect Animation::getTextureRect() {

    return uvRect;

}
