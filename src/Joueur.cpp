//
// Created by romain on 18/06/25.
//
#include "Joueur.h"

bool Joueur::moveBy(const int position, const int taille_plato) {
    return moveTo((this->getPosition() + position) % taille_plato);
}

bool Joueur::moveTo(const int position) {
    const bool tourComplet = this->position >= position;
    this->setPosition(position);
    return tourComplet;
}