#include "Octorok.h"

void Octorok::updateOctorok(Player &player, float deltaTime) {

    if(player.getSprite().getGlobalBounds().intersects(detectionArea.getGlobalBounds())) {

        if(player.getSprite().getPosition().y < sprite.getPosition().y-20 && moveUp) {
            sprite.move(sf::Vector2f(0.0f, -octorokSpeed));
            detectionArea.move(sf::Vector2f(0.0f, -octorokSpeed));

            animation.update(3, deltaTime, 2);
            sprite.setTextureRect(animation.getTextureRect());

            if(!projectileVisible) {
                projectile.move(sf::Vector2f(0.0f, -octorokSpeed));
            }

        } else if(player.getSprite().getPosition().y > sprite.getPosition().y+20 && moveDown) {
            sprite.move(sf::Vector2f(0.0f, octorokSpeed));
            detectionArea.move(sf::Vector2f(0.0f, octorokSpeed));

            animation.update(0, deltaTime, 2);
            sprite.setTextureRect(animation.getTextureRect());

            if(!projectileVisible) {
                projectile.move(sf::Vector2f(0.0f, octorokSpeed));
            }

        } else if(!projectileVisible) {

            int shootRange = 500;

            if(player.getSprite().getPosition().x < sprite.getPosition().x-shootRange) {
                projectileSpeed = -2;
                projectileVisible = true;

                animation.update(4, deltaTime, 2);
                sprite.setTextureRect(animation.getTextureRect());

            } else if(player.getSprite().getPosition().x > sprite.getPosition().x+shootRange) {
                projectileSpeed = 2;
                projectileVisible = true;

                animation.update(5, deltaTime, 2);
                sprite.setTextureRect(animation.getTextureRect());

            } else if(player.getSprite().getPosition().x > sprite.getPosition().x-shootRange && player.getSprite().getPosition().x < sprite.getPosition().x) {
                sprite.move(sf::Vector2f(-octorokSpeed, 0.0f));

                animation.update(1, deltaTime, 2);
                sprite.setTextureRect(animation.getTextureRect());

                projectile.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
                detectionArea.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));

            } else if(player.getSprite().getPosition().x < sprite.getPosition().x+shootRange && player.getSprite().getPosition().x > sprite.getPosition().x) {
                sprite.move(sf::Vector2f(octorokSpeed, 0.0f));

                animation.update(2, deltaTime, 2);
                sprite.setTextureRect(animation.getTextureRect());

                projectile.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
                detectionArea.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
            }

        }

        float playerClockTime = player.getInvincibilityTimer().getElapsedTime().asSeconds();

        if(projectileVisible) {

            if(!projectile.getGlobalBounds().intersects(detectionArea.getGlobalBounds())) {
                projectileVisible = false;
                projectile.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
            } else if(projectile.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {

                if(playerClockTime >= 1) {
                    if(!player.isShieldRaised() || player.getShieldPower() == 0) {
                        player.decreaseHealth(projectileDamage);
                    } else {
                        player.decreaseShieldPower(projectileShieldDamage);
                    }
                    player.resetInvincibilityTimer();
                }

                projectileVisible = false;
                projectile.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
            }

            else {
                projectile.move(projectileSpeed, 0);
            }

        }

        if(sprite.getGlobalBounds().contains(player.getSprite().getPosition()) && playerClockTime >= 0.5) {
            player.decreaseHealth(collisionDamage);
            player.resetInvincibilityTimer();
        }

    } else {
        projectileVisible = false;
        projectile.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
    }

}


void Octorok::updateRemainingHealthAndInvincibility(Player &player) {

    timeElapsed = octorokInvincible.getElapsedTime().asSeconds();

    if(timeElapsed <= recoveryTime) {
        enemyFrozen = true;
    } else {
        enemyFrozen = false;
    }

    if(player.isAttacking() && player.getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && timeElapsed >= invincibleTime) {

        healthRemaining-=player.getSwordDamage();
        octorokInvincible.restart().asSeconds();

    }

    if(healthRemaining <= 0) {

        octorokAlive = false;

    }

    healthBarOutline.setPosition(sprite.getPosition().x-(healthBarSize/2), sprite.getPosition().y-70);
    healthBarOutline.setSize(sf::Vector2f(healthBarSize, 10));

    healthBar.setSize(sf::Vector2f(healthBarSize*(healthRemaining/maxHealth), 10));
    healthBar.setPosition(healthBarOutline.getPosition());

}


void Octorok::updateAllComponents(Player &player, float deltaTime) {

    if(!enemyFrozen) {
        updateOctorok(player, deltaTime);
    }

    updateRemainingHealthAndInvincibility(player);

}


