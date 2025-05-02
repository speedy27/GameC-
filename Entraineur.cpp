#include "Entraineur.h"
#include <iostream>

Entraineur::Entraineur(const std::string& name)
    : name(name), current(0) {}

Entraineur::~Entraineur() {
    for (auto p : equipe) delete p;
}

void Entraineur::addPokemon(Pokemon* p) {
    if (equipe.size() < 6) equipe.push_back(p);
}

bool Entraineur::hasPokemon() const {
    for (auto p : equipe) if (!p->isFainted()) return true;
    return false;
}

Pokemon* Entraineur::getCurrentPokemon() {
    if (current < equipe.size()) return equipe[current];
    return nullptr;
}

void Entraineur::nextPokemon() {
    while (current < equipe.size() && equipe[current]->isFainted()) {
        ++current;
    }
}

const std::string& Entraineur::getName() const {
    return name;
}

void Entraineur::interagir() {
    std::cout << "Entraineur " << name << " vous salue." << std::endl;
}
