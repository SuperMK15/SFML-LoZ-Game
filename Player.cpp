#include "Player.h"

Player::Player() {

    sprite.setSize(sf::Vector2f(120, 120));
    sprite.setOrigin(sf::Vector2f(60.0f, 60.0f));
    sprite.setPosition(500, 500);

    texture.loadFromFile("images/LinkFullSheet.png");
    sprite.setTexture(&texture);

    animation = Animation(&texture, sf::Vector2u(2, 6), 0.2f);

    textureSize = texture.getSize();
    textureSize.x /= 2;
    textureSize.y /= 6;

    sprite.setTextureRect(sf::IntRect(textureSize.x*0, textureSize.y*0, textureSize.x, textureSize.y));


    shieldBarrier.setRadius(45.0f);
    shieldBarrier.setOrigin(sf::Vector2f(45.0f, 45.0f));
    shieldBarrier.setPosition(200.0f, 200.0f);
    shieldBarrier.setFillColor(sf::Color(255, 255, 255, 0));
    shieldBarrier.setOutlineThickness(2.5f);
    shieldBarrier.setOutlineColor(sf::Color::Blue);


    healthBarOutline.setSize(sf::Vector2f(200.0f, 20.0f));
    healthBarOutline.setFillColor(sf::Color(139, 0, 0, 125));
    healthBarOutline.setOutlineColor(sf::Color(139, 0, 0));
    healthBarOutline.setOutlineThickness(5);

    healthBar.setSize(sf::Vector2f(200.0f, 20.0f));
    healthBar.setFillColor(sf::Color::Red);



    staminaBarOutline.setSize(sf::Vector2f(200.0f, 20.0f));
    staminaBarOutline.setFillColor(sf::Color(0, 139, 0, 125));
    staminaBarOutline.setOutlineColor(sf::Color(0, 139, 0));
    staminaBarOutline.setOutlineThickness(5);

    staminaBar.setSize(sf::Vector2f(200.0f, 20.0f));
    staminaBar.setFillColor(sf::Color::Green);


    shieldBarOutline.setSize(sf::Vector2f(200.0f, 20.0f));
    shieldBarOutline.setFillColor(sf::Color(0, 0, 139, 125));
    shieldBarOutline.setOutlineColor(sf::Color(0, 0, 139));
    shieldBarOutline.setOutlineThickness(5);

    shieldBar.setSize(sf::Vector2f(200.0f, 20.0f));
    shieldBar.setFillColor(sf::Color::Blue);

}


void Player::draw(sf::RenderWindow &window) {

    window.draw(sprite);

    if(shieldRaised) window.draw(shieldBarrier);

    window.draw(healthBar);
    window.draw(healthBarOutline);

    window.draw(staminaBarOutline);
    window.draw(staminaBar);

    if(hasShield) {

        window.draw(shieldBarOutline);
        window.draw(shieldBar);

    }

}


sf::RectangleShape Player::getSprite() {
    return sprite;
}

float Player::getPlayerSpeed() {
    return playerSpeed;
}


bool Player::getUp() {
    return up;
}

bool Player::getDown() {
    return down;
}

bool Player::getRight() {
    return right;
}

bool Player::getLeft() {
    return left;
}


void Player::moveUp(float deltaTime) {

    idlePosX = 0;
    idlePosY = 2;

    sprite.move(0.0f, -playerSpeed);
    animation.update(2, deltaTime, 2);
    sprite.setTextureRect(animation.getTextureRect());

}

void Player::moveDown(float deltaTime) {

    idlePosX = 0;
    idlePosY = 0;

    sprite.move(0.0f, playerSpeed);
    animation.update(0, deltaTime, 2);
    sprite.setTextureRect(animation.getTextureRect());

}

void Player::moveLeft(float deltaTime) {

    idlePosX = 0;
    idlePosY = 1;

    sprite.move(-playerSpeed, 0.0f);
    animation.update(1, deltaTime, 2);
    sprite.setTextureRect(animation.getTextureRect());

}

void Player::moveRight(float deltaTime) {

    idlePosX = 1;
    idlePosY = 3;

    sprite.move(playerSpeed, 0.0f);
    animation.update(3, deltaTime, 2);
    sprite.setTextureRect(animation.getTextureRect());

}

void Player::idle() {

    sprite.setTextureRect(sf::IntRect(textureSize.x*idlePosX, textureSize.y*idlePosY, textureSize.x, textureSize.y));

    firstTime = true;
    sprinting = false;
    staminaRecoveryRate*=2;

}


void Player::revive() {

    currentHealth = maxHealth;
    currentStamina = maxStamina;
    shieldPower = shieldPowerMax;

}

