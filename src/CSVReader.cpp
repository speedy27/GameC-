#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// Fonction utilitaire pour nettoyer les espaces
std::string nettoyer(const std::string& str) {
    std::string nettoye;
    for (char c : str) {
        if (!isspace(static_cast<unsigned char>(c))) nettoye += c;
    }
    return nettoye;
}

// Lecture CSV générique
std::vector<std::map<std::string, std::string>> CSVReader::lireCSV(const std::string& cheminFichier) {
    std::vector<std::map<std::string, std::string>> donnees;
    fs::path cheminAbsolu = fs::current_path() / cheminFichier;
    std::ifstream fichier(cheminAbsolu);

    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier CSV : " << cheminAbsolu << std::endl;
        return donnees;
    }

    std::string ligne, cellule;
    std::vector<std::string> enTetes;

    // Lecture des entêtes
    if (std::getline(fichier, ligne)) {
        std::stringstream streamLigne(ligne);
        while (std::getline(streamLigne, cellule, ',')) {
            enTetes.push_back(nettoyer(cellule));
        }
    }

    // Lecture des lignes
    while (std::getline(fichier, ligne)) {
        std::stringstream streamLigne(ligne);
        std::map<std::string, std::string> ligneMap;
        size_t index = 0;

        while (std::getline(streamLigne, cellule, ',')) {
            if (index < enTetes.size()) {
                ligneMap[enTetes[index]] = nettoyer(cellule);
            }
            ++index;
        }

        if (!ligneMap.empty()) {
            donnees.push_back(ligneMap);
        }
    }

    return donnees;
}

// Charger les Pokémon depuis le CSV
std::vector<std::unique_ptr<Pokemon>> CSVReader::chargerPokemons(const std::string& cheminFichier) {
    auto lignes = lireCSV(cheminFichier);
    std::vector<std::unique_ptr<Pokemon>> pokemons;

    for (const auto& ligne : lignes) {
        try {
            std::string nom = ligne.at("Nom");
            std::string type = ligne.at("Type");
            int hp = std::stoi(ligne.at("PV"));
            std::string imageFront = ligne.at("ImageFront");
            std::string imageBack = ligne.at("ImageBack");

            std::vector<Attaque> attaques;
            for (int i = 1; i <= 4; ++i) {
                std::string nomAttaque = "Attaque" + std::to_string(i);
                std::string puissanceAttaque = "Puissance" + std::to_string(i);
                if (ligne.count(nomAttaque) && ligne.count(puissanceAttaque)) {
                    attaques.push_back({ ligne.at(nomAttaque), std::stoi(ligne.at(puissanceAttaque)) });
                }
            }

            // Création du Pokémon selon le type
            if (type == "Feu") {
                pokemons.push_back(std::make_unique<PokemonFeu>(nom, type, hp, attaques, imageFront, imageBack));
            } else if (type == "Eau") {
                pokemons.push_back(std::make_unique<PokemonEau>(nom, type, hp, attaques, imageFront, imageBack));
            } else if (type == "Plante") {
                pokemons.push_back(std::make_unique<PokemonPlante>(nom, type, hp, attaques, imageFront, imageBack));
            } else if (type == "Electrik") {
                pokemons.push_back(std::make_unique<PokemonElectrik>(nom, type, hp, attaques, imageFront, imageBack));
            } else if (type == "Psy") {
                pokemons.push_back(std::make_unique<PokemonPsy>(nom, type, hp, attaques, imageFront, imageBack));
            } else {
                pokemons.push_back(std::make_unique<PokemonNormal>(nom, type, hp, attaques, imageFront, imageBack));
            }

        } catch (const std::exception& e) {
            std::cerr << "Erreur lors du chargement d'un Pokémon : " << e.what() << std::endl;
        }
    }

    return pokemons;
}

// Charger l'équipe depuis le CSV
std::vector<std::string> CSVReader::chargerEquipe(const std::string& cheminFichier) {
    auto lignes = lireCSV(cheminFichier);
    std::vector<std::string> equipe;

    for (const auto& ligne : lignes) {
        try {
            equipe.push_back(ligne.at("NomPokemon"));
        } catch (const std::out_of_range& e) {
            std::cerr << "Erreur : colonne 'NomPokemon' manquante dans le fichier : " << cheminFichier << std::endl;
        }
    }

    return equipe;
}
