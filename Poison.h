/*
 * Fichier : Poison.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Poison
 */

#ifndef POISON_H
#define POISON_H

#include "Pokemon.h"

/**
 * @class Poison
 * @brief Pokémon de type Poison.
 */
class Poison : public Pokemon {
public:
    Poison(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // POISON_H
