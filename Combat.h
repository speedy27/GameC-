/*
 * Fichier : Combat.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Combat
 */

#ifndef COMBAT_H
#define COMBAT_H

#include "Pokemon.h"

/**
 * @class Combat
 * @brief Pokémon de type Combat.
 */
class Combat : public Pokemon {
public:
    Combat(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // COMBAT_H
