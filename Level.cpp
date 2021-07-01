#include "Level.h"

Level::Level(float xSize, float ySize, int num, std::string backgroundFilePath, std::string musicFilePath, sf::Vector2f startingPos, float scalar) {

    levelSizeX = xSize;
    levelSizeY = ySize;

    startingPosX = startingPos.x;
    startingPosY = startingPos.y;

    levelNum = num;

    speedScalar = scalar;

    background.setSize(sf::Vector2f(xSize, ySize));

    backgroundTexture->loadFromFile(backgroundFilePath);
    background.setTexture(backgroundTexture);

    gameOverScreen.setSize(sf::Vector2f(1500, 900));
    gameOverScreen.setOrigin(750, 450);
    gameOverTexture->loadFromFile("images/GameOverScreen.png");
    gameOverScreen.setTexture(gameOverTexture);

    levelMusic.setVolume(25);
    levelMusic.openFromFile(musicFilePath);
    levelMusic.setLoop(true);

    gameOverMusic.setVolume(50);
    gameOverMusic.openFromFile("audio/GameOverSong.wav");
    gameOverMusic.setLoop(false);

    finalBossMusic.setVolume(50);
    finalBossMusic.openFromFile("audio/FinalBossMusic.wav");
    finalBossMusic.setLoop(true);

}

void Level::setBackgroundColor(sf::Color color) {

    background.setFillColor(color);

}


void Level::addFixed(float xSize, float ySize, float xPos, float yPos, std::string filePath) {

    allFixed.push_back({xSize, ySize, xPos, yPos, filePath});

}

void Level::addMoveable(float xPos, float yPos, float xSize, float ySize) {

    allMoveables.push_back({xPos, yPos, xSize, ySize});

}

void Level::addButton(float xPos, float yPos, float SIZE) {

    allButtons.push_back({xPos, yPos, SIZE});

}

void Level::addOctorok(int type, float xPos, float yPos) {

    allOctoroks.push_back({type, xPos, yPos});

}

void Level::addOrb(float xPos, float yPos) {

    allOrbs.push_back({xPos, yPos});

}


void Level::addStaminaVessel(float xPos, float yPos) {

    staminaVesselTexture->loadFromFile("images/StaminaVessel.png");

    staminaVessel.setSize(sf::Vector2f(100, 100));
    staminaVessel.setPosition(sf::Vector2f(xPos, yPos));
    staminaVessel.setTexture(staminaVesselTexture);

    staminaVesselClaimed = false;

}

void Level::addHeartContainer(float xPos, float yPos) {

    heartContainerTexture->loadFromFile("images/HeartContainer.png");

    heartContainer.setSize(sf::Vector2f(75, 75));
    heartContainer.setPosition(sf::Vector2f(xPos, yPos));
    heartContainer.setTexture(heartContainerTexture);

    heartContainerClaimed = false;

}

void Level::setSpecialItem(float xSize, float ySize, float xPos, float yPos, std::string filePath) {

    specialItemTexture->loadFromFile(filePath);

    specialItem.setSize(sf::Vector2f(xSize, ySize));
    specialItem.setPosition(xPos, yPos);
    specialItem.setTexture(specialItemTexture);

    specialItemClaimed = false;

}

void Level::setEndLevelCrystal(float xPos, float yPos) {

    endLevelCrystalTexture->loadFromFile("images/EndCrystalTexture.png");

    endLevelCrystal.setSize(sf::Vector2f(200.0f, 300.0f));
    endLevelCrystal.setOrigin(100, 150);
    endLevelCrystal.setPosition(xPos, yPos);
    endLevelCrystal.setTexture(endLevelCrystalTexture);

    drawEndLevelCrystal = false;

}


void Level::addClue(float xSize, float ySize, float xPos, float yPos, std::string filePath) {

    allClueTextures.push_back(new sf::Texture);
    allClueTextures.back()->loadFromFile(filePath);
    allClueTextures.back()->setSmooth(true);

    allClues.push_back({});
    allClues.back().setSize(sf::Vector2f(xSize, ySize));
    allClues.back().setPosition(xPos, yPos);
    allClues.back().setTexture(allClueTextures.back());

}


