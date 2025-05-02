#include "Joueur.h"
#include <iostream>

Joueur::Joueur(const std::string& name)
    : Entraineur(name), badges(0), wins(0), losses(0) {}

int Joueur::getBadges() const { return badges; }
int Joueur::getWins() const { return wins; }
int Joueur::getLosses() const { return losses; }

void Joueur::gainBadge() { ++badges; }
void Joueur::addWin()   { ++wins; }
void Joueur::addLoss()  { ++losses; }

void Joueur::interagir() {
    std::cout << "Salut " << name << "! Prêt pour un nouveau défi?" << std::endl;
}


void Joueur::addDefeatedTrainer(Entraineur* e) {
    defeatedTrainers.push_back(e);
}

const std::vector<Entraineur*>& Joueur::getDefeatedTrainers() const {
    return defeatedTrainers;
}
