//
// Created by romain on 18/06/25.
//
#include "Joueur.h"

bool Joueur::moveBy(const int position, const int taille_plato) {
    const int oldPosition = this->getPosition();
    this->setPosition((this->getPosition() + position) % taille_plato);
    return oldPosition > this->getPosition();
}
