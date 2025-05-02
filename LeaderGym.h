#ifndef LEADERGYM_H
#define LEADERGYM_H

#include "Entraineur.h"

/**
 * Classe Leader de Gym
 */
class LeaderGym : public Entraineur {
public:
    LeaderGym(const std::string& name, const std::string& gym, const std::string& badge);
    void interagir() override;

private:
    std::string gymName, badgeName;
};

#endif // LEADERGYM_H
