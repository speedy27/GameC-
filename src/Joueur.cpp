#include "Joueur.h"
#include <iostream>

Joueur::Joueur(const std::string& nom, const std::vector<std::string>& equipe)
    : Entraineur(nom, equipe) {}

void Joueur::afficherInfos() const {
    std::cout << "===== Joueur =====\n";
    std::cout << "Nom : " << nom << "\n";
    std::cout << "Équipe : ";
    for (const auto& pokemon : equipe) {
        std::cout << pokemon << " ";
    }
    std::cout << "\n";
}
