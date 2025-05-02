/*
 * Fichier : Eau.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Eau
 */

#ifndef EAU_H
#define EAU_H

#include "Pokemon.h"

/**
 * @class Eau
 * @brief Pokémon de type Eau.
 */
class Eau : public Pokemon {
public:
    Eau(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // EAU_H
