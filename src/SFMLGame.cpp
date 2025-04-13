#include "SFMLGame.h"
#include <iostream>
#include <sstream>

SFMLGame::SFMLGame()
    : window(sf::VideoMode(1200, 800), "Pokemon C++ - Combat Graphique") {

    if (!font.loadFromFile("resources/fonts/Pokemon.ttf")) {
        std::cerr << "Erreur lors du chargement de la police Pokemon.ttf\n";
    }

    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);

    messageCombat.setFont(font);
    messageCombat.setCharacterSize(24);
    messageCombat.setFillColor(sf::Color::White);
    messageCombat.setPosition(50, 700);

    fondAttaques.setSize(sf::Vector2f(400, 300));
    fondAttaques.setFillColor(sf::Color(0, 0, 0, 150));
    fondAttaques.setPosition(30, 480);

    if (!musique.openFromFile("resources/sounds/victory.wav")) {
        std::cerr << "Erreur lors du chargement de la musique\n";
    } else {
        musique.setLoop(true);
        musique.play();
    }

    initialiserMenu();
}

void SFMLGame::initialiserMenu() {
    menuPrincipal.clear();

    const std::vector<std::string> options = {
        "Afficher mon equipe",
        "Lancer un combat",
        "Quitter le jeu"
    };

    int y = 200;
    for (const auto& option : options) {
        sf::Text menuOption;
        menuOption.setFont(font);
        menuOption.setCharacterSize(40);
        menuOption.setFillColor(sf::Color::Yellow);
        menuOption.setString(option);
        menuOption.setPosition(400, y);
        menuPrincipal.push_back(menuOption);
        y += 100;
    }

    etatActuel = Etat::Menu;
}

void SFMLGame::initialiserCombat() {
    jeu.initialiserJeu();

    auto equipeJoueur = jeu.getEquipeJoueur();
    if (!equipeJoueur.empty()) {
        joueurPokemon = jeu.choisirPokemon(equipeJoueur[0]);
    }

    adversairePokemon = jeu.choisirAdversaire();

    if (!joueurPokemon || !adversairePokemon) {
        messageCombat.setString("Erreur d'initialisation du combat !");
        return;
    }

    combat = jeu.creerCombat(joueurPokemon->clone(), adversairePokemon->clone());
    mettreAJourBoutonsAttaque();
    etatActuel = Etat::Combat;
}

void SFMLGame::mettreAJourBoutonsAttaque() {
    boutonsAttaques.clear();
    attaques.clear();

    if (!combat) return;

    int y = 500;
    for (const auto& attaque : combat->getPokemonJoueur()->getAttaques()) {
        sf::Text bouton;
        bouton.setFont(font);
        bouton.setCharacterSize(25);
        bouton.setString(attaque.nom + " (Puissance: " + std::to_string(attaque.puissance) + ")");
        bouton.setPosition(50, y);
        bouton.setFillColor(sf::Color::White);

        boutonsAttaques.push_back(bouton);
        attaques.push_back(attaque);
        y += 60;
    }
}

void SFMLGame::runGame() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (etatActuel == Etat::Menu && event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                if (x >= 400 && x <= 800) {
                    if (y >= 200 && y <= 240) {
                        jeu.initialiserJeu();
                        afficherEquipeConsole();
                    } else if (y >= 300 && y <= 340) {
                        initialiserCombat();
                    } else if (y >= 400 && y <= 440) {
                        window.close();
                    }
                }
            } else if (etatActuel == Etat::Combat && event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                for (size_t i = 0; i < boutonsAttaques.size(); ++i) {
                    auto bounds = boutonsAttaques[i].getGlobalBounds();
                    if (bounds.contains(x, y)) {
                        std::string resultat = combat->effectuerAttaqueJoueur(attaques[i]);
                        messageCombat.setString(resultat);
                        mettreAJourBoutonsAttaque();
                        break;
                    }
                }
            }
        }

        dessiner();
    }
}

void SFMLGame::dessiner() {
    window.clear();

    if (etatActuel == Etat::Menu) {
        afficherMenuPrincipal();
    } else if (etatActuel == Etat::Combat && combat) {
        afficherCombat();
    }

    window.display();
}

void SFMLGame::afficherMenuPrincipal() {
    afficherMessage("Menu Principal", 400, 100);
    for (const auto& option : menuPrincipal) {
        window.draw(option);
    }
}

void SFMLGame::afficherCombat() {
    combat->dessinerCombat(window, font);
    window.draw(fondAttaques);

    for (auto& bouton : boutonsAttaques) {
        window.draw(bouton);
    }

    window.draw(messageCombat);
}

void SFMLGame::afficherMessage(const std::string& message, float x, float y) {
    text.setString(message);
    text.setPosition(x, y);
    window.draw(text);
}

void SFMLGame::afficherEquipeConsole() {
    jeu.afficherEquipe();
}
