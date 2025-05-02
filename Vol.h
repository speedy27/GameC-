/*
 * Fichier : Vol.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Vol
 */

#ifndef VOL_H
#define VOL_H

#include "Pokemon.h"

/**
 * @class Vol
 * @brief Pokémon de type Vol.
 */
class Vol : public Pokemon {
public:
    Vol(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // VOL_H