bool Player::isDead() {

    return (currentHealth <= 0);

}


bool Player::checkUpMovement(std::vector<Fixed> shapesToCheck) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if(sprite.getPosition().x >= shapesToCheck[i].getSprite().getPosition().x && sprite.getPosition().x <= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x)) {

            if(sprite.getPosition().y <= (shapesToCheck[i].getSprite().getSize().y+shapesToCheck[i].getSprite().getPosition().y) && sprite.getPosition().y >= (shapesToCheck[i].getSprite().getSize().y+shapesToCheck[i].getSprite().getPosition().y)-30) {
                return false;
            }

        }

    }

    return true;


}

bool Player::checkDownMovement(std::vector<Fixed> shapesToCheck) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if((sprite.getPosition().x) >= shapesToCheck[i].getSprite().getPosition().x && (sprite.getPosition().x) <= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x)) {

            if((sprite.getPosition().y) >= shapesToCheck[i].getSprite().getPosition().y-30 && (sprite.getPosition().y) <= shapesToCheck[i].getSprite().getPosition().y) {
                return false;
            }

        }

    }

    return true;

}

bool Player::checkRightMovement(std::vector<Fixed> shapesToCheck) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if((sprite.getPosition().y) >= shapesToCheck[i].getSprite().getPosition().y && (sprite.getPosition().y) <= (shapesToCheck[i].getSprite().getPosition().y+shapesToCheck[i].getSprite().getSize().y)) {

            if((sprite.getPosition().x) <= shapesToCheck[i].getSprite().getPosition().x && (sprite.getPosition().x) >= shapesToCheck[i].getSprite().getPosition().x-30) {
                return false;
            }

        }

    }

    return true;

}

bool Player::checkLeftMovement(std::vector<Fixed> shapesToCheck) {

    for(int i = 0; i < shapesToCheck.size(); i++) {

        if(sprite.getPosition().y >= shapesToCheck[i].getSprite().getPosition().y && sprite.getPosition().y <= (shapesToCheck[i].getSprite().getPosition().y+shapesToCheck[i].getSprite().getSize().y)) {

            if(sprite.getPosition().x >= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x) && sprite.getPosition().x <= (shapesToCheck[i].getSprite().getPosition().x+shapesToCheck[i].getSprite().getSize().x)+30) {
                return false;
            }

        }

    }

    return true;

}

void Player::checkAllMovementDirections(std::vector<Fixed> shapesToCheck) {

    up = checkUpMovement(shapesToCheck);
    down = checkDownMovement(shapesToCheck);
    right = checkRightMovement(shapesToCheck);
    left = checkLeftMovement(shapesToCheck);

}


void Player::setPosition(float xPos, float yPos) {

    sprite.setPosition(xPos, yPos);

}


bool Player::getBlocked() {
    return blockedByInteractable;
}

void Player::setBlocked(bool b) {
    blockedByInteractable = b;
}


void Player::reset(int scalar) {

    playerSpeed = 1*scalar;
    animation.changeSwitchTime(0.2f);

    blockedByInteractable = false;
    pushing = false;
    sprinting = false;
    attacking = false;

    staminaRecoveryRate = 0.01/(staminaRechargeTime/maxStamina);


}


void Player::isPushing() {

    pushing = true;
    playerSpeed /= 2;
    animation.changeSwitchTime(animation.getSwitchTime()*2);

}


void Player::updateSword() {

    staminaRecoveryClock.restart().asSeconds();

    if(hasSword) {

        attacking = true;

        switch(idlePosY) {

        case 0:
            sprite.setTextureRect(sf::IntRect(textureSize.x*0, textureSize.y*5, textureSize.x, textureSize.y));
            break;

        case 1:
            sprite.setTextureRect(sf::IntRect(textureSize.x*0, textureSize.y*4, textureSize.x, textureSize.y));
            break;

        case 2:
            sprite.setTextureRect(sf::IntRect(textureSize.x*1, textureSize.y*5, textureSize.x, textureSize.y));
            break;

        case 3:
            sprite.setTextureRect(sf::IntRect(textureSize.x*1, textureSize.y*4, textureSize.x, textureSize.y));
            break;

        }

    }

    if((staminaUpdateClock.getElapsedTime().asSeconds() >= 1 || firstTime) && hasSword) {
        currentStamina--;
        staminaUpdateClock.restart().asSeconds();
        firstTime = false;
    }

}

void Player::updateShield() {

    shieldBarrier.setPosition(sprite.getPosition());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && hasShield && shieldPower >= 1) {

        shieldRaised = true;

    } else {

        shieldRaised = false;

    }

}


