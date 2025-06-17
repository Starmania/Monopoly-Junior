//
// Created by romain on 17/06/25.
//

#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>

#include "Couleurs.h"

class Joueur {
    const Couleur::Couleur couleur;
    const std::string nom;
    int stands = 0;
    int moula = 0;
public:
    Joueur(const Couleur::Couleur couleur, std::string nom): couleur(couleur), nom(std::move(nom)) {}
    Couleur::Couleur getCouleur() const {return couleur;}
    std::string getNom() const {return nom;}
    int getStands() const {return stands;}
    void setStands(const int stands) {this->stands = stands;}
    int getMoula() const {return moula;}
    void setMoula(const int moula) {this->moula = moula;}
};

#endif //JOUEUR_H
