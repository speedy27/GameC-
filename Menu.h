#ifndef MENU_H
#define MENU_H

#include "Joueur.h"
#include "Entraineur.h"
#include "MaitrePokemon.h"
#include <vector>

/**
 * Interface console principale pour le simulateur Pokémon
 */
class Menu {
public:
    Menu(Joueur& j, const std::vector<Entraineur*>& leaders, const std::vector<MaitrePokemon*>& maitres);
    void run();
private:
    Joueur& joueur;
    std::vector<Entraineur*> leaders;
    std::vector<MaitrePokemon*> maitres;

    void afficherPokemons() const;
    void afficherStats() const;
    void changerOrdre();
    void combattreLeader();
    void combattreMaitre();
    void interagir();
};

#endif // MENU_H
