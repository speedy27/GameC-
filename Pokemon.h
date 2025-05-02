/*
 * Fichier : Pokemon.h
 * Auteurs : Florian & Adrien
 * Description : Classe abstraite Pokemon
 */

#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "Attack.h"
#include "Interagir.h"
#include "Type.h"

static inline double getEffectiveness(Type atk, Type tgt) {
    if (atk==Type::Feu && tgt==Type::Plante) return 2.0;
    if (atk==Type::Eau && tgt==Type::Feu) return 2.0;
    if (atk==Type::Plante && tgt==Type::Eau) return 2.0;
    return 1.0;
}

/**
 * @class Pokemon
 * @brief Classe abstraite représentant un Pokémon.
 */
class Pokemon : public Interagir {
public:
    Pokemon(const std::string& name, int hp, const Attack& attack);
    virtual ~Pokemon();
    virtual void attaquer(Pokemon& cible) = 0;
    int getHP() const;
    const std::string& getName() const;
    bool isFainted() const;
    void receiveDamage(int dmg);
    void setTypes(const std::vector<Type>& typesList);
    const std::vector<Type>& getTypes() const;
    virtual Pokemon* clone() const = 0;
    void interagir() override;
protected:
    std::string name;
    int hp;
    Attack attack;
    std::vector<Type> types;
};

#endif // POKEMON_H
