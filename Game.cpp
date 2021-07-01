#include "Game.h"

void Game::run() {

    float windowSizeX = 1500;
    float windowSizeY = 900;

    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML Link Game", sf::Style::Close);

    //Player player;
    player.setPosition(windowSizeX/2, 2000.0f);

    sf::View view(player.getSprite().getPosition(), sf::Vector2f(windowSizeX, windowSizeY));
    window.setView(view);

    float deltaTime = 0.0f;
    sf::Clock clock;

    // Level 1 Creation ----------------------------------------------------------------------------------------------------
    Level level1(8000, 4000, 1, "images/B1_Texture.png", "audio/OverworldTheme1.wav", sf::Vector2f(windowSizeX/2, 2000.0f), 10);

    level1.addFixed(2750.0f, 1500.0f, 0.0f, 0.0f, "images/B1S1_Texture.png");
    level1.addFixed(2400.0f, 1500.0f, 0.0f, 2500.0f, "images/B1S2_Texture.png");
    level1.addFixed(2050.0f, 500.0f, 2400.0f, 3500.0f, "images/B1S3_Texture.png");
    level1.addFixed(3050.0f, 1200.0f, 4950.0f, 0.0f, "images/B1S4_Texture.png");
    level1.addFixed(1200.0f, 1300.0f, 4450.0f, 1200.0f, "images/B1S5_Texture.png");

    for(int i = 0; i < 8; i++) level1.addMoveable(2761.11+(i*211.11), 1370);

    level1.addButton(2800.0f, 525.0f);
    level1.addButton(3750.0f, 25.0f);
    level1.addButton(4700.0f, 525.0f);
    level1.addButton(2450.0f, 3250.0f);

    level1.addOctorok(1, 7900, 2500);
    level1.addOctorok(1, 7400, 2500);
    level1.addOctorok(1, 6900, 2500);

    level1.addStaminaVessel(2900, 3325);

    level1.setSpecialItem(75, 100, 3812.5f, 550.0f, "images/SwordTexture.png");

    level1.setEndLevelCrystal(7850, 2000);
    // Level 1 Creation -----------------------------------------------------------------------------------------------------


    // Level 2 Creation -----------------------------------------------------------------------------------------------------
    Level level2(8000, 8000, 2, "images/B2_Texture.png", "audio/OverworldTheme1.wav", sf::Vector2f(4000, 4000), 16);

    level2.addFixed(2500.0f, 2000.0f, 0.0f, 0.0f, "images/B2S1_Texture.png");
    level2.addFixed(2500.0f, 2000.0f, 5500.0f, 0.0f, "images/B2S1_Texture.png");
    level2.addFixed(2500.0f, 2000.0f, 0.0f, 6000.0f, "images/B2S1_Texture.png");
    level2.addFixed(2500.0f, 2000.0f, 5500.0f, 6000.0f, "images/B2S1_Texture.png");

    for(int i = 0; i < 3; i++) {
        level2.addMoveable(3700+(i*200), 3800);
        level2.addMoveable(3700+(i*200), 4050);
        level2.addMoveable(2600+(i*1300), 350);
        level2.addMoveable(2600+(i*1300), 7500);
    }
    level2.addMoveable(3700, 3925);
    level2.addMoveable(4100, 3925);

    for(int i = 0; i < 3; i++) level2.addButton(2600+(i*1300), 100);
    for(int i = 0; i < 3; i++) level2.addButton(2600+(i*1300), 7700);

    level2.addOctorok(2, 300, 5700);
    level2.addOctorok(1, 1250, 4250);
    level2.addOctorok(1, 2200, 2800);
    level2.addOctorok(1, 5800, 5200);
    level2.addOctorok(1, 6750, 3750);
    level2.addOctorok(2, 7700, 2300);

    level2.addStaminaVessel(300, 5700);
    level2.addHeartContainer(7700, 2300);

    level2.addClue(600, 390, 3700, 3675, "images/B2_Clue1.png");
    level2.addClue(600, 390, 3700, 3925, "images/B2_Clue2.png");
    level2.addClue(100, 130, 2650, 350, "images/1.png");
    level2.addClue(100, 130, 3950, 350, "images/2.png");
    level2.addClue(100, 130, 5250, 350, "images/3.png");
    level2.addClue(100, 130, 2650, 7500, "images/4.png");
    level2.addClue(100, 130, 3950, 7500, "images/5.png");
    level2.addClue(100, 130, 5250, 7500, "images/6.png");

    level2.setSpecialItem(90, 120, 3955, 3940, "images/GemOfShielding.png");

    level2.setEndLevelCrystal(4000, 4000);
    // Level 2 Creation -----------------------------------------------------------------------------------------------------


    // Level 3 Creation -----------------------------------------------------------------------------------------------------
    Level level3(7000.0f, 4000.0f, 3, "images/B3_Texture.png", "audio/OverworldTheme1.wav", sf::Vector2f(3500, 2000), 1);
    level3.setBackgroundColor(sf::Color(0, 200, 0));

    level3.addFixed(2000, 1000, 0, 0, "images/B3S1_Texture.png");
    level3.addFixed(2000, 1000, 5000, 0, "images/B3S1_Texture.png");
    level3.addFixed(2000, 1000, 0, 3000, "images/B3S1_Texture.png");
    level3.addFixed(2000, 1000, 5000, 3000, "images/B3S1_Texture.png");

    level3.addOrb(2250, 3800);
    level3.addOrb(2750, 3800);
    level3.addOrb(3250, 3800);
    level3.addOrb(3750, 3800);
    level3.addOrb(4250, 3800);
    level3.addOrb(4750, 3800);

    level3.addOrb(2250, 200);
    level3.addOrb(2750, 200);
    level3.addOrb(3250, 200);
    level3.addOrb(3750, 200);
    level3.addOrb(4250, 200);
    level3.addOrb(4750, 200);

    level3.addClue(100, 50, 2200, 3700, "images/B3Dot.png");
    level3.addClue(100, 50, 2700, 3700, "images/B3Bar.png");
    level3.addClue(100, 50, 3200, 3700, "images/B3Bar.png");
    level3.addClue(100, 50, 3700, 3700, "images/B3Dot.png");
    level3.addClue(100, 50, 4200, 3700, "images/B3Bar.png");
    level3.addClue(100, 50, 4700, 3700, "images/B3Dot.png");

    level3.addClue(100, 50, 2200, 300, "images/B3Bar.png");
    level3.addClue(100, 50, 2700, 300, "images/B3Dot.png");
    level3.addClue(100, 50, 3200, 300, "images/B3Bar.png");
    level3.addClue(100, 50, 3700, 300, "images/B3Bar.png");
    level3.addClue(100, 50, 4200, 300, "images/B3Bar.png");
    level3.addClue(100, 50, 4700, 300, "images/B3Dot.png");

    level3.addOctorok(2, 200, 1200);
    level3.addOctorok(1, 1000, 2800);
    level3.addOctorok(1, 5800, 1200);
    level3.addOctorok(2, 6300, 2800);
    level3.addOctorok(2, 6800, 2000);

    level3.addStaminaVessel(3500, 3400);
    level3.addHeartContainer(0, 0);

    level3.setSpecialItem(90, 90, 3500, 500, "images/AttackUpStone.png");

    level3.setEndLevelCrystal(3500, 2000);
    // Level 3 Creation -----------------------------------------------------------------------------------------------------


    // Level 4 Creation -----------------------------------------------------------------------------------------------------
    Level level4(10000.0f, 4000.0f, 4, "images/B4_Texture.png", "audio/FinalLevelSong.wav", sf::Vector2f(windowSizeX/2, 2000.0f), 10);

    level4.addFixed(1000, 1750, 0, 0, "images/B4TextureA.png");
    level4.addFixed(1000, 1750, 0, 2250, "images/B4TextureA.png");
    level4.addFixed(1000, 1750, 3000, 0, "images/B4TextureA.png");
    level4.addFixed(1000, 1750, 3000, 2250, "images/B4TextureA.png");
    level4.addFixed(1000, 1750, 6000, 0, "images/B4TextureA.png");
    level4.addFixed(1000, 1750, 6000, 2250, "images/B4TextureA.png");
    level4.addFixed(2000, 1000, 1000, 0, "images/B4TextureB.png");
    level4.addFixed(2000, 1000, 1000, 3000, "images/B4TextureB.png");
    level4.addFixed(2000, 1000, 4000, 0, "images/B4TextureB.png");
    level4.addFixed(2000, 1000, 4000, 3000, "images/B4TextureB.png");
    level4.addFixed(3000, 500, 7000, 0, "images/B4TextureC.png");
    level4.addFixed(3000, 500, 7000, 3500, "images/B4TextureC.png");

    for(int i = 0; i < 3; i++) {
        level4.addMoveable(3050, 1765+(i*160), 200, 150);
        level4.addMoveable(6050, 1765+(i*160), 200, 150);
    }

    level4.addOctorok(1, 1500, 2750);
    level4.addOctorok(2, 2500, 1250);
    level4.addOctorok(3, 5500, 2000);
    level4.addOctorok(4, 8500, 2000);

    level4.addStaminaVessel(0, 0);
    level4.addHeartContainer(0, 0);
    level4.setEndLevelCrystal(9800, 2000);
    // Level 4 Creation -----------------------------------------------------------------------------------------------------


    // Game Complete Screen Creation-----------------------------------------------------------------------------------------

    sf::RectangleShape gameCompleteScreen(sf::Vector2f(1500, 900));
    gameCompleteScreen.setOrigin(750, 450);
    sf::Texture gameCompletedTexture;
    gameCompletedTexture.loadFromFile("images/GameCompleteScreen.png");
    gameCompleteScreen.setTexture(&gameCompletedTexture);

    sf::Music gameCompletedMusic;
    gameCompletedMusic.setVolume(25);
    gameCompletedMusic.openFromFile("audio/GameCompleteMusic.wav");
    gameCompletedMusic.setLoop(false);

    // Game Complete Screen Creation-----------------------------------------------------------------------------------------

    int levelCounter = 0, gameLoopCounter = 0;
    bool setUpNeeded, gameCompleted = false;

    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        if(gameLoopCounter == 0) {
            levelCounter++;
            gameLoopCounter++;
            setUpNeeded = true;
        }

        // Game Logic
        switch(levelCounter) {

        case 1:
            level1.run(player, window, view, deltaTime, setUpNeeded, gameLoopCounter);
            break;

        case 2:
            level2.run(player, window, view, deltaTime, setUpNeeded, gameLoopCounter);
            break;

        case 3:
            level3.run(player, window, view, deltaTime, setUpNeeded, gameLoopCounter);
            break;

        case 4:
            level4.run(player, window, view, deltaTime, setUpNeeded, gameLoopCounter);
            break;

        case 5:
            if(setUpNeeded) {
                gameCompletedMusic.play();
                gameCompleteScreen.setPosition(view.getCenter());
                setUpNeeded = false;
            }

            window.clear();
            window.draw(gameCompleteScreen);
            window.display();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) gameCompleted = true;

            break;

        }

        if(gameCompleted) break;

    }

}
