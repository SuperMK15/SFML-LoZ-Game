#ifndef OCTOROK_H
#define OCTOROK_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

class Octorok {

    sf::RectangleShape sprite;
    sf::RectangleShape detectionArea;
    sf::CircleShape projectile;

    sf::Texture *octorokTexture = new sf::Texture;
    sf::Texture *projectileTexture = new sf::Texture;

    Animation animation;

    sf::RectangleShape healthBarOutline;
    sf::RectangleShape healthBar;
    float healthBarSize = 90;

    sf::Vector2f startingPos;

    int currentSpriteTextureX;
    int currentSpriteTextureY;
    sf::Vector2u octorokTextureSize;

    float projectileDamage;
    float collisionDamage;

    float projectileShieldDamage = 1;

    bool octorokAlive = true;

    float timeElapsed;
    sf::Clock octorokInvincible;
    float invincibleTime;
    float recoveryTime;
    bool enemyFrozen = false;

    bool projectileVisible = false;
    float projectileSpeed = -2;
    float projectileRadius = 20;

    float maxHealth;
    float healthRemaining;

    bool moveUp = true, moveDown = true, moveRight = true, moveLeft = true;

    float octorokSpeed = 0.5;

private:

    void updateOctorok(Player&, float);

    void updateRemainingHealthAndInvincibility(Player&);

    void updateAllComponents(Player&, float);

public:

    Octorok(int, float, float);

    void updateAndDraw(sf::RenderWindow&, Player&, float, bool, int);

    void revive();

    bool isDead();

    sf::RectangleShape getSprite();

    sf::RectangleShape getDetectionArea();

};


#endif // OCTOROK_H
