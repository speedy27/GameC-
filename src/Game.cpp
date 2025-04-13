#include "Game.h"
#include <iostream>
#include <random>

Game::Game() {}

void Game::initialiserJeu() {
    CSVReader reader;
    tousLesPokemons = reader.chargerPokemons("data/pokemon.csv");
    equipeJoueur = reader.chargerEquipe("data/joueur.csv");
}

void Game::afficherEquipe() const {
    std::cout << "Votre équipe :\n";
    for (const auto& nom : equipeJoueur) { // <<--- NOM CORRECT !
        std::cout << "- " << nom << "\n";
    }
}

std::unique_ptr<Pokemon> Game::choisirPokemon(const std::string& nom) const {
    for (const auto& p : tousLesPokemons) { // <<--- NOM CORRECT !
        if (p->getNom() == nom) {
            return p->clone();
        }
    }
    return nullptr;
}

std::unique_ptr<Pokemon> Game::choisirAdversaire() const {
    if (tousLesPokemons.empty()) return nullptr;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tousLesPokemons.size() - 1); // <<--- NOM CORRECT !

    return tousLesPokemons[dis(gen)]->clone();
}

const std::vector<std::string>& Game::getEquipeJoueur() const {
    return equipeJoueur; // <<--- NOM CORRECT !
}

std::unique_ptr<Battle> Game::creerCombat(std::unique_ptr<Pokemon> joueur, std::unique_ptr<Pokemon> adversaire) {
    return std::make_unique<Battle>(std::move(joueur), std::move(adversaire));
}
