/*
 * Fichier : Tenedres.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Tenedres
 */

#ifndef TENEDRES_H
#define TENEDRES_H

#include "Pokemon.h"

/**
 * @class Tenedres
 * @brief Pokémon de type Tenedres.
 */
class Tenedres : public Pokemon {
public:
    Tenedres(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // TENEDRES_H
