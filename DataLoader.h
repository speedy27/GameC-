/*
 * Fichier : DataLoader.h
 * Auteurs : Florian & Adrien
 * Description : Déclaration de DataLoader
 */

#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include <string>
#include "Pokemon.h"
#include "Entraineur.h"
#include "LeaderGym.h"
#include "MaitrePokemon.h"

class DataLoader {
public:
    static std::vector<Pokemon*> loadPokemons(const std::string& file);
    static std::vector<Entraineur*> loadLeaders(const std::string& file, const std::vector<Pokemon*>& templates);
    static std::vector<MaitrePokemon*> loadMaitres(const std::string& file, const std::vector<Pokemon*>& templates);
};

#endif // DATALOADER_H
