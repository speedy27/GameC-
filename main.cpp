#include <iostream>
#include <vector>
#include <regex>
#include "DataLoader.h"
#include "Menu.h"

int main() {
    auto poks = DataLoader::loadPokemons("pokemon.csv");
    if (poks.empty()) {
        std::cerr << "Erreur : impossible de charger pokemon.csv\n";
        return 1;
    }

    std::cout << "Pokémons disponibles :\n";
    for (auto* p : poks) {
        std::cout << " - " << p->getName() << "\n";
    }
    std::cout << "\n";

    Joueur joueur("Joueur");
    std::string saisie;
    while (joueur.getEquipe().size() < 6) {
        std::cout << "Entrez un patron pour le Pokémon #"
                  << joueur.getEquipe().size()+1
                  << " (regex, insensible à la casse) : ";
        std::getline(std::cin >> std::ws, saisie);
        std::regex rgx(saisie, std::regex_constants::icase);
        std::vector<Pokemon*> matchs;
        for (auto* p : poks) {
            if (std::regex_search(p->getName(), rgx)) {
                matchs.push_back(p);
            }
        }
        if (matchs.empty()) {
            std::cout << "Aucune correspondance, réessayez.\n\n";
        } else if (matchs.size() == 1) {
            joueur.addPokemon(matchs.front()->clone());
            std::cout << "-> " << matchs.front()->getName() << " ajouté.\n\n";
        } else {
            std::cout << matchs.size() << " correspondances :\n";
            for (size_t i=0; i<matchs.size(); ++i)
                std::cout << "  [" << i << "] " << matchs[i]->getName() << "\n";
            std::cout << "Indice du choix : ";
            size_t idx; std::cin >> idx;
            if (idx < matchs.size()) {
                joueur.addPokemon(matchs[idx]->clone());
                std::cout << "-> " << matchs[idx]->getName() << " ajouté.\n\n";
            } else {
                std::cout << "Indice invalide.\n\n";
            }
            std::cin.clear();
            std::getline(std::cin, saisie);
        }
    }

    auto leaders = DataLoader::loadLeaders("leaders.csv", poks);
    auto maitres = DataLoader::loadMaitres("maitres.csv", poks);
    Menu menu(joueur, leaders, maitres);
    menu.run();

    for (auto* p : poks) delete p;
    for (auto* e : leaders) delete e;
    for (auto* m : maitres) delete m;
    return 0;
}
