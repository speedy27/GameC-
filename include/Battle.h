#ifndef BATTLE_H
#define BATTLE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Pokemon.h"

// Classe Battle : gère un combat entre deux Pokémon
class Battle {
private:
    std::unique_ptr<Pokemon> pokemon1;
    std::unique_ptr<Pokemon> pokemon2;

public:
    // Constructeur
    Battle(std::unique_ptr<Pokemon> p1, std::unique_ptr<Pokemon> p2);

    // Vérifie si le combat est terminé
    bool estCombatFini() const;

    // Accesseurs pour les Pokémon du combat
    const Pokemon* getPokemonJoueur() const { return pokemon1.get(); }
    const Pokemon* getPokemonAdversaire() const { return pokemon2.get(); }

    // Gère l'attaque du joueur et la riposte de l'adversaire
    std::string effectuerAttaqueJoueur(const Attaque& attaqueJoueur);

    // Dessine le combat dans la fenêtre SFML
    void dessinerCombat(sf::RenderWindow& window, sf::Font& font) const;
};

#endif // BATTLE_H
