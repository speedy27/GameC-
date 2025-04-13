#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entraineur.h"

// Classe Joueur qui hérite de Entraineur
class Joueur : public Entraineur {
public:
    // Constructeur
    Joueur(const std::string& nom, const std::vector<std::string>& equipe);

    // Méthode spécifique pour le joueur
    void afficherInfos() const;
};

#endif // JOUEUR_H
