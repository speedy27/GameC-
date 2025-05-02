/*
 * Fichier : Electrik.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Electrik
 */

#ifndef ELECTRIK_H
#define ELECTRIK_H

#include "Pokemon.h"

/**
 * @class Electrik
 * @brief Pokémon de type Electrik.
 */
class Electrik : public Pokemon {
public:
    Electrik(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // ELECTRIK_H
