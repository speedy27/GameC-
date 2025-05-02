/*
 * Fichier : DataLoader.cpp
 * Auteurs : Florian & Adrien
 * Description : Chargement des CSV de Pokémon, leaders et maîtres
 */

 #include "DataLoader.h"
 #include <fstream>
 #include <sstream>
 #include <algorithm>
 #include <map>               // pour std::map
 #include "Type.h"
 #include "Attack.h"
 
 // Inclusion de toutes les sous-classes de type
 #include "Normal.h"
 #include "Feu.h"
 #include "Eau.h"
 #include "Plante.h"
 #include "Electrik.h"
 #include "Glace.h"
 #include "Combat.h"
 #include "Poison.h"
 #include "Sol.h"
 #include "Vol.h"
 #include "Psy.h"
 #include "Insecte.h"
 #include "Roche.h"
 #include "Spectre.h"
 #include "Dragon.h"
 #include "Tenedres.h"
 #include "Acier.h"
 #include "Fee.h"
 
 static Type fromString(const std::string& s) {
     std::string ss = s;
     std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
     #define M(str,typ) if (ss == str) return Type::typ;
     M("normal", Normal) M("feu", Feu) M("eau", Eau) M("plante", Plante)
     M("electrik", Electrik) M("glace", Glace) M("combat", Combat) M("poison", Poison)
     M("sol", Sol) M("vol", Vol) M("psy", Psy) M("insecte", Insecte)
     M("roche", Roche) M("spectre", Spectre) M("dragon", Dragon)
     M("tenedres", Tenedres) M("acier", Acier) M("fee", Fee)
     #undef M
     return Type::Normal; // défaut
 }
 
 std::vector<Pokemon*> DataLoader::loadPokemons(const std::string& file) {
     std::vector<Pokemon*> v;
     std::ifstream in(file);
     if (!in) return v;
     std::string line;
     std::getline(in, line); // skip header
 
     while (std::getline(in, line)) {
         std::stringstream ss(line);
         std::string name, t1s, t2s, atkName;
         int hp, power;
         char sep;
 
         std::getline(ss, name, ',');
         std::getline(ss, t1s, ',');
         std::getline(ss, t2s, ',');
         ss >> hp >> sep;
         std::getline(ss, atkName, ',');
         ss >> power;
 
         Type type1 = fromString(t1s);
         Type type2 = t2s.empty() ? type1 : fromString(t2s);
         Attack a(atkName, type1, power);
 
         Pokemon* p = nullptr;
         switch (type1) {
             case Type::Normal:   p = new Normal(name, hp, a); break;
             case Type::Feu:      p = new Feu(name, hp, a);    break;
             case Type::Eau:      p = new Eau(name, hp, a);    break;
             case Type::Plante:   p = new Plante(name, hp, a); break;
             case Type::Electrik: p = new Electrik(name, hp, a); break;
             case Type::Glace:    p = new Glace(name, hp, a);  break;
             case Type::Combat:   p = new Combat(name, hp, a); break;
             case Type::Poison:   p = new Poison(name, hp, a); break;
             case Type::Sol:      p = new Sol(name, hp, a);    break;
             case Type::Vol:      p = new Vol(name, hp, a);    break;
             case Type::Psy:      p = new Psy(name, hp, a);    break;
             case Type::Insecte:  p = new Insecte(name, hp, a);break;
             case Type::Roche:    p = new Roche(name, hp, a);  break;
             case Type::Spectre:  p = new Spectre(name, hp, a);break;
             case Type::Dragon:   p = new Dragon(name, hp, a); break;
             case Type::Tenedres: p = new Tenedres(name, hp, a);break;
             case Type::Acier:    p = new Acier(name, hp, a);  break;
             case Type::Fee:      p = new Fee(name, hp, a);    break;
             default:             p = new Normal(name, hp, a); break;
         }
         p->setTypes({type1, type2});
         v.push_back(p);
     }
     return v;
 }
 
 std::vector<Entraineur*> DataLoader::loadLeaders(const std::string& file,
                                                  const std::vector<Pokemon*>& templates) {
     std::vector<Entraineur*> v;
     std::ifstream in(file);
     if (!in) return v;
     std::string line;
     std::getline(in, line); // header
 
     // Construire un map {nom Pokémon → prototype}
     std::map<std::string, Pokemon*> m;
     for (auto* p : templates) m[p->getName()] = p;
 
     while (std::getline(in, line)) {
         std::stringstream ss(line);
         std::string name, gymName, badgeName;
         std::getline(ss, name, ',');
         std::getline(ss, gymName, ',');
         std::getline(ss, badgeName, ',');
 
         // Créer le leader avec nom, gym et badge
         LeaderGym* leader = new LeaderGym(name, gymName, badgeName);
 
         // Ajouter ses Pokémon
         std::string poke;
         while (std::getline(ss, poke, ',')) {
             auto it = m.find(poke);
             if (it != m.end()) {
                 leader->addPokemon(it->second->clone());
             }
         }
         v.push_back(leader);
     }
     return v;
 }
 
 std::vector<MaitrePokemon*> DataLoader::loadMaitres(const std::string& file,
                                                    const std::vector<Pokemon*>& templates) {
     std::vector<MaitrePokemon*> v;
     std::ifstream in(file);
     if (!in) return v;
     std::string line;
     std::getline(in, line); // header
 
     std::map<std::string, Pokemon*> m;
     for (auto* p : templates) m[p->getName()] = p;
 
     while (std::getline(in, line)) {
         std::stringstream ss(line);
         std::string name;
         std::getline(ss, name, ',');
 
         MaitrePokemon* mpr = new MaitrePokemon(name);
 
         std::string poke;
         while (std::getline(ss, poke, ',')) {
             auto it = m.find(poke);
             if (it != m.end()) {
                 mpr->addPokemon(it->second->clone());
             }
         }
         v.push_back(mpr);
     }
     return v;
 }
 