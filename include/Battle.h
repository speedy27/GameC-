#ifndef BATTLE_H
#define BATTLE_H

#include "Pokemon.h"
#include <random>

class Battle {
private:
    Pokemon* player;
    Pokemon* opponent;
    std::mt19937 rng;

public:
    Battle(Pokemon* player, Pokemon* opponent);
    void start();
    bool playerTurn();
    bool opponentTurn();
    int calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Attack& attack);
    bool checkAccuracy(const Attack& attack);
};

#endif