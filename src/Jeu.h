//
// Created by romain on 17/06/25.
//

#ifndef JEU_H
#define JEU_H
#include "Plato.h"
#include <random>


class Jeu {
private:
    Plato plato;
    int lancer_de();
    bool est_carte_utilisable(Carte* carte);
public:
    void ajouter_joueur(std::string nom_joueur, Couleur::Couleur couleur);
    void jouer();
};



#endif //JEU_H
