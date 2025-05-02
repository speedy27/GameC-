/*
 * Fichier : Plante.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Plante
 */

#ifndef PLANTE_H
#define PLANTE_H

#include "Pokemon.h"

/**
 * @class Plante
 * @brief Pokémon de type Plante.
 */
class Plante : public Pokemon {
public:
    Plante(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // PLANTE_H
