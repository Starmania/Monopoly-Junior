//
// Created by romain on 17/06/25.
//

#include "Jeu.h"

#include <iostream>
#include <utility>

int Jeu::lancer_de() {
    return plato.lancer_de();
}

bool Jeu::est_carte_utilisable(Carte *carte) {
    CarteStand *stand = dynamic_cast<CarteStand *>(carte);
    if (!stand) { return true; }
    Attraction *case_ = plato.get_stand_couleur(stand->get_couleur());
    return !case_->voisin_meme_proprio();
}

void Jeu::ajouter_joueur(std::string nom_joueur, const Couleur::Couleur couleur) {
    return plato.ajouter_joueur(std::move(nom_joueur), couleur);
}

void Jeu::jouer() {
    plato.lancer_jeu();

    const int taille_plato = static_cast<int>(plato.get_plato_size());

    while (!plato.joueur_fait_bankeroute()) {
        Joueur *joueur = plato.joueur_suivant();
        int lance = plato.lancer_de();

        std::cout << "Le joueur " << Couleur::to_string(joueur->getCouleur())
                << " lances un " << lance << ". Il a " << joueur->getMoula() << "$." << std::endl;

        if (bool tour_complet = joueur->moveBy(lance, taille_plato)) {
            joueur->addMoula(3);
            std::cout << "Il passe par la case départ ! (+3$)" << std::endl;
        }
        Case *case_ = plato.get_case(joueur->getPosition());
        switch (case_->getCaseType()) {
            case Cases::ATTRACTION: {
                Attraction *attraction = dynamic_cast<Attraction *>(case_);

                std::cout << "Il arrive sur l'attraction " << attraction->getNom() << std::endl;

                const int moula = attraction->getPrix(joueur->getCouleur());
                if (moula == 0) {
                    std::cout << "Elle lui appartiens !" << std::endl;
                    break;
                }

                joueur->setMoula(joueur->getMoula() - moula);

                if (attraction->getProprietaire() == Couleur::UNDEFINED) {
                    if (joueur->getStands() > 0) {
                        attraction->setProprio(joueur->getCouleur());
                        joueur->setStands(joueur->getStands() - 1);
                    }
                } else {
                    plato.get_joueur(attraction->getProprietaire())->addMoula(moula);
                }
                break;
            }
            case Cases::FORTUNE:{
                Fortune *fortune = dynamic_cast<Fortune *>(case_);
                joueur->addMoula(fortune->takeMoula());
                break;
            }
            case Cases::CHANCE:{
                Carte *carte;
                do {
                    carte = plato.piocher_carte();
                } while (!est_carte_utilisable(carte));
                // More code here needed
                break;}
            case Cases::GOTO_CAFE:{
                joueur->addMoula(-3);

                joueur->setPosition(26);
                break;}
            case Cases::TRAIN:{
                std::cout << "On prends le train !!" << std::endl;
                plato.relancer_de();
                break;}
            case Cases::IMPOTS:{
                const Impots *impots = dynamic_cast<const Impots *>(case_);
                joueur->addMoula(impots->getHagra());
                break;}

            case Cases::CAFE:
            case Cases::DEPART:
            case Cases::BASE:
            default: break ;
        }
    }


}
