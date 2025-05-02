/*
 * Fichier : Fee.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Fee
 */

#ifndef FEE_H
#define FEE_H

#include "Pokemon.h"

/**
 * @class Fee
 * @brief Pokémon de type Fee.
 */
class Fee : public Pokemon {
public:
    Fee(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // FEE_H
