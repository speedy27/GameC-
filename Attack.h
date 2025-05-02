/*
 * Fichier : Attack.h
 * Auteurs : Florian & Adrien
 * Description : Déclaration de la classe Attack
 */

#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include "Type.h"

/**
 * @class Attack
 * @brief Représente une attaque Pokémon.
 */
class Attack {
public:
    Attack(const std::string& name = "", Type type = Type::Normal, int power = 0);
    const std::string& getName() const;
    Type getType() const;
    int getPower() const;
private:
    std::string name;
    Type type;
    int power;
};

#endif // ATTACK_H
