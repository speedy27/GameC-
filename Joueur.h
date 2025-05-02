#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entraineur.h"

/**
 * Classe Joueur
 */ 
class Joueur : public Entraineur {
public:
    void addDefeatedTrainer(Entraineur* e);
    const std::vector<Entraineur*>& getDefeatedTrainers() const;

    Joueur(const std::string& name);
    int getBadges() const;
    int getWins() const;
    int getLosses() const;
    void gainBadge();
    void addWin();
    void addLoss();
    void interagir() override;

private:
    std::vector<Entraineur*> defeatedTrainers;  // Entraîneurs vaincus

    int badges, wins, losses;
};

#endif // JOUEUR_H
