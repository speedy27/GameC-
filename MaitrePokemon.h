#ifndef MAITREPOKEMON_H
#define MAITREPOKEMON_H

#include "Entraineur.h"

/**
 * Classe Maître Pokémon
 */
class MaitrePokemon : public Entraineur {
public:
    MaitrePokemon(const std::string& name);
    void interagir() override;
};

#endif // MAITREPOKEMON_H
