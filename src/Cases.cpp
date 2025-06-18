//
// Created by romain on 23/05/25.
//
#include "Cases.h"

Case *Case::linkTo(Case *suivante) {
    this->caseSuivante = suivante;
    if (suivante) suivante->casePrecedente = this;
    return suivante;
}

bool Attraction::est_meme_proprio(Case *case_) const {
    const Attraction *attraction = dynamic_cast<Attraction *>(case_);
    if (!attraction) return false;
    return attraction->proprietaire == this->proprietaire && attraction->couleur == this->couleur;
}

bool Attraction::voisin_meme_proprio() const {
    return (casePrecedente && est_meme_proprio(casePrecedente)) ||
           (caseSuivante && est_meme_proprio(caseSuivante));
}

int Attraction::getPrix(const Couleur::Couleur joueur) const {
    if (proprietaire == joueur) return 0;

    if (voisin_meme_proprio()) return prix * 2;
    return prix;
}
