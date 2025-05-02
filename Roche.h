/*
 * Fichier : Roche.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Roche
 */

#ifndef ROCHE_H
#define ROCHE_H

#include "Pokemon.h"

/**
 * @class Roche
 * @brief Pokémon de type Roche.
 */
class Roche : public Pokemon {
public:
    Roche(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // ROCHE_H
