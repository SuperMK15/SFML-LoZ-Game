#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Fixed.h"
#include "Moveables.h"
#include "Button.h"
#include "Octorok.h"
#include "Orb.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Level {

    float levelSizeX, levelSizeY;
    float startingPosX, startingPosY;

    int levelNum;

    bool changeSpeed;
    float speedScalar;

    sf::RectangleShape background;
    sf::Texture* backgroundTexture = new sf::Texture;

    sf::RectangleShape gameOverScreen;
    sf::Texture* gameOverTexture = new sf::Texture;
    bool firstGameOver = true;

    sf::RectangleShape staminaVessel;
    sf::Texture* staminaVesselTexture = new sf::Texture;
    bool staminaVesselClaimed;
    bool drawStaminaVessel = false;

    sf::RectangleShape heartContainer;
    sf::Texture* heartContainerTexture = new sf::Texture;
    bool heartContainerClaimed;
    bool drawHeartContainer = false;

    sf::RectangleShape specialItem;
    sf::Texture* specialItemTexture = new sf::Texture;
    bool specialItemClaimed;
    bool drawSpecialItem = false;

    sf::RectangleShape endLevelCrystal;
    sf::Texture *endLevelCrystalTexture = new sf::Texture;
    bool drawEndLevelCrystal = false;

    sf::Music levelMusic, gameOverMusic, finalBossMusic;
    bool finalBossMusicPlaying = false;

    std::vector<Fixed> allFixed;

    std::vector<Moveable> allMoveables;

    std::vector<Button> allButtons;

    std::vector<Octorok> allOctoroks;

    std::vector<Orb> allOrbs;

    std::vector<sf::RectangleShape> allClues;
    std::vector<sf::Texture*> allClueTextures;

public:
    Level();
    Level(float, float, int, std::string, std::string, sf::Vector2f, float);

    void setBackgroundColor(sf::Color);

    void addFixed(float, float, float, float, std::string);

    void addMoveable(float, float, float = 200, float = 130);

    void addButton(float, float, float = 200);

    void addOctorok(int, float, float);

    void addStaminaVessel(float, float);

    void addHeartContainer(float, float);

    void setSpecialItem(float, float, float, float, std::string);

    void setEndLevelCrystal(float, float);

    void addClue(float, float, float, float, std::string);

    void addOrb(float, float);


    void gameOver(sf::RenderWindow&, sf::View&, Player&);


    void updateStaminaVessel(Player&, bool);

    void updateHeartContainer(Player&, bool);

    void updateSpecialItem(Player&, bool);

    bool updateEndLevelCrystal(Player&, bool);


    void run(Player&, sf::RenderWindow&, sf::View&, float, bool&, int&);

};

#endif // LEVEL_H