void Level::gameOver(sf::RenderWindow &window, sf::View &view, Player &player) {

    if(firstGameOver) {

        if(!finalBossMusicPlaying) levelMusic.stop();
        if(finalBossMusicPlaying) finalBossMusic.stop();
        gameOverMusic.play();

        gameOverScreen.setPosition(view.getCenter());

        window.clear();
        window.draw(gameOverScreen);
        window.display();

        firstGameOver = false;

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {

        window.close();

    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {

        player.revive();

        for(Octorok &octorok : allOctoroks) {

            octorok.revive();

        }

        player.setPosition(startingPosX, startingPosY);

        view.setCenter(player.getSprite().getPosition());
        window.setView(view);

        levelMusic.play();

    }



}


void Level::updateStaminaVessel(Player &player, bool condition) {

    if(condition) {

        drawStaminaVessel = true;

        if(staminaVessel.getGlobalBounds().contains(player.getSprite().getPosition()) && !staminaVesselClaimed) {

            player.addStaminaVessel();
            staminaVesselClaimed = true;

        }

    }

}

void Level::updateHeartContainer(Player &player, bool condition) {

    if(condition) {

        drawHeartContainer = true;

        if(heartContainer.getGlobalBounds().contains(player.getSprite().getPosition()) && !heartContainerClaimed) {

            player.addHeartContainer();
            heartContainerClaimed = true;

        }

    }

}

void Level::updateSpecialItem(Player &player, bool condition) {

    if(condition) {

        drawSpecialItem = true;

        if(specialItem.getGlobalBounds().contains(player.getSprite().getPosition())) {

            switch(levelNum) {

            case 1:
                player.giveSword();
                break;

            case 2:
                player.giveShield();
                break;

            case 3:
                player.setSwordDamage(1.5);
                break;

            }

            specialItemClaimed = true;

        }

    }

}

bool Level::updateEndLevelCrystal(Player &player, bool condition) {

    if(condition) {

        drawEndLevelCrystal = true;

        if(endLevelCrystal.getGlobalBounds().contains(player.getSprite().getPosition())) {

            return true;

        }

    }

    return false;

}


void Level::run(Player &player, sf::RenderWindow &window, sf::View &view, float deltaTime, bool &setUpNeeded, int &gameLoopCounter) {

    if(player.isDead()) {
        gameOver(window, view, player);
        return;
    }

    if(setUpNeeded) {

        player.setPosition(startingPosX, startingPosY);

        view.setCenter(player.getSprite().getPosition());
        window.setView(view);

        setUpNeeded = false;

        levelMusic.play();

    }

    changeSpeed = true;

    player.checkAllMovementDirections(allFixed);
    player.reset(speedScalar);
    player.updateShield();
    player.updateHealthBar(view, window.getSize().x, window.getSize().y);
    player.updateStaminaBar(speedScalar);
    player.updateShieldBar();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && player.getUp()) {

        for(int i = 0; i < allMoveables.size(); i++) {

            if(allMoveables[i].checkInteractionForMove(player) == "MOVE_UP") {

                if(!player.isStaminaDepleted() && allMoveables[i].checkUpMovement(allFixed) && Moveable::checkVerticalCollisionForArray(allMoveables, allMoveables[i].getSprite(), i) != "BOTTOM") {
                    player.isPushing();
                    allMoveables[i].moveBoulder(0.0f, -player.getPlayerSpeed());
                } else {
                    player.setBlocked(true);
                }
            }

        }


        if(player.getSprite().getPosition().y > 30 && !player.getBlocked()) {

            player.moveUp(deltaTime);

            if(player.getSprite().getPosition().y > (window.getSize().y/2) && player.getSprite().getPosition().y < (levelSizeY - (window.getSize().y/2))) {
                view.move(0.0f, -player.getPlayerSpeed());
                window.setView(view);
            }

        } else {
            player.setSprinting(false);
        }


    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && player.getDown()) {

        for(int i = 0; i < allMoveables.size(); i++) {

            if(allMoveables[i].checkInteractionForMove(player) == "MOVE_DOWN") {

                if(!player.isStaminaDepleted() && allMoveables[i].checkDownMovement(allFixed, 200, 95) && Moveable::checkVerticalCollisionForArray(allMoveables, allMoveables[i].getSprite(), i) != "TOP") {
                    player.isPushing();
                    allMoveables[i].moveBoulder(0.0f, player.getPlayerSpeed());
                } else {
                    player.setBlocked(true);
                }
            }

        }

        if(player.getSprite().getPosition().y < levelSizeY-30 && !player.getBlocked()) {

            player.moveDown(deltaTime);

            if(player.getSprite().getPosition().y < (levelSizeY - (window.getSize().y/2)) && player.getSprite().getPosition().y > (window.getSize().y/2)) {
                view.move(0.0f, player.getPlayerSpeed());
                window.setView(view);
            }

        } else {
            player.setSprinting(false);
        }

    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getLeft()) {

        for(int i = 0; i < allMoveables.size(); i++) {

            if(allMoveables[i].checkInteractionForMove(player) == "MOVE_LEFT") {

                if(!player.isStaminaDepleted() && allMoveables[i].checkLeftMovement(allFixed) && Moveable::checkHorizontalCollisionForArray(allMoveables, allMoveables[i].getSprite(), i) != "RIGHT") {
                    player.isPushing();
                    allMoveables[i].moveBoulder(-player.getPlayerSpeed(), 0.0f);
                } else {
                    player.setBlocked(true);
                }

            }

        }


        if(player.getSprite().getPosition().x > 30 && !player.getBlocked()) {

            player.moveLeft(deltaTime);

            if(player.getSprite().getPosition().x > (window.getSize().x/2) && player.getSprite().getPosition().x < (levelSizeX - (window.getSize().x/2))) {
                view.move(-player.getPlayerSpeed(), 0.0f);
                window.setView(view);
            }

        } else {
            player.setSprinting(false);
        }


    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getRight()) {

        for(int i = 0; i < allMoveables.size(); i++) {

            if(allMoveables[i].checkInteractionForMove(player) == "MOVE_RIGHT") {

                if(!player.isStaminaDepleted() && allMoveables[i].checkRightMovement(allFixed, 160, 130) && Moveable::checkHorizontalCollisionForArray(allMoveables, allMoveables[i].getSprite(), i) != "LEFT") {
                    player.isPushing();
                    allMoveables[i].moveBoulder(player.getPlayerSpeed(), 0.0f);
                } else {
                    player.setBlocked(true);
                }

            }

        }


        if(player.getSprite().getPosition().x < levelSizeX-30) {

            player.moveRight(deltaTime);

            if(player.getSprite().getPosition().x < (levelSizeX - (window.getSize().x/2)) && player.getSprite().getPosition().x > (window.getSize().x/2)) {
                view.move(player.getPlayerSpeed(), 0.0f);
                window.setView(view);
            }

        } else {
            player.setSprinting(false);
        }


    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !player.isStaminaDepleted()) {

        player.updateSword();
        changeSpeed = false;

    } else {

        player.idle();
        changeSpeed = false;

    }

    player.refreshStamina();
    player.refreshShieldPower();

    // Level Specific Modifications -------------------------------------------------------------------------------------------------------------

    switch(levelNum) {

    case 1:
        updateStaminaVessel(player, !staminaVesselClaimed && allButtons[3].isPressed());
        updateSpecialItem(player, allButtons[0].isPressed() && allButtons[1].isPressed() && allButtons[2].isPressed());

        if(updateEndLevelCrystal(player, allOctoroks[0].isDead() && allOctoroks[1].isDead() && allOctoroks[2].isDead())) {

            gameLoopCounter = 0;
            levelMusic.stop();
            return;

        }

        break;

    case 2:
        staminaVessel.setPosition(allOctoroks[0].getSprite().getPosition());
        updateStaminaVessel(player, allOctoroks[0].isDead());

        heartContainer.setPosition(allOctoroks[5].getSprite().getPosition());
        updateHeartContainer(player, allOctoroks[5].isDead());

        updateSpecialItem(player, allButtons[0].isPressed() && !allButtons[1].isPressed() && allButtons[2].isPressed() && allButtons[3].isPressed() && !allButtons[4].isPressed() && allButtons[5].isPressed());

        if(updateEndLevelCrystal(player, allButtons[0].isPressed() && !allButtons[1].isPressed() && allButtons[2].isPressed() && allButtons[3].isPressed() && !allButtons[4].isPressed() &&
                                 allButtons[5].isPressed() && allOctoroks[1].isDead() && allOctoroks[2].isDead() && allOctoroks[3].isDead() && allOctoroks[4].isDead())) {

            gameLoopCounter = 0;
            levelMusic.stop();
            return;

        }

        break;

    case 3:
        updateStaminaVessel(player, !allOrbs[0].isActivated() && allOrbs[1].isActivated() && allOrbs[2].isActivated() && !allOrbs[3].isActivated() && allOrbs[4].isActivated() && !allOrbs[5].isActivated());

        heartContainer.setPosition(allOctoroks[4].getSprite().getPosition());
        updateHeartContainer(player, allOctoroks[4].isDead());

        updateSpecialItem(player, allOrbs[6].isActivated() && !allOrbs[7].isActivated() && allOrbs[8].isActivated() && allOrbs[9].isActivated() && allOrbs[10].isActivated() && !allOrbs[11].isActivated());

        if(updateEndLevelCrystal(player, allOctoroks[1].isDead() && allOctoroks[2].isDead() && (player.getSwordDamage() == 1.5))) {

            gameLoopCounter = 0;
            levelMusic.stop();
            return;

        }

        break;

    case 4:
        if(allOctoroks[3].getDetectionArea().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) && !allOctoroks[3].isDead()) {

            if(!finalBossMusicPlaying) {
                levelMusic.stop();
                finalBossMusic.play();
                finalBossMusicPlaying = true;
            }

        } else {

            if(finalBossMusicPlaying) {
                finalBossMusic.stop();
                levelMusic.play();
                finalBossMusicPlaying = false;
            }

        }

        staminaVessel.setPosition(allOctoroks[1].getSprite().getPosition());
        updateStaminaVessel(player, allOctoroks[1].isDead());

        heartContainer.setPosition(allOctoroks[2].getSprite().getPosition());
        updateHeartContainer(player, allOctoroks[2].isDead());

        if(updateEndLevelCrystal(player, allOctoroks[0].isDead() && allOctoroks[1].isDead() && allOctoroks[2].isDead() && allOctoroks[3].isDead())) {

            gameLoopCounter = 0;
            levelMusic.stop();
            return;

        }

    }

    // Level Specific Modifications -------------------------------------------------------------------------------------------------------------

    // Drawing Everything ------------------------------------------------

    window.clear();

    window.draw(background);

    for(Fixed fixed : allFixed) {

        window.draw(fixed.getSprite());

    }

    for(Button &button : allButtons) {

        button.updateButton(allMoveables);
        window.draw(button.getSprite());

    }

    for(Orb &orb : allOrbs) {

        orb.update(player, window);
        window.draw(orb.getSprite());

    }

    for(sf::RectangleShape clue : allClues) {

        window.draw(clue);

    }

    if(drawStaminaVessel && !staminaVesselClaimed) window.draw(staminaVessel);
    if(drawHeartContainer && !heartContainerClaimed) window.draw(heartContainer);

    if(drawSpecialItem && !specialItemClaimed) window.draw(specialItem);

    if(drawEndLevelCrystal) window.draw(endLevelCrystal);

    for(Octorok &octorok : allOctoroks) {

        octorok.updateAndDraw(window, player, deltaTime, changeSpeed, speedScalar);

    }

    for(Moveable moveable : allMoveables) {

        window.draw(moveable.getSprite());

    }

    player.draw(window);

    window.display();

    // Drawing Everything ------------------------------------------------

}
