#ifndef LEADERGYM_H
#define LEADERGYM_H

#include "Entraineur.h"

// Classe LeaderGym qui hérite de Entraineur
class LeaderGym : public Entraineur {
private:
    std::string specialiteType; // Type de spécialité du leader

public:
    // Constructeur
    LeaderGym(const std::string& nom, const std::vector<std::string>& equipe, const std::string& specialiteType);

    // Affichage spécifique pour le leader de gym
    void afficherInfos() const;
};

#endif // LEADERGYM_H
