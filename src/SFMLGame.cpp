#include "SFMLGame.h"
#include <iostream>

SFMLGame::SFMLGame() 
    : window(sf::VideoMode(800, 600), "Pokemon C++ Battle"),
      currentState(GameState::MAIN_MENU),
      animationTimer(0.0f),
      animationPlaying(false),
      selectedAttack(0)
{
    // Configure window
    window.setFramerateLimit(60);
    
    // Load resources
    loadResources();
    
    // Setup menu background
    menuBackground.setSize(sf::Vector2f(800, 600));
    menuBackground.setFillColor(sf::Color(50, 50, 150));
    
    // Setup battle background
    battleBackground.setSize(sf::Vector2f(800, 600));
    battleBackground.setFillColor(sf::Color(100, 200, 100));
    
    // Setup selection background
    selectBackground.setSize(sf::Vector2f(800, 600));
    selectBackground.setFillColor(sf::Color(150, 150, 200));
    
    // Setup menu options
    sf::Text startOption("Commencer un combat", font, 30);
    startOption.setPosition(300, 200);
    startOption.setFillColor(sf::Color::White);
    
    sf::Text quitOption("Quitter", font, 30);
    quitOption.setPosition(300, 300);
    quitOption.setFillColor(sf::Color::White);
    
    menuOptions.push_back(startOption);
    menuOptions.push_back(quitOption);
    
    // Setup battle text
    battleText.setFont(font);
    battleText.setCharacterSize(24);
    battleText.setFillColor(sf::Color::White);
    battleText.setPosition(50, 450);
    
    // Setup result text
    resultText.setFont(font);
    resultText.setCharacterSize(36);
    resultText.setFillColor(sf::Color::Yellow);
    resultText.setPosition(200, 250);
    
    // Initialize game logic
    gameLogic.initialize();
}

void SFMLGame::loadResources() {
    // Load font
    if (!font.loadFromFile("resources/fonts/pokemon.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police" << std::endl;
        font.loadFromFile("resources/fonts/arial.ttf"); // Fallback font
    }
    
    // Load textures
    textures["background"].loadFromFile("resources/images/battle_bg.jpg");
    textures["pikachu_back"].loadFromFile("resources/images/pikachu_back.png");
    textures["pikachu_front"].loadFromFile("resources/images/pikachu_front.png");
    textures["dracaufeu_back"].loadFromFile("resources/images/dracaufeu_back.png");
    textures["dracaufeu_front"].loadFromFile("resources/images/dracaufeu_front.png");
    textures["florizarre_back"].loadFromFile("resources/images/florizarre_back.png");
    textures["florizarre_front"].loadFromFile("resources/images/florizarre_front.png");
    textures["tortank_back"].loadFromFile("resources/images/tortank_back.png");
    textures["tortank_front"].loadFromFile("resources/images/tortank_front.png");
    textures["alakazam_back"].loadFromFile("resources/images/alakazam_back.png");
    textures["alakazam_front"].loadFromFile("resources/images/alakazam_front.png");
    textures["ronflex_back"].loadFromFile("resources/images/ronflex_back.png");
    textures["ronflex_front"].loadFromFile("resources/images/ronflex_front.png");
    textures["attack_thunder"].loadFromFile("resources/images/thunder.png");
    textures["attack_fire"].loadFromFile("resources/images/fire.png");
    textures["attack_water"].loadFromFile("resources/images/water.png");
    textures["attack_grass"].loadFromFile("resources/images/grass.png");
    
    // Load sounds
    soundBuffers["select"].loadFromFile("resources/sounds/select.wav");
    soundBuffers["attack"].loadFromFile("resources/sounds/attack.wav");
    soundBuffers["hit"].loadFromFile("resources/sounds/hit.wav");
    soundBuffers["victory"].loadFromFile("resources/sounds/victory.wav");
    soundBuffers["defeat"].loadFromFile("resources/sounds/defeat.wav");
    
    sounds["select"].setBuffer(soundBuffers["select"]);
    sounds["attack"].setBuffer(soundBuffers["attack"]);
    sounds["hit"].setBuffer(soundBuffers["hit"]);
    sounds["victory"].setBuffer(soundBuffers["victory"]);
    sounds["defeat"].setBuffer(soundBuffers["defeat"]);
}

void SFMLGame::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        handleEvents();
        update(deltaTime);
        render();
    }
}

