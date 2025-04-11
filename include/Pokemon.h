#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <iostream>

class Attack {
private:
    std::string name;
    int power;
    int accuracy;
    std::string type;

public:
    Attack(const std::string& name, int power, int accuracy, const std::string& type);
    std::string getName() const;
    int getPower() const;
    int getAccuracy() const;
    std::string getType() const;
};

class Pokemon {
private:
    std::string name;
    std::string type;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    std::vector<Attack> attacks;

public:
    Pokemon(const std::string& name, const std::string& type, int hp, int attack, int defense, int speed);
    void addAttack(const Attack& attack);
    std::string getName() const;
    std::string getType() const;
    int getHp() const;
    int getMaxHp() const;
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;
    std::vector<Attack> getAttacks() const;
    void takeDamage(int damage);
    bool isKO() const;
    void displayStatus() const;
    void displayAttacks() const;
};

// Type effectiveness calculation
float getTypeEffectiveness(const std::string& attackType, const std::string& defenderType);

#endif