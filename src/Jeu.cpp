//
// Created by romain on 17/06/25.
//

#include "Jeu.h"

#include <utility>

int Jeu::lancer_de() {
    return plato.lancer_de();
}

void Jeu::ajouter_joueur(std::string nom_joueur, const Couleur::Couleur couleur) {
    return plato.ajouter_joueur(std::move(nom_joueur), couleur);
}

void Jeu::jouer() {
    plato.lancer_jeu();


}
