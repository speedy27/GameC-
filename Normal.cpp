/*
 * Fichier : Normal.cpp
 * Auteurs : Florian & Adrien
 * Description : Implémentation de Normal
 */

#include "Normal.h"
#include <iostream>

Normal::Normal(const std::string& name, int hp, const Attack& attack)
    : Pokemon(name, hp, attack) { types = { Type::Normal }; }

void Normal::attaquer(Pokemon& cible) {
    double mult=1.0;
    for(auto& tt: cible.getTypes()) mult*=getEffectiveness(attack.getType(), tt);
    int dmg=int(attack.getPower()*mult);
    std::cout<< name << " utilise " << attack.getName()
             << " et inflige " << dmg << " dégâts";
    if(mult>1.0) std::cout<<" (super efficace)";
    else if(mult<1.0) std::cout<<" (peu efficace)";
    std::cout<<" à "<<cible.getName()<<"!"<<std::endl;
    cible.receiveDamage(dmg);
}

Pokemon* Normal::clone() const { return new Normal(*this); }
