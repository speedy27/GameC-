/*
 * Fichier : Sol.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Sol
 */

#ifndef SOL_H
#define SOL_H

#include "Pokemon.h"

/**
 * @class Sol
 * @brief Pokémon de type Sol.
 */
class Sol : public Pokemon {
public:
    Sol(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // SOL_H
