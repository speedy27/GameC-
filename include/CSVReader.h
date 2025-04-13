#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Pokemon.h"

class CSVReader {
public:
    // Lit un fichier CSV générique et retourne un vecteur de maps (colonnes -> valeurs)
    static std::vector<std::map<std::string, std::string>> lireCSV(const std::string& cheminFichier);

    // Charge la liste des Pokémon depuis le CSV
    static std::vector<std::unique_ptr<Pokemon>> chargerPokemons(const std::string& cheminFichier);

    // Charge la liste des noms des Pokémon de l'équipe joueur depuis le CSV d'équipe
    static std::vector<std::string> chargerEquipe(const std::string& cheminFichier);
};

#endif // CSVREADER_H
