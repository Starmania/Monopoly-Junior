//
// Created by romain on 23/05/25.
//
#include "Cases.h"

Case *Case::linkTo(Case *suivante) {
    this->caseSuivante = suivante;
    if (suivante) suivante->casePrecedente = this;
    return suivante;
}




Attraction* Attraction::as_attraction(Case *case_) {
    return dynamic_cast<Attraction*>(case_);
}

bool Attraction::est_meme_proprio(Case *case_) const {
    const Attraction* attraction = as_attraction(case_);
    if (!attraction) return false;
    return attraction->proprietaire == this->proprietaire && attraction->couleur == this->couleur;

}

int Attraction::getPrix() const {
    if (proprietaire.empty()) {
        return prix;
    }
    if ((casePrecedente && est_meme_proprio(casePrecedente)) ||
        (caseSuivante && est_meme_proprio(caseSuivante))) {
        return prix * 2;
        }
    return prix;
}