Octorok::Octorok(int octorokType, float xPos, float yPos) {

    currentSpriteTextureX = 0;
    currentSpriteTextureY = 1;

    startingPos.x = xPos;
    startingPos.y = yPos;

    if(octorokType == 4) {

        projectileShieldDamage = 2;

        sprite.setSize(sf::Vector2f(200.0f, 200.0f));
        sprite.setOrigin(100, 100);
        sprite.setPosition(xPos, yPos);
        sprite.setFillColor(sf::Color(148, 0, 211));
        projectileRadius = 30;

        healthBarOutline.setSize(sf::Vector2f(160, 10));
        healthBarOutline.setPosition(xPos-(healthBarSize/2), yPos-70);
        healthBarOutline.setFillColor(sf::Color(139, 0, 0, 125));
        healthBarOutline.setOutlineColor(sf::Color(139, 0, 0));
        healthBarOutline.setOutlineThickness(5);

        healthBar.setSize(sf::Vector2f(90.0f, 10.0f));
        healthBar.setFillColor(sf::Color::Red);
        healthBar.setPosition(healthBarOutline.getPosition());

    } else {

        sprite.setSize(sf::Vector2f(100.0f, 100.0f));
        sprite.setOrigin(50, 50);
        sprite.setPosition(xPos, yPos);

        healthBarOutline.setSize(sf::Vector2f(90, 10));
        healthBarOutline.setPosition(xPos-45, yPos-70);
        healthBarOutline.setFillColor(sf::Color(139, 0, 0, 125));
        healthBarOutline.setOutlineColor(sf::Color(139, 0, 0));
        healthBarOutline.setOutlineThickness(5);

        healthBar.setSize(sf::Vector2f(90.0f, 10.0f));
        healthBar.setFillColor(sf::Color::Red);
        healthBar.setPosition(healthBarOutline.getPosition());

    }

    switch(octorokType) {

    case 1:
        octorokTexture->loadFromFile("images/RedOctorokSpriteSheet.png");
        animation = Animation(octorokTexture, sf::Vector2u(2, 6), 0.2f);

        healthBarSize = 80;
        maxHealth = 3;
        octorokSpeed = 0.25;
        invincibleTime = 1;
        recoveryTime = 0.5;
        projectileDamage = 0.5;
        collisionDamage = 0.25;
        break;

    case 2:
        octorokTexture->loadFromFile("images/YellowOctorokSpriteSheet.png");
        animation = Animation(octorokTexture, sf::Vector2u(2, 6), 0.15f);

        maxHealth = 6;
        octorokSpeed = 0.5;
        invincibleTime = 1.5;
        recoveryTime = 0.5;
        projectileDamage = 1;
        collisionDamage = 0.5;
        break;

    case 3:
        octorokTexture->loadFromFile("images/BlueOctorokSpriteSheet.png");
        animation = Animation(octorokTexture, sf::Vector2u(2, 6), 0.1f);

        maxHealth = 9;
        octorokSpeed = 0.75;
        invincibleTime = 2;
        recoveryTime = 0.5;
        projectileDamage = 2;
        collisionDamage = 1;
        break;

    case 4:
        octorokTexture->loadFromFile("images/BlueOctorokSpriteSheet.png");
        animation = Animation(octorokTexture, sf::Vector2u(2, 6), 0.1f);

        healthBarSize = 160;
        maxHealth = 18;
        octorokSpeed = 0.75;
        invincibleTime = 2;
        recoveryTime = 0.25;
        projectileDamage = 2;
        collisionDamage = 1;
        break;

    }

    healthRemaining = maxHealth;

    sprite.setTexture(octorokTexture);
    octorokTextureSize = octorokTexture->getSize();

    sprite.setTextureRect(sf::IntRect(octorokTextureSize.x*currentSpriteTextureX, octorokTextureSize.y*currentSpriteTextureY, octorokTextureSize.x, octorokTextureSize.y));

    detectionArea.setSize(sf::Vector2f(3000.0f, 3000.0f));
    detectionArea.setOrigin(1500, 1500);
    detectionArea.setPosition(xPos, yPos);

    projectileTexture->loadFromFile("images/OctorokRockTexture.png");
    projectile.setRadius(projectileRadius);
    projectile.setOrigin(projectile.getRadius(), projectile.getRadius());
    projectile.setTexture(projectileTexture);
    projectileTexture->setSmooth(true);
    projectile.setPosition(xPos, yPos);
    projectile.setFillColor(sf::Color::Green);

    moveUp = true;
    moveDown = true;
    moveRight = true;
    moveLeft = true;

}


void Octorok::updateAndDraw(sf::RenderWindow &window, Player &player, float deltaTime, bool changeSpeed, int scalar) {

    if(changeSpeed) {

        octorokSpeed*=scalar;

        if(projectileSpeed < 0) projectileSpeed = -2*scalar;
        if(projectileSpeed > 0) projectileSpeed = 2*scalar;

    }

    if(octorokAlive) {
        updateAllComponents(player, deltaTime);
        window.draw(sprite);
        window.draw(healthBarOutline);
        window.draw(healthBar);
    }
    if(projectileVisible) {
        window.draw(projectile);
    }

    if(changeSpeed) {

        octorokSpeed/=(double)scalar;

        if(projectileSpeed < 0) projectileSpeed = -20/(double)scalar;
        if(projectileSpeed > 0) projectileSpeed = 2/(double)scalar;

    }

}


void Octorok::revive() {

    healthRemaining = maxHealth;
    octorokAlive = true;

    sprite.setPosition(startingPos);
    detectionArea.setPosition(startingPos);
    projectile.setPosition(startingPos);

}


bool Octorok::isDead() {

    return (healthRemaining <= 0);

}


sf::RectangleShape Octorok::getSprite() { return sprite; }

sf::RectangleShape Octorok::getDetectionArea() {

    return detectionArea;

}
