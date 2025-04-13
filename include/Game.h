#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include "Pokemon.h"
#include "Battle.h"
#include "CSVReader.h"

class Game {
private:
    std::vector<std::unique_ptr<Pokemon>> tousLesPokemons;
    std::vector<std::string> equipeJoueur; // <<--- NOM CORRECT !

public:
    Game();

    void initialiserJeu();

    void afficherEquipe() const;

    std::unique_ptr<Pokemon> choisirPokemon(const std::string& nom) const;

    std::unique_ptr<Pokemon> choisirAdversaire() const;

    const std::vector<std::string>& getEquipeJoueur() const;

    std::unique_ptr<Battle> creerCombat(std::unique_ptr<Pokemon> joueur, std::unique_ptr<Pokemon> adversaire);
};

#endif // GAME_H
