#include "Entraineur.h"
#include <iostream>

Entraineur::Entraineur(const std::string& nom, const std::vector<std::string>& equipe)
    : nom(nom), equipe(equipe) {}

std::string Entraineur::getNom() const {
    return nom;
}

const std::vector<std::string>& Entraineur::getEquipe() const {
    return equipe;
}

void Entraineur::afficherInfos() const {
    std::cout << "Entraîneur : " << nom << "\n";
    std::cout << "Équipe : ";
    for (const auto& pokemon : equipe) {
        std::cout << pokemon << " ";
    }
    std::cout << "\n";
}
