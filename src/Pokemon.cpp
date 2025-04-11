#include "Pokemon.h"
#include <iostream>
#include <map>
#include <cmath>

Attack::Attack(const std::string& name, int power, int accuracy, const std::string& type)
    : name(name), power(power), accuracy(accuracy), type(type) {}

std::string Attack::getName() const { return name; }
int Attack::getPower() const { return power; }
int Attack::getAccuracy() const { return accuracy; }
std::string Attack::getType() const { return type; }

Pokemon::Pokemon(const std::string& name, const std::string& type, int hp, int attack, int defense, int speed)
    : name(name), type(type), hp(hp), maxHp(hp), attack(attack), defense(defense), speed(speed) {}

void Pokemon::addAttack(const Attack& attack) {
    if (attacks.size() < 4) {
        attacks.push_back(attack);
    } else {
        std::cout << "Un Pokémon ne peut pas avoir plus de 4 attaques!" << std::endl;
    }
}

std::string Pokemon::getName() const { return name; }
std::string Pokemon::getType() const { return type; }
int Pokemon::getHp() const { return hp; }
int Pokemon::getMaxHp() const { return maxHp; }
int Pokemon::getAttack() const { return attack; }
int Pokemon::getDefense() const { return defense; }
int Pokemon::getSpeed() const { return speed; }
std::vector<Attack> Pokemon::getAttacks() const { return attacks; }

void Pokemon::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

bool Pokemon::isKO() const {
    return hp <= 0;
}

void Pokemon::displayStatus() const {
    std::cout << name << " (" << type << ") - HP: " << hp << "/" << maxHp << std::endl;
}

void Pokemon::displayAttacks() const {
    std::cout << "Attaques de " << name << ":" << std::endl;
    for (size_t i = 0; i < attacks.size(); ++i) {
        std::cout << i + 1 << ". " << attacks[i].getName() 
                  << " (Puissance: " << attacks[i].getPower() 
                  << ", Précision: " << attacks[i].getAccuracy() 
                  << ", Type: " << attacks[i].getType() << ")" << std::endl;
    }
}

float getTypeEffectiveness(const std::string& attackType, const std::string& defenderType) {
    // Table simplifiée des efficacités de type
    std::map<std::string, std::map<std::string, float>> typeChart;
    
    // Super efficace (x2)
    typeChart["Feu"]["Plante"] = 2.0f;
    typeChart["Feu"]["Insecte"] = 2.0f;
    typeChart["Eau"]["Feu"] = 2.0f;
    typeChart["Eau"]["Sol"] = 2.0f;
    typeChart["Plante"]["Eau"] = 2.0f;
    typeChart["Plante"]["Sol"] = 2.0f;
    typeChart["Electrik"]["Eau"] = 2.0f;
    typeChart["Electrik"]["Vol"] = 2.0f;
    typeChart["Psy"]["Combat"] = 2.0f;
    typeChart["Psy"]["Poison"] = 2.0f;
    
    // Pas très efficace (x0.5)
    typeChart["Feu"]["Eau"] = 0.5f;
    typeChart["Feu"]["Roche"] = 0.5f;
    typeChart["Eau"]["Plante"] = 0.5f;
    typeChart["Eau"]["Electrik"] = 0.5f;
    typeChart["Plante"]["Feu"] = 0.5f;
    typeChart["Plante"]["Poison"] = 0.5f;
    typeChart["Plante"]["Vol"] = 0.5f;
    typeChart["Electrik"]["Plante"] = 0.5f;
    typeChart["Electrik"]["Sol"] = 0.0f; // Immunité
    
    if (typeChart.count(attackType) > 0 && typeChart[attackType].count(defenderType) > 0) {
        return typeChart[attackType][defenderType];
    }
    
    return 1.0f; // Efficacité normale par défaut
}