void Player::updateHealthBar(sf::View view1, float windowSizeX, float windowSizeY) {

    healthBarOutline.setPosition(view1.getCenter().x-windowSizeX/2+20, view1.getCenter().y-windowSizeY/2+20);
    healthBarOutline.setSize(sf::Vector2f((40*maxHealth), 20));
    healthBar.setPosition(healthBarOutline.getPosition());
    healthBar.setSize(sf::Vector2f((40*maxHealth)*(currentHealth/maxHealth), 20));


}

void Player::updateStaminaBar(int scalar) {

    if(currentStamina <= 0) {
        staminaBar.setSize(sf::Vector2f(0, 20));
    }

    if(!staminaDepleted) {

        staminaBar.setFillColor(sf::Color::Green);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

            playerSpeed = 1.5*scalar;
            sprinting = true;

            animation.changeSwitchTime(0.1333f);

        } else {

            playerSpeed = 1*scalar;
            sprinting = false;

            animation.changeSwitchTime(0.2f);

        }

        if(currentStamina <= 0) {

            staminaDepleted = true;

        }

    } else {

        staminaBar.setFillColor(sf::Color::Yellow);

        playerSpeed = 0.5*scalar;
        sprinting = false;

        animation.changeSwitchTime(0.4f);

        if(currentStamina >= maxStamina) {

            staminaDepleted = false;

        }

    }


    staminaBarOutline.setPosition(healthBarOutline.getPosition().x, healthBarOutline.getPosition().y+40);
    staminaBarOutline.setSize(sf::Vector2f(40*maxStamina, 20));
    staminaBar.setPosition(staminaBarOutline.getPosition());
    staminaBar.setSize(sf::Vector2f((40*maxStamina)*(currentStamina/maxStamina), 20));

}

void Player::updateShieldBar() {

    if(!hasShield) return;

    if(shieldPower < 1) {

        shieldBar.setFillColor(sf::Color::Magenta);

    } else {

        shieldBar.setFillColor(sf::Color::Blue);

    }

    shieldBarOutline.setPosition(healthBarOutline.getPosition().x, healthBarOutline.getPosition().y+80);
    shieldBarOutline.setSize(sf::Vector2f(50*shieldPowerMax, 20));
    shieldBar.setPosition(shieldBarOutline.getPosition());
    shieldBar.setSize(sf::Vector2f((50*shieldPowerMax)*(shieldPower/shieldPowerMax), 20));

    if(shieldPower < shieldPowerMax && !shieldDepleted) {

        shieldDepleted = true;
        shieldRechargeTimer.restart().asSeconds();

    }

}


bool Player::isAttacking() { return attacking; }


bool Player::isShieldRaised() { return shieldRaised; }

float Player::getShieldPower() { return shieldPower; }


void Player::decreaseHealth(float amount) {

    currentHealth -= amount;

}

void Player::decreaseShieldPower(float amount) {

    if(shieldPower > 0) shieldPower -= amount;

    if(shieldPower < 0) shieldPower = 0;

}


void Player::giveSword() { hasSword = true; }
void Player::giveShield() { hasShield = true; }


float Player::getSwordDamage() { return swordDamage; }
void Player::setSwordDamage(float sD) { swordDamage = sD; }


void Player::resetInvincibilityTimer() {

    invinciblityTimer.restart().asSeconds();

}


sf::Clock Player::getInvincibilityTimer() {

    return invinciblityTimer;

}

bool Player::isStaminaDepleted() { return staminaDepleted; }

void Player::setSprinting(bool val) { sprinting = val; }


void Player::refreshStamina() {

    if(sprintingClock.getElapsedTime().asSeconds() >= 0.01 && sprinting) {

        currentStamina-=0.02;
        sprintingClock.restart().asSeconds();

    }

    if(pushingClock.getElapsedTime().asSeconds() >= 0.01 && pushing) {

        currentStamina-=0.01;
        pushingClock.restart().asSeconds();

    }

    if(staminaRecoveryClock.getElapsedTime().asSeconds() >= 0.01 && currentStamina < maxStamina && !sprinting && !pushing) {

        currentStamina+=staminaRecoveryRate;
        staminaRecoveryClock.restart().asSeconds();

    }

}

void Player::refreshShieldPower() {

    if(shieldRechargeTimer.getElapsedTime().asSeconds() >= 0.05 && shieldDepleted) {

        shieldPower+=0.005;
        shieldRechargeTimer.restart().asSeconds();

        if(shieldPower >= shieldPowerMax) {

            shieldPower = shieldPowerMax;
            shieldDepleted = false;

        }

    }

}


void Player::addStaminaVessel() {

    maxStamina++;
    currentStamina = maxStamina;

}

void Player::addHeartContainer() {

    maxHealth++;
    currentHealth = maxHealth;

}
