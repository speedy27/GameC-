#ifndef COMBATENGINE_H
#define COMBATENGINE_H

#include "Joueur.h"
#include "Entraineur.h"

/**
 * Moteur de combat
 */
class CombatEngine {
public:
    static bool battle(Joueur& joueur, Entraineur& ennemi);
};

#endif // COMBATENGINE_H
