#include "CombatEngine.h"
#include <iostream>
#include <chrono>
#include <thread>

bool CombatEngine::battle(Joueur& joueur, Entraineur& ennemi) {
    std::cout << "=== Combat: " << joueur.getName() << " vs " << ennemi.getName() << " ===" << std::endl;
    while (joueur.hasPokemon() && ennemi.hasPokemon()) {
        auto* p1 = joueur.getCurrentPokemon();
        auto* p2 = ennemi.getCurrentPokemon();
        std::cout << p1->getName() << " (" << p1->getHP() << " HP) vs " << p2->getName() << " (" << p2->getHP() << " HP)" << std::endl;
        p1->attaquer(*p2);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (p2->isFainted()) { std::cout << p2->getName() << " est K.O.!" << std::endl; ennemi.nextPokemon(); if (!ennemi.hasPokemon()) break; }
        p2->attaquer(*p1);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (p1->isFainted()) { std::cout << p1->getName() << " est K.O.!" << std::endl; joueur.nextPokemon(); if (!joueur.hasPokemon()) break; }
    }
    if (joueur.hasPokemon()) { std::cout << joueur.getName() << " remporte le combat!" << std::endl; joueur.addWin(); return true; }
    else { std::cout << ennemi.getName() << " remporte le combat!" << std::endl; joueur.addLoss(); return false; }
}
