#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <random>

// Structure de données pour les attaques
struct Attaque {
    std::string nom;
    int puissance;
};

class Pokemon {
protected:
    std::string nom;
    std::string type;
    int pv;
    int pvMax;
    std::vector<Attaque> attaques;
    std::string imageFront;
    std::string imageBack;

public:
    Pokemon(const std::string& nom, const std::string& type, int pv, const std::vector<Attaque>& attaques,
            const std::string& imageFront, const std::string& imageBack)
        : nom(nom), type(type), pv(pv), pvMax(pv), attaques(attaques),
          imageFront(imageFront), imageBack(imageBack) {}

    virtual ~Pokemon() = default;

    const std::string& getNom() const { return nom; }
    const std::string& getType() const { return type; }
    int getPV() const { return pv; }
    int getPVMax() const { return pvMax; }
    const std::vector<Attaque>& getAttaques() const { return attaques; }
    const std::string& getImageFront() const { return imageFront; }
    const std::string& getImageBack() const { return imageBack; }

    bool estKO() const { return pv <= 0; }

    int subirDegats(int degats) {
        pv -= degats;
        if (pv < 0) pv = 0;
        return degats;
    }

    Attaque choisirAttaqueAleatoire() const {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        if (attaques.empty()) return {"Griffes", 10}; // Sécurité

        std::uniform_int_distribution<> dis(0, attaques.size() - 1);
        return attaques[dis(gen)];
    }

    void afficherInfos() const {
        std::cout << "Nom: " << nom << "\n"
                  << "Type: " << type << "\n"
                  << "HP: " << pv << "/" << pvMax << "\n";
        for (const auto& atk : attaques) {
            std::cout << "Attaque: " << atk.nom << " (Puissance: " << atk.puissance << ")\n";
        }
    }

    virtual std::unique_ptr<Pokemon> clone() const = 0;
};

// Sous-classes concrètes pour chaque type de Pokémon

class PokemonFeu : public Pokemon {
public:
    using Pokemon::Pokemon;

    std::unique_ptr<Pokemon> clone() const override {
        return std::make_unique<PokemonFeu>(*this);
    }
};

class PokemonEau : public Pokemon {
public:
    using Pokemon::Pokemon;

    std::unique_ptr<Pokemon> clone() const override {
        return std::make_unique<PokemonEau>(*this);
    }
};

class PokemonPlante : public Pokemon {
public:
    using Pokemon::Pokemon;

    std::unique_ptr<Pokemon> clone() const override {
        return std::make_unique<PokemonPlante>(*this);
    }
};

class PokemonElectrik : public Pokemon {
public:
    using Pokemon::Pokemon;

    std::unique_ptr<Pokemon> clone() const override {
        return std::make_unique<PokemonElectrik>(*this);
    }
};

class PokemonPsy : public Pokemon {
public:
    using Pokemon::Pokemon;

    std::unique_ptr<Pokemon> clone() const override {
        return std::make_unique<PokemonPsy>(*this);
    }
};

class PokemonNormal : public Pokemon {
public:
    using Pokemon::Pokemon;

    std::unique_ptr<Pokemon> clone() const override {
        return std::make_unique<PokemonNormal>(*this);
    }
};

#endif // POKEMON_H
