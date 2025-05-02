/*
 * Fichier : Glace.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Glace
 */

#ifndef GLACE_H
#define GLACE_H

#include "Pokemon.h"

/**
 * @class Glace
 * @brief Pokémon de type Glace.
 */
class Glace : public Pokemon {
public:
    Glace(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // GLACE_H
