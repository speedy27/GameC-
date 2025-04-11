#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include <map>
#include <string>
#include <memory>

enum class GameState {
    MAIN_MENU,
    POKEMON_SELECT,
    BATTLE,
    BATTLE_MENU,
    ATTACK_ANIMATION,
    BATTLE_RESULT
};

class SFMLGame {
private:
    // Core SFML components
    sf::RenderWindow window;
    sf::Font font;
    sf::Event event;
    
    // Game state
    GameState currentState;
    Game gameLogic;
    
    // Resources
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    
    // UI elements
    sf::RectangleShape menuBackground;
    sf::RectangleShape battleBackground;
    sf::RectangleShape selectBackground;
    std::vector<sf::Text> menuOptions;
    std::vector<sf::Text> pokemonOptions;
    std::vector<sf::Text> attackOptions;
    
    // Battle elements
    sf::Sprite playerPokemonSprite;
    sf::Sprite opponentPokemonSprite;
    sf::RectangleShape playerHealthBar;
    sf::RectangleShape opponentHealthBar;
    sf::Text battleText;
    sf::Text resultText;
    
    // Animation variables
    float animationTimer;
    bool animationPlaying;
    int selectedAttack;
    
    // Helper functions
    void loadResources();
    void handleEvents();
    void update(float deltaTime);
    void render();
    
    // State-specific functions
    void handleMainMenu();
    void handlePokemonSelect();
    void handleBattle();
    void handleBattleMenu();
    void handleAttackAnimation(float deltaTime);
    void handleBattleResult();
    
    void selectOption(int index);
    void startBattle();
    void executeAttack();
    void updateHealthBars();

public:
    SFMLGame();
    void run();
};

#endif