/*
 * Fichier : Interagir.h
 * Auteurs : Florian & Adrien
 * Description : Interface pour interaction
 */

#ifndef INTERAGIR_H
#define INTERAGIR_H

/**
 * @class Interagir
 * @brief Interface pour entités interactives.
 */
class Interagir {
public:
    virtual ~Interagir() {}
    virtual void interagir() = 0;
};

#endif // INTERAGIR_H
