/*
 * Fichier : Feu.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Feu
 */

#ifndef FEU_H
#define FEU_H

#include "Pokemon.h"

/**
 * @class Feu
 * @brief Pokémon de type Feu.
 */
class Feu : public Pokemon {
public:
    Feu(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // FEU_H
