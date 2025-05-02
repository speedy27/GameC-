/*
 * Fichier : Pokemon.cpp
 * Auteurs : Florian & Adrien
 * Description : Implémentation de Pokemon
 */

#include "Pokemon.h"
#include <iostream>

Pokemon::Pokemon(const std::string& name, int hp, const Attack& attack)
    : name(name), hp(hp), attack(attack) {}

Pokemon::~Pokemon() {}

int Pokemon::getHP() const { return hp; }
const std::string& Pokemon::getName() const { return name; }
bool Pokemon::isFainted() const { return hp<=0; }
void Pokemon::receiveDamage(int dmg) {
    hp -= dmg; if (hp<0) hp=0;
}
void Pokemon::setTypes(const std::vector<Type>& typesList) { types = typesList; }
const std::vector<Type>& Pokemon::getTypes() const { return types; }
void Pokemon::interagir() {
    std::cout << name << " remue la queue !" << std::endl;
}
