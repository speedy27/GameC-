#ifndef ENTRAINEUR_H
#define ENTRAINEUR_H

#include <string>
#include <vector>

class Entraineur {
protected:
    std::string nom;
    std::vector<std::string> equipe;

public:
    // Constructeur
    Entraineur(const std::string& nom, const std::vector<std::string>& equipe);

    // Accesseurs
    std::string getNom() const;
    const std::vector<std::string>& getEquipe() const;

    // Afficher les infos de l'entraîneur
    void afficherInfos() const;
};

#endif // ENTRAINEUR_H
