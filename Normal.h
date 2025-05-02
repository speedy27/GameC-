/*
 * Fichier : Normal.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Normal
 */

#ifndef NORMAL_H
#define NORMAL_H

#include "Pokemon.h"

/**
 * @class Normal
 * @brief Pokémon de type Normal.
 */
class Normal : public Pokemon {
public:
    Normal(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // NORMAL_H
