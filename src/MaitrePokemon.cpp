#include "MaitrePokemon.h"
#include <iostream>

MaitrePokemon::MaitrePokemon(const std::string& nom, const std::vector<std::string>& equipe, int nombreTitres)
    : Entraineur(nom, equipe), nombreTitres(nombreTitres) {}

void MaitrePokemon::afficherInfos() const {
    std::cout << "===== Maître Pokémon =====\n";
    std::cout << "Nom : " << nom << "\n";
    std::cout << "Titres remportés : " << nombreTitres << "\n";
    std::cout << "Équipe : ";
    for (const auto& pokemon : equipe) {
        std::cout << pokemon << " ";
    }
    std::cout << "\n";
}

