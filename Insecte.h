/*
 * Fichier : Insecte.h
 * Auteurs : Florian & Adrien
 * Description : Sous-classe Insecte
 */

#ifndef INSECTE_H
#define INSECTE_H

#include "Pokemon.h"

/**
 * @class Insecte
 * @brief Pokémon de type Insecte.
 */
class Insecte : public Pokemon {
public:
    Insecte(const std::string& name, int hp, const Attack& attack);
    void attaquer(Pokemon& cible) override;
    Pokemon* clone() const override;
};

#endif // INSECTE_H
