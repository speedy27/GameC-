/*
 * Fichier : Spectre.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Spectre
 */

#ifndef SPECTRE_H
#define SPECTRE_H

#include "Pokemon.h"

/**
 * @class Spectre
 * @brief Pokémon de type Spectre.
 */
class Spectre : public Pokemon {
public:
    Spectre(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // SPECTRE_H
