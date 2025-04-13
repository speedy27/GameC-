#ifndef SFMLGAME_H
#define SFMLGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Battle.h"
#include <memory>
#include <vector>

class SFMLGame {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::Text messageCombat;

    sf::RectangleShape fondAttaques;
    sf::Music musique;

    Game jeu;
    std::unique_ptr<Battle> combat;
    std::unique_ptr<Pokemon> joueurPokemon;
    std::unique_ptr<Pokemon> adversairePokemon;

    std::vector<sf::Text> menuPrincipal;
    std::vector<sf::Text> boutonsAttaques;
    std::vector<Attaque> attaques;

    enum class Etat {
        Menu,
        Combat
    } etatActuel;

    // Initialisations
    void initialiserMenu();
    void initialiserCombat();
    void initialiserUI();

    // Interface utilisateur
    void afficherMenuPrincipal();
    void afficherCombat();
    void afficherMessage(const std::string& message, float x, float y);
    void afficherEquipeConsole();

    // Logique de combat
    void mettreAJourBoutonsAttaque();

    // Dessin global
    void dessiner();

public:
    SFMLGame();
    void runGame();
};

#endif // SFMLGAME_H
