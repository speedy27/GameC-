/*
 * Fichier : Attack.cpp
 * Auteurs : Florian & Adrien
 * Description : Implémentation de la classe Attack
 */

#include "Attack.h"

Attack::Attack(const std::string& name, Type type, int power)
    : name(name), type(type), power(power) {}

const std::string& Attack::getName() const { return name; }
Type Attack::getType() const { return type; }
int Attack::getPower() const { return power; }
