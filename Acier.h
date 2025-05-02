/*
 * Fichier : Acier.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Acier
 */

#ifndef ACIER_H
#define ACIER_H

#include "Pokemon.h"

/**
 * @class Acier
 * @brief Pokémon de type Acier.
 */
class Acier : public Pokemon {
public:
    Acier(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // ACIER_H
