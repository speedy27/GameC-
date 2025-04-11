#include "SFMLGame.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Initialiser le générateur de nombres aléatoires
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    try {
        // Créer et lancer le jeu avec l'interface SFML
        SFMLGame game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}