#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Fixed.h"

class Player {

    sf::RectangleShape sprite;
    sf::Texture texture;
    sf::Vector2u textureSize;

    Animation animation;

    int idlePosX = 0;
    int idlePosY = 0;

    float playerSpeed = 10;

    float maxHealth = 5;
    float currentHealth = maxHealth;
    sf::Clock invinciblityTimer;
    sf::RectangleShape healthBarOutline;
    sf::RectangleShape healthBar;

    sf::RectangleShape staminaBarOutline;
    sf::RectangleShape staminaBar;
    double staminaRecoveryRate;
    const float staminaRechargeTime = 4;
    float maxStamina = 4.0f;
    float currentStamina = maxStamina;

    sf::Clock staminaUpdateClock;
    sf::Clock staminaRecoveryClock;
    sf::Clock sprintingClock;
    sf::Clock pushingClock;

    bool pushing;
    bool sprinting;
    bool attacking;
    bool staminaDepleted;

    bool up, down, left, right;
    bool blockedByInteractable;

    bool hasSword = false;
    bool firstTime;
    float swordDamage = 1;

    sf::CircleShape shieldBarrier;
    bool hasShield = false;
    bool shieldRaised;
    bool shieldDepleted = false;
    float shieldPowerMax = 4;
    float shieldPower = 4;

    sf::RectangleShape shieldBarOutline;
    sf::RectangleShape shieldBar;
    sf::Clock shieldRechargeTimer;

    bool checkUpMovement(std::vector<Fixed>);

    bool checkDownMovement(std::vector<Fixed>);

    bool checkRightMovement(std::vector<Fixed>);

    bool checkLeftMovement(std::vector<Fixed>);


public:
    Player();

    void draw(sf::RenderWindow&);

    sf::RectangleShape getSprite();
    float getPlayerSpeed();

    bool getUp();
    bool getDown();
    bool getRight();
    bool getLeft();

    bool getBlocked();
    void setBlocked(bool);

    void moveUp(float);
    void moveDown(float);
    void moveLeft(float);
    void moveRight(float);

    void idle();

    void revive();
    bool isDead();

    void checkAllMovementDirections(std::vector<Fixed>);

    void setPosition(float, float);

    void reset(int);

    void isPushing();

    void updateSword();
    void updateShield();

    void updateHealthBar(sf::View, float, float);

    void updateStaminaBar(int);

    void updateShieldBar();

    bool isAttacking();

    bool isShieldRaised();

    float getShieldPower();

    void decreaseHealth(float);

    void decreaseShieldPower(float);

    void giveSword();
    void giveShield();

    float getSwordDamage();
    void setSwordDamage(float);

    void resetInvincibilityTimer();

    sf::Clock getInvincibilityTimer();

    bool isStaminaDepleted();

    void setSprinting(bool);

    void refreshStamina();
    void refreshShieldPower();

    void addStaminaVessel();
    void addHeartContainer();

};

#endif // PLAYER_H
