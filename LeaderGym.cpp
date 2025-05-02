#include "LeaderGym.h"
#include <iostream>

LeaderGym::LeaderGym(const std::string& name, const std::string& gym, const std::string& badge)
    : Entraineur(name), gymName(gym), badgeName(badge) {}

void LeaderGym::interagir() {
    std::cout << "Leader " << name << " (" << gymName << ") vous remet la médaille " << badgeName << "!" << std::endl;
}
