/*
 * Fichier : Menu.cpp
 * Auteurs : Florian & Adrien
 * Description : Implémentation de la classe Menu pour l’interface console.
 */

 #include "Menu.h"
 #include "CombatEngine.h"
 #include <iostream>
 #include <limits>
 #include <regex>
 
 Menu::Menu(Joueur& j,
            const std::vector<Entraineur*>& leadersList,
            const std::vector<MaitrePokemon*>& maitresList)
     : joueur(j), leaders(leadersList), maitres(maitresList) {}
 
 void Menu::run() {
     int choix;
     do {
         std::cout << "\n--- Menu ---\n"
                   << "1. Afficher Pokémon\n"
                   << "2. Statistiques\n"
                   << "3. Changer ordre\n"
                   << "4. Affronter un leader\n"
                   << "5. Affronter un maître\n"
                   << "6. Interagir\n"
                   << "0. Quitter\n"
                   << "Choix: ";
         std::cin >> choix;
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         switch (choix) {
             case 1: afficherPokemons();   break;
             case 2: afficherStats();      break;
             case 3: changerOrdre();       break;
             case 4: combattreLeader();    break;
             case 5: combattreMaitre();    break;
             case 6: interagir();          break;
         }
     } while (choix != 0);
 }
 
 void Menu::afficherPokemons() const {
     std::cout << "--- Pokémons du joueur ---\n";
     for (auto* p : joueur.getEquipe()) {
         std::cout << p->getName() << " (" << p->getHP() << " HP)\n";
     }
 }
 
 void Menu::afficherStats() const {
     std::cout << "Badges: " << joueur.getBadges()
               << " | Victoires: " << joueur.getWins()
               << " | Défaites: " << joueur.getLosses()
               << "\n";
 }
 
 void Menu::changerOrdre() {
     int i, j;
     afficherPokemons();
     std::cout << "Index à échanger (1-6): ";
     std::cin >> i >> j;
     auto& eq = const_cast<std::vector<Pokemon*>&>(joueur.getEquipe());
     if (i >= 1 && i <= (int)eq.size() && j >= 1 && j <= (int)eq.size()) {
         std::swap(eq[i-1], eq[j-1]);
     }
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 }
 
 void Menu::combattreLeader() {
     std::cout << "\n--- Choix du Leader ---\n";
     for (auto* l : leaders) {
         std::cout << " - " << l->getName() << "\n";
     }
     std::cout << "Entrez regex pour le leader: ";
     std::string pat;
     std::getline(std::cin, pat);
     std::regex rgx(pat, std::regex_constants::icase);
 
     std::vector<Entraineur*> matchs;
     for (auto* l : leaders) {
         if (std::regex_search(l->getName(), rgx)) matchs.push_back(l);
     }
     if (matchs.empty()) {
         std::cout << "Aucun leader ne correspond.\n";
         return;
     }
     Entraineur* sel = nullptr;
     if (matchs.size() == 1) {
         sel = matchs.front();
     } else {
         std::cout << matchs.size() << " correspondances:\n";
         for (size_t k = 0; k < matchs.size(); ++k)
             std::cout << "[" << k << "] " << matchs[k]->getName() << "\n";
         std::cout << "Indice du choix: ";
         size_t idx;
         std::cin >> idx;
         if (idx < matchs.size()) sel = matchs[idx];
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     }
     if (sel) {
         bool win = CombatEngine::battle(joueur, *sel);
         if (win) joueur.gainBadge();
     }
 }
 
 void Menu::combattreMaitre() {
     if (joueur.getBadges() < (int)leaders.size()) {
         std::cout << "Vous devez obtenir toutes les médailles!\n";
         return;
     }
     std::cout << "\n--- Choix du Maître ---\n";
     for (auto* m : maitres) {
         std::cout << " - " << m->getName() << "\n";
     }
     std::cout << "Entrez regex pour le maître: ";
     std::string pat;
     std::getline(std::cin, pat);
     std::regex rgx(pat, std::regex_constants::icase);
 
     std::vector<MaitrePokemon*> matchs;
     for (auto* m : maitres) {
         if (std::regex_search(m->getName(), rgx)) matchs.push_back(m);
     }
     if (matchs.empty()) {
         std::cout << "Aucun maître ne correspond.\n";
         return;
     }
     MaitrePokemon* sel = nullptr;
     if (matchs.size() == 1) {
         sel = matchs.front();
     } else {
         std::cout << matchs.size() << " correspondances:\n";
         for (size_t k = 0; k < matchs.size(); ++k)
             std::cout << "[" << k << "] " << matchs[k]->getName() << "\n";
         std::cout << "Indice du choix: ";
         size_t idx;
         std::cin >> idx;
         if (idx < matchs.size()) sel = matchs[idx];
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     }
     if (sel) {
         CombatEngine::battle(joueur, *sel);
     }
 }
 
 void Menu::interagir() {
     std::cout << "\n--- Interaction ---\n"
               << "1. Pokémon du joueur\n"
               << "2. Entraîneurs vaincus\n"
               << "Choix: ";
     int c;
     std::cin >> c;
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     if (c == 1) {
         const auto& eq = joueur.getEquipe();
         for (size_t i = 0; i < eq.size(); ++i)
             std::cout << i << ": " << eq[i]->getName() << "\n";
         std::cout << "Index du Pokémon: ";
         size_t idx;
         std::cin >> idx;
         if (idx < eq.size()) eq[idx]->interagir();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     } else if (c == 2) {
         const auto& dt = joueur.getDefeatedTrainers();
         if (dt.empty()) {
             std::cout << "Aucun entraîneur vaincu pour interagir.\n";
             return;
         }
         for (size_t i = 0; i < dt.size(); ++i)
             std::cout << i << ": " << dt[i]->getName() << "\n";
         std::cout << "Index de l'entraîneur: ";
         size_t idx;
         std::cin >> idx;
         if (idx < dt.size()) dt[idx]->interagir();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     }
 }
 