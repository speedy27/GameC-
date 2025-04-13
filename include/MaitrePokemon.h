#ifndef MAITREPOKEMON_H
#define MAITREPOKEMON_H

#include "Entraineur.h"

// Classe MaitrePokemon qui hérite de Entraineur
class MaitrePokemon : public Entraineur {
private:
    int nombreTitres; // Nombre de titres de Maître Pokémon

public:
    // Constructeur
    MaitrePokemon(const std::string& nom, const std::vector<std::string>& equipe, int nombreTitres);

    // Affichage spécifique pour le Maître Pokémon
    void afficherInfos() const;
};

#endif // MAITREPOKEMON_H
