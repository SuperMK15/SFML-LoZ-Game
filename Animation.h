#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

    sf::IntRect uvRect;

public:

    Animation(sf::Texture*, sf::Vector2u, float);
    Animation();

    void update(int, float, unsigned int);

    void changeSwitchTime(float);

    float getSwitchTime();

    sf::IntRect getTextureRect();

};


#endif // ANIMATION_H
