#ifndef ENTRAINEUR_H
#define ENTRAINEUR_H

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Interagir.h"

/**
 * Classe de base pour Joueur, LeaderGym, MaitrePokemon
 */
class Entraineur : public Interagir {
public:
    Entraineur(const std::string& name);
    virtual ~Entraineur();

    void addPokemon(Pokemon* p);
    bool hasPokemon() const;
    Pokemon* getCurrentPokemon();
    void nextPokemon();
    const std::string& getName() const;
    void interagir() override;
    const std::vector<Pokemon*>& getEquipe() const { return equipe; }

protected:
    std::string name;
    std::vector<Pokemon*> equipe;
    size_t current;
};

#endif // ENTRAINEUR_H
