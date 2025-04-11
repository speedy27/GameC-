#include "Battle.h"
#include <iostream>
#include <random>
#include <ctime>
#include <thread>
#include <chrono>

Battle::Battle(Pokemon* player, Pokemon* opponent) : player(player), opponent(opponent) {
    // Initialisation du générateur de nombres aléatoires
    std::random_device rd;
    rng = std::mt19937(rd());
}

void Battle::start() {
    std::cout << "Un combat sauvage commence !" << std::endl;
    std::cout << "Votre Pokémon: ";
    player->displayStatus();
    std::cout << "Pokémon adverse: ";
    opponent->displayStatus();
    std::cout << "\n";

    // Détermine qui commence en fonction de la vitesse
    bool playerFirst = player->getSpeed() >= opponent->getSpeed();
    
    while (!player->isKO() && !opponent->isKO()) {
        if (playerFirst) {
            if (playerTurn()) {
                break; // Le combat est terminé
            }
            if (!opponent->isKO() && opponentTurn()) {
                break; // Le combat est terminé
            }
        } else {
            if (opponentTurn()) {
                break; // Le combat est terminé
            }
            if (!player->isKO() && playerTurn()) {
                break; // Le combat est terminé
            }
        }
    }

    // Affichage du résultat du combat
    if (opponent->isKO()) {
        std::cout << "Félicitations! " << opponent->getName() << " est K.O.!" << std::endl;
        std::cout << "Vous avez gagné le combat!" << std::endl;
    } else {
        std::cout << "Votre " << player->getName() << " est K.O.!" << std::endl;
        std::cout << "Vous avez perdu le combat!" << std::endl;
    }
}

bool Battle::playerTurn() {
    std::cout << "\n--- VOTRE TOUR ---" << std::endl;
    player->displayStatus();
    opponent->displayStatus();
    player->displayAttacks();
    
    int choice;
    do {
        std::cout << "Choisissez une attaque (1-" << player->getAttacks().size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(player->getAttacks().size()));
    
    const Attack& selectedAttack = player->getAttacks()[choice - 1];
    
    std::cout << player->getName() << " utilise " << selectedAttack.getName() << "!" << std::endl;
    
    // Vérifier si l'attaque touche
    if (checkAccuracy(selectedAttack)) {
        int damage = calculateDamage(*player, *opponent, selectedAttack);
        float effectiveness = getTypeEffectiveness(selectedAttack.getType(), opponent->getType());
        
        if (effectiveness > 1.5f) {
            std::cout << "C'est super efficace!" << std::endl;
        } else if (effectiveness < 0.6f && effectiveness > 0.0f) {
            std::cout << "Ce n'est pas très efficace..." << std::endl;
        } else if (effectiveness == 0.0f) {
            std::cout << "Ça n'affecte pas " << opponent->getName() << "..." << std::endl;
        }
        
        opponent->takeDamage(damage);
        std::cout << "Ça inflige " << damage << " dégâts!" << std::endl;
    } else {
        std::cout << "Mais l'attaque échoue!" << std::endl;
    }
    
    // Pause pour meilleure lisibilité
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    return opponent->isKO();
}

bool Battle::opponentTurn() {
    std::cout << "\n--- TOUR ADVERSE ---" << std::endl;
    
    // L'adversaire choisit une attaque aléatoire
    std::uniform_int_distribution<int> dist(0, opponent->getAttacks().size() - 1);
    int aiChoice = dist(rng);
    const Attack& selectedAttack = opponent->getAttacks()[aiChoice];
    
    std::cout << opponent->getName() << " utilise " << selectedAttack.getName() << "!" << std::endl;
    
    // Vérifier si l'attaque touche
    if (checkAccuracy(selectedAttack)) {
        int damage = calculateDamage(*opponent, *player, selectedAttack);
        float effectiveness = getTypeEffectiveness(selectedAttack.getType(), player->getType());
        
        if (effectiveness > 1.5f) {
            std::cout << "C'est super efficace!" << std::endl;
        } else if (effectiveness < 0.6f && effectiveness > 0.0f) {
            std::cout << "Ce n'est pas très efficace..." << std::endl;
        } else if (effectiveness == 0.0f) {
            std::cout << "Ça n'affecte pas " << player->getName() << "..." << std::endl;
        }
        
        player->takeDamage(damage);
        std::cout << "Ça inflige " << damage << " dégâts!" << std::endl;
    } else {
        std::cout << "Mais l'attaque échoue!" << std::endl;
    }
    
    // Pause pour meilleure lisibilité
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    return player->isKO();
}

int Battle::calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Attack& attack) {
    // Formule simplifiée des dégâts Pokémon
    float effectiveness = getTypeEffectiveness(attack.getType(), defender.getType());
    
    // Calcul de base des dégâts
    float levelFactor = 2.0f; // Représente le niveau * 2 / 5 + 2
    float attackDefenseRatio = static_cast<float>(attacker.getAttack()) / defender.getDefense();
    float baseDamage = (levelFactor * attack.getPower() * attackDefenseRatio) / 50 + 2;
    
    // Facteur aléatoire (entre 0.85 et 1.0)
    std::uniform_real_distribution<float> randomFactor(0.85f, 1.0f);
    float random = randomFactor(rng);
    
    // STAB (Same Type Attack Bonus)
    float stab = (attack.getType() == attacker.getType()) ? 1.5f : 1.0f;
    
    // Calcul final
    int finalDamage = static_cast<int>(baseDamage * stab * effectiveness * random);
    if (finalDamage < 1) finalDamage = 1; // Un minimum de 1 de dégâts
    
    return finalDamage;
}

bool Battle::checkAccuracy(const Attack& attack) {
    std::uniform_int_distribution<int> dist(1, 100);
    int roll = dist(rng);
    return roll <= attack.getAccuracy();
}