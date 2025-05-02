/*
 * Fichier : Dragon.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Dragon
 */

#ifndef DRAGON_H
#define DRAGON_H

#include "Pokemon.h"

/**
 * @class Dragon
 * @brief Pokémon de type Dragon.
 */
class Dragon : public Pokemon {
public:
    Dragon(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // DRAGON_H
