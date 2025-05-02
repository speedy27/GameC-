/*
 * Fichier : Psy.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Psy
 */

#ifndef PSY_H
#define PSY_H

#include "Pokemon.h"

/**
 * @class Psy
 * @brief Pokémon de type Psy.
 */
class Psy : public Pokemon {
public:
    Psy(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // PSY_H
