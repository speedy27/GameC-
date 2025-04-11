#include "Game.h"
#include <iostream>
#include <random>
#include <ctime>

Game::Game() : playerPokemon(nullptr), opponentPokemon(nullptr) {}

Game::~Game() {
    delete playerPokemon;
    delete opponentPokemon;
}

void Game::initialize() {
    std::cout << "==================================" << std::endl;
    std::cout << "   BIENVENUE DANS POKEMON C++    " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "\n";
    
    createPokemonList();
}

void Game::createPokemonList() {
    // Création des Pokémon disponibles avec leurs statistiques et attaques
    
    // Pokémon de type Feu
    Pokemon pikachu("Pikachu", "Electrik", 35, 55, 40, 90);
    pikachu.addAttack(Attack("Eclair", 40, 100, "Electrik"));
    pikachu.addAttack(Attack("Vive-Attaque", 40, 100, "Normal"));
    pikachu.addAttack(Attack("Tonnerre", 90, 100, "Electrik"));
    pikachu.addAttack(Attack("Fatal-Foudre", 110, 70, "Electrik"));
    availablePokemon.push_back(pikachu);
    
    Pokemon dracaufeu("Dracaufeu", "Feu", 78, 84, 78, 100);
    dracaufeu.addAttack(Attack("Lance-Flammes", 90, 100, "Feu"));
    dracaufeu.addAttack(Attack("Griffe", 40, 100, "Normal"));
    dracaufeu.addAttack(Attack("Cru-Aile", 60, 100, "Vol"));
    dracaufeu.addAttack(Attack("Déflagration", 110, 85, "Feu"));
    availablePokemon.push_back(dracaufeu);
    
    Pokemon florizarre("Florizarre", "Plante", 80, 82, 83, 80);
    florizarre.addAttack(Attack("Tranch'Herbe", 55, 95, "Plante"));
    florizarre.addAttack(Attack("Charge", 40, 100, "Normal"));
    florizarre.addAttack(Attack("Lance-Soleil", 120, 100, "Plante"));
    florizarre.addAttack(Attack("Poudre Toxik", 0, 90, "Poison"));
    availablePokemon.push_back(florizarre);
    
    Pokemon tortank("Tortank", "Eau", 79, 83, 100, 78);
    tortank.addAttack(Attack("Pistolet à O", 40, 100, "Eau"));
    tortank.addAttack(Attack("Hydrocanon", 110, 80, "Eau"));
    tortank.addAttack(Attack("Morsure", 60, 100, "Ténèbres"));
    tortank.addAttack(Attack("Surf", 90, 100, "Eau"));
    availablePokemon.push_back(tortank);
    
    Pokemon alakazam("Alakazam", "Psy", 55, 50, 45, 120);
    alakazam.addAttack(Attack("Psyko", 90, 100, "Psy"));
    alakazam.addAttack(Attack("Choc Mental", 50, 100, "Psy"));
    alakazam.addAttack(Attack("Ball'Ombre", 80, 100, "Spectre"));
    alakazam.addAttack(Attack("Tonnerre", 90, 100, "Electrik"));
    availablePokemon.push_back(alakazam);
    
    Pokemon ronflex("Ronflex", "Normal", 160, 110, 65, 30);
    ronflex.addAttack(Attack("Plaquage", 85, 100, "Normal"));
    ronflex.addAttack(Attack("Séisme", 100, 100, "Sol"));
    ronflex.addAttack(Attack("Poing-Glace", 75, 100, "Glace"));
    ronflex.addAttack(Attack("Repos", 0, 100, "Psy"));
    availablePokemon.push_back(ronflex);
}

void Game::selectPlayerPokemon() {
    std::cout << "Choisissez votre Pokémon:" << std::endl;
    for (size_t i = 0; i < availablePokemon.size(); ++i) {
        std::cout << i + 1 << ". " << availablePokemon[i].getName() 
                  << " (Type: " << availablePokemon[i].getType() 
                  << ", HP: " << availablePokemon[i].getHp() << ")" << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << availablePokemon.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(availablePokemon.size()));
    
    playerPokemon = new Pokemon(availablePokemon[choice - 1]);
    
    std::cout << "Vous avez choisi " << playerPokemon->getName() << "!" << std::endl;
    playerPokemon->displayAttacks();
    std::cout << "\n";
}

void Game::selectOpponentPokemon() {
    // Sélection aléatoire du Pokémon adverse
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, availablePokemon.size() - 1);
    
    int opponentIndex;
    do {
        opponentIndex = dist(gen);
    } while (playerPokemon && availablePokemon[opponentIndex].getName() == playerPokemon->getName());
    
    opponentPokemon = new Pokemon(availablePokemon[opponentIndex]);
    
    std::cout << "Un " << opponentPokemon->getName() << " sauvage apparaît!" << std::endl;
    std::cout << "\n";
}

void Game::startBattle() {
    Battle battle(playerPokemon, opponentPokemon);
    battle.start();
}

void Game::displayMenu() {
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "1. Commencer un combat" << std::endl;
    std::cout << "2. Quitter" << std::endl;
    std::cout << "Votre choix: ";
}

void Game::run() {
    initialize();
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                delete playerPokemon;
                delete opponentPokemon;
                playerPokemon = nullptr;
                opponentPokemon = nullptr;
                
                selectPlayerPokemon();
                selectOpponentPokemon();
                startBattle();
                break;
                
            case 2:
                std::cout << "Merci d'avoir joué! À bientôt!" << std::endl;
                running = false;
                break;
                
            default:
                std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    }
}