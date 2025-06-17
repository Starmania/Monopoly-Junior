#include <iostream>

#include "src/Carte.h"
#include "src/Jeu.h"
#include "src/Plato.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Jeu jeu;

    jeu.ajouter_joueur("Romain", Couleur::BLANC);
    jeu.ajouter_joueur("Simon", Couleur::JAUNE);

    jeu.jouer();

    return 0;
}
