#ifndef GAME_H
#define GAME_H

#include "Pokemon.h"
#include "Battle.h"
#include <vector>

class Game {
private:
    std::vector<Pokemon> availablePokemon;
    Pokemon* playerPokemon;
    Pokemon* opponentPokemon;

public:
    Game();
    ~Game();
    void initialize();
    void createPokemonList();
    void selectPlayerPokemon();
    void selectOpponentPokemon();
    void startBattle();
    void displayMenu();
    void run();
};

#endif