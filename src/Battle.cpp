#include "Battle.h"
#include <sstream>
#include <iostream>

Battle::Battle(std::unique_ptr<Pokemon> p1, std::unique_ptr<Pokemon> p2)
    : pokemon1(std::move(p1)), pokemon2(std::move(p2)) {}

// Vérifie si le combat est terminé
bool Battle::estCombatFini() const {
    return pokemon1->estKO() || pokemon2->estKO();
}

// Effectue l'attaque du joueur et gère la riposte de l'adversaire
std::string Battle::effectuerAttaqueJoueur(const Attaque& attaqueJoueur) {
    std::ostringstream resultat;

    // Attaque du joueur
    int degats = pokemon2->subirDegats(attaqueJoueur.puissance);
    resultat << pokemon1->getNom() << " utilise " << attaqueJoueur.nom
             << " et inflige " << degats << " dégâts à " << pokemon2->getNom() << "!\n";

    if (pokemon2->estKO()) {
        resultat << pokemon2->getNom() << " est K.O. !\n";
        return resultat.str();
    }

    // Riposte de l'adversaire
    Attaque attaqueAdverse = pokemon2->choisirAttaqueAleatoire();
    int degatsRiposte = pokemon1->subirDegats(attaqueAdverse.puissance);

    resultat << pokemon2->getNom() << " riposte avec " << attaqueAdverse.nom
             << " et inflige " << degatsRiposte << " dégâts à " << pokemon1->getNom() << "!\n";

    if (pokemon1->estKO()) {
        resultat << pokemon1->getNom() << " est K.O. !\n";
    }

    return resultat.str();
}

// Dessine le combat dans la fenêtre SFML
void Battle::dessinerCombat(sf::RenderWindow& window, sf::Font& font) const {
    // Pokémon du joueur
    sf::Texture textureJoueur;
    if (textureJoueur.loadFromFile("resources/images/" + pokemon1->getImageBack())) {
        sf::Sprite spriteJoueur(textureJoueur);
        spriteJoueur.setPosition(100, 400);
        window.draw(spriteJoueur);
    }

    // Pokémon adverse
    sf::Texture textureAdversaire;
    if (textureAdversaire.loadFromFile("resources/images/" + pokemon2->getImageFront())) {
        sf::Sprite spriteAdversaire(textureAdversaire);
        spriteAdversaire.setPosition(700, 100);
        window.draw(spriteAdversaire);
    }

    // Fonction locale pour dessiner les barres de PV
    auto dessinerBarrePV = [&](int pv, int pvMax, float x, float y) {
        sf::RectangleShape fondBarre(sf::Vector2f(200, 20));
        fondBarre.setFillColor(sf::Color(50, 50, 50));
        fondBarre.setPosition(x, y);
        window.draw(fondBarre);

        float ratio = static_cast<float>(pv) / pvMax;
        sf::RectangleShape barrePV(sf::Vector2f(200 * ratio, 20));

        if (ratio > 0.5f)
            barrePV.setFillColor(sf::Color::Green);
        else if (ratio > 0.3f)
            barrePV.setFillColor(sf::Color::Yellow);
        else
            barrePV.setFillColor(sf::Color::Red);

        barrePV.setPosition(x, y);
        window.draw(barrePV);
    };

    dessinerBarrePV(pokemon1->getPV(), pokemon1->getPVMax(), 100, 370);
    dessinerBarrePV(pokemon2->getPV(), pokemon2->getPVMax(), 700, 70);

    // Fonction locale pour afficher les infos des Pokémon
    auto afficherInfos = [&](const Pokemon& pokemon, float x, float y) {
        sf::Text infos;
        infos.setFont(font);
        infos.setCharacterSize(20);
        infos.setFillColor(sf::Color::White);

        std::ostringstream oss;
        oss << pokemon.getNom() << " (" << pokemon.getPV() << " PV)";
        infos.setString(oss.str());
        infos.setPosition(x, y);

        window.draw(infos);
    };

    afficherInfos(*pokemon1, 100, 340);
    afficherInfos(*pokemon2, 700, 40);
}
