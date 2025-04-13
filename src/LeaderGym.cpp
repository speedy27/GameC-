#include "LeaderGym.h"
#include <iostream>

LeaderGym::LeaderGym(const std::string& nom, const std::vector<std::string>& equipe, const std::string& specialiteType)
    : Entraineur(nom, equipe), specialiteType(specialiteType) {}

void LeaderGym::afficherInfos() const {
    std::cout << "===== Leader de Gymnase =====\n";
    std::cout << "Nom : " << nom << "\n";
    std::cout << "Spécialité : " << specialiteType << "\n";
    std::cout << "Équipe : ";
    for (const auto& pokemon : equipe) {
        std::cout << pokemon << " ";
    }
    std::cout << "\n";
}