void SFMLGame::handleEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Handle key presses
        if (event.type == sf::Event::KeyPressed) {
            switch (currentState) {
                case GameState::MAIN_MENU:
                    handleMainMenu();
                    break;
                    
                case GameState::POKEMON_SELECT:
                    handlePokemonSelect();
                    break;
                    
                case GameState::BATTLE_MENU:
                    handleBattleMenu();
                    break;
                    
                case GameState::BATTLE_RESULT:
                    if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                        currentState = GameState::MAIN_MENU;
                        sounds["select"].play();
                    }
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void SFMLGame::update(float deltaTime) {
    switch (currentState) {
        case GameState::ATTACK_ANIMATION:
            handleAttackAnimation(deltaTime);
            break;
            
        default:
            break;
    }
}

void SFMLGame::render() {
    window.clear();
    
    switch (currentState) {
        case GameState::MAIN_MENU:
            window.draw(menuBackground);
            window.draw(sf::Text("POKEMON C++ BATTLE", font, 48));
            
            for (const auto& option : menuOptions) {
                window.draw(option);
            }
            break;
            
        case GameState::POKEMON_SELECT:
            window.draw(selectBackground);
            window.draw(sf::Text("CHOISISSEZ VOTRE POKEMON", font, 36));
            
            for (const auto& option : pokemonOptions) {
                window.draw(option);
            }
            break;
            
        case GameState::BATTLE:
        case GameState::BATTLE_MENU:
        case GameState::ATTACK_ANIMATION:
            window.draw(battleBackground);
            window.draw(playerPokemonSprite);
            window.draw(opponentPokemonSprite);
            window.draw(playerHealthBar);
            window.draw(opponentHealthBar);
            window.draw(battleText);
            
            if (currentState == GameState::BATTLE_MENU) {
                for (const auto& option : attackOptions) {
                    window.draw(option);
                }
            }
            break;
            
        case GameState::BATTLE_RESULT:
            window.draw(battleBackground);
            window.draw(playerPokemonSprite);
            window.draw(opponentPokemonSprite);
            window.draw(resultText);
            break;
    }
    
    window.display();
}

void SFMLGame::handleMainMenu() {
    static int selectedOption = 0;
    
    if (event.key.code == sf::Keyboard::Up) {
        selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Down) {
        selectedOption = (selectedOption + 1) % menuOptions.size();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Return) {
        if (selectedOption == 0) {
            // Start battle option
            currentState = GameState::POKEMON_SELECT;
            
            // Create pokemon selection options
            pokemonOptions.clear();
            for (size_t i = 0; i < 6; ++i) {
                sf::Text option("", font, 24);
                switch (i) {
                    case 0: option.setString("Pikachu"); break;
                    case 1: option.setString("Dracaufeu"); break;
                    case 2: option.setString("Florizarre"); break;
                    case 3: option.setString("Tortank"); break;
                    case 4: option.setString("Alakazam"); break;
                    case 5: option.setString("Ronflex"); break;
                }
                option.setPosition(300, 150 + i * 50);
                option.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
                pokemonOptions.push_back(option);
            }
        } else {
            // Quit option
            window.close();
        }
        sounds["select"].play();
    }
    
    // Update menu visuals
    for (size_t i = 0; i < menuOptions.size(); ++i) {
        menuOptions[i].setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
    }
}

void SFMLGame::handlePokemonSelect() {
    static int selectedOption = 0;
    
    if (event.key.code == sf::Keyboard::Up) {
        selectedOption = (selectedOption - 1 + pokemonOptions.size()) % pokemonOptions.size();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Down) {
        selectedOption = (selectedOption + 1) % pokemonOptions.size();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Return) {
        // Select pokemon and start battle
        selectOption(selectedOption);
        startBattle();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Escape) {
        currentState = GameState::MAIN_MENU;
        sounds["select"].play();
    }
    
    // Update selection visuals
    for (size_t i = 0; i < pokemonOptions.size(); ++i) {
        pokemonOptions[i].setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
    }
}

void SFMLGame::handleBattle() {
    // Let the battle animation play
}

void SFMLGame::handleBattleMenu() {
    static int selectedOption = 0;
    
    if (event.key.code == sf::Keyboard::Up) {
        selectedOption = (selectedOption - 1 + attackOptions.size()) % attackOptions.size();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Down) {
        selectedOption = (selectedOption + 1) % attackOptions.size();
        sounds["select"].play();
    } else if (event.key.code == sf::Keyboard::Return) {
        // Execute selected attack
        selectedAttack = selectedOption;
        
        battleText.setString("Vous utilisez " + attackOptions[selectedOption].getString() + "!");
        
        // Start attack animation
        currentState = GameState::ATTACK_ANIMATION;
        animationTimer = 0.0f;
        animationPlaying = true;
        sounds["attack"].play();
    }
    
    // Update selection visuals
    for (size_t i = 0; i < attackOptions.size(); ++i) {
        attackOptions[i].setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
    }
}

void SFMLGame::handleAttackAnimation(float deltaTime) {
    animationTimer += deltaTime;
    
    // Basic animation: shake the opponent sprite
    if (animationTimer < 1.0f) {
        opponentPokemonSprite.setPosition(
            500 + std::sin(animationTimer * 30) * 10,
            200
        );
        
        // Flash the opponent sprite
        if (static_cast<int>(animationTimer * 10) % 2 == 0) {
            opponentPokemonSprite.setColor(sf::Color(255, 255, 255));
        } else {
            opponentPokemonSprite.setColor(sf::Color(255, 100, 100));
        }
    } else if (animationTimer < 2.0f) {
        // Play hit sound once
        if (animationTimer < 1.1f) {
            sounds["hit"].play();
            opponentPokemonSprite.setColor(sf::Color(255, 255, 255));
        }
        
        // Update battle text
        battleText.setString("L'attaque est efficace!");
        
        // Simulate damage
        opponentHealthBar.setSize(sf::Vector2f(
            std::max(0.0f, opponentHealthBar.getSize().x - 0.5f),
            opponentHealthBar.getSize().y
        ));
    } else if (animationTimer < 3.0f) {
        // Update battle text
        battleText.setString("L'adversaire attaque!");
        
        // Simulate opponent's attack animation
        playerPokemonSprite.setPosition(
            150 + std::sin(animationTimer * 30) * 10,
            300
        );
        
        // Flash the player sprite
        if (static_cast<int>(animationTimer * 10) % 2 == 0) {
            playerPokemonSprite.setColor(sf::Color(255, 255, 255));
        } else {
            playerPokemonSprite.setColor(sf::Color(255, 100, 100));
        }
    } else if (animationTimer < 4.0f) {
        // Play hit sound once
        if (animationTimer < 3.1f) {
            sounds["hit"].play();
            playerPokemonSprite.setColor(sf::Color(255, 255, 255));
        }
        
        // Update battle text
        battleText.setString("Vous subissez des dégâts!");
        
        // Simulate damage
        playerHealthBar.setSize(sf::Vector2f(
            std::max(0.0f, playerHealthBar.getSize().x - 0.3f),
            playerHealthBar.getSize().y
        ));
    } else {
        // Reset animation state
        animationPlaying = false;
        opponentPokemonSprite.setPosition(500, 200);
        playerPokemonSprite.setPosition(150, 300);
        opponentPokemonSprite.setColor(sf::Color(255, 255, 255));
        playerPokemonSprite.setColor(sf::Color(255, 255, 255));
        
        // Check if battle is over
        if (opponentHealthBar.getSize().x <= 0) {
            currentState = GameState::BATTLE_RESULT;
            resultText.setString("VICTOIRE!");
            sounds["victory"].play();
        } else if (playerHealthBar.getSize().x <= 0) {
            currentState = GameState::BATTLE_RESULT;
            resultText.setString("DÉFAITE!");
            sounds["defeat"].play();
        } else {
            // Continue battle
            currentState = GameState::BATTLE_MENU;
            battleText.setString("Que voulez-vous faire?");
        }
    }
}

void SFMLGame::handleBattleResult() {
    // Handled in the event handler
}

void SFMLGame::selectOption(int index) {
    // Simulate game logic pokemon selection
    gameLogic.selectPlayerPokemon();
}

void SFMLGame::startBattle() {
    // Simulate game logic battle setup
    gameLogic.selectOpponentPokemon();
    
    // Setup battle sprites and UI
    std::string playerPokemonName = pokemonOptions[selectedAttack].getString();
    std::string opponentPokemonName;
    
    // Randomize opponent pokemon
    int opponentIndex = std::rand() % 6;
    switch (opponentIndex) {
        case 0: opponentPokemonName = "pikachu"; break;
        case 1: opponentPokemonName = "dracaufeu"; break;
        case 2: opponentPokemonName = "florizarre"; break;
        case 3: opponentPokemonName = "tortank"; break;
        case 4: opponentPokemonName = "alakazam"; break;
        case 5: opponentPokemonName = "ronflex"; break;
    }
    
    // Set up player pokemon sprite
    playerPokemonSprite.setTexture(textures[playerPokemonName.substr(0, playerPokemonName.find(" ")) + "_back"]);
    playerPokemonSprite.setPosition(150, 300);
    playerPokemonSprite.setScale(2.0f, 2.0f);
    
    // Set up opponent pokemon sprite
    opponentPokemonSprite.setTexture(textures[opponentPokemonName + "_front"]);
    opponentPokemonSprite.setPosition(500, 200);
    opponentPokemonSprite.setScale(2.0f, 2.0f);
    
    // Set up health bars
    playerHealthBar.setSize(sf::Vector2f(200, 20));
    playerHealthBar.setFillColor(sf::Color::Green);
    playerHealthBar.setPosition(150, 250);
    
    opponentHealthBar.setSize(sf::Vector2f(200, 20));
    opponentHealthBar.setFillColor(sf::Color::Green);
    opponentHealthBar.setPosition(500, 150);
    
    // Set up attack options
    attackOptions.clear();
    
    // Simplified attack list
    std::vector<std::string> attacks = {"Attaque 1", "Attaque 2", "Attaque 3", "Attaque 4"};
    
    for (size_t i = 0; i < attacks.size(); ++i) {
        sf::Text option(attacks[i], font, 24);
        option.setPosition(450, 450 + i * 30);
        option.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        attackOptions.push_back(option);
    }
    
    battleText.setString("Un combat sauvage commence!");
    
    currentState = GameState::BATTLE_MENU;
}

void SFMLGame::executeAttack() {
    // Simulate attack execution
    // This would normally call gameLogic methods
}

void SFMLGame::updateHealthBars() {
    // Update health bars based on gameLogic state
}