#include "MaitrePokemon.h"
#include <iostream>

MaitrePokemon::MaitrePokemon(const std::string& name)
    : Entraineur(name) {}

void MaitrePokemon::interagir() {
    std::cout << "Maître " << name << " félicite votre parcours exceptionnel!" << std::endl;
}
