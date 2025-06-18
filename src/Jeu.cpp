//
// Created by romain on 17/06/25.
//

#include "Jeu.h"

#include <algorithm>
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

void Jeu::do_work(Joueur *joueur) {
    Case *case_ = plato.get_case(joueur->getPosition());
    switch (case_->getCaseType()) {
        case Cases::ATTRACTION: {
            Attraction *attraction = dynamic_cast<Attraction *>(case_);

            std::cout << "Tu arrives sur l'attraction " << attraction->getNom() << std::endl;

            const int moula = attraction->getPrix(joueur->getCouleur());
            if (moula == 0) {
                std::cout << "Elle t'appartiens déjà !" << std::endl;
                break;
            }

            joueur->addMoula(-moula);

            if (attraction->getProprietaire() == Couleur::UNDEFINED) {
                // Le stand appartiens à la banque et peut être acheté
                if (joueur->getStands() > 0) {
                    attraction->setProprio(joueur->getCouleur());
                    joueur->setStands(joueur->getStands() - 1);
                }
            } else {
                // Paye le joueur à qui appartiens l'attraction
                plato.get_joueur(attraction->getProprietaire())->addMoula(moula);
            }
            break;
        }
        case Cases::FORTUNE: {
            Fortune *fortune = dynamic_cast<Fortune *>(case_);
            int moula = fortune->takeMoula();
            if (moula == 0) {
                std::cout << "Case fortune ! (Mais vide...)" << std::endl;
            } else {
                std::cout << "Case fortune ! +" << moula << "$" << std::endl;
            }
            joueur->addMoula(fortune->takeMoula());
            break;
        }
        case Cases::CHANCE: {
            std::cout << "Case chance !" << std::endl;
            Carte *carte;
            do {
                carte = plato.piocher_carte();
            } while (!est_carte_utilisable(carte));

            const CarteAller *aller = dynamic_cast<CarteAller *>(carte);
            if (aller) {
                std::cout << "On se déplace..." << std::endl;
                joueur->moveTo(aller->getDestination());
                do_work(joueur);
            } else {
                const CarteStand *stand = dynamic_cast<CarteStand *>(carte);

                Attraction *attraction1 = plato.get_stand_couleur(stand->get_couleur());
                Attraction *attraction2 = dynamic_cast<Attraction *>(attraction1->getCaseSuivante());

                const std::string proprio1 = plato.get_proprio_formate(attraction1->getProprietaire());
                const std::string proprio2 = plato.get_proprio_formate(attraction2->getProprietaire());

                std::cout << "Les attractions de couleur " << Couleur::to_string(attraction1->getCouleur())
                        << " sont dispoblibles !" << std::endl << "Tu peux prendre: " << std::endl;

                std::cout << "1) " << attraction1->getNom() << " appartenant à " << proprio1 << std::endl;
                std::cout << "2) " << attraction2->getNom() << " appartenant à " << proprio2 << std::endl;

                std::string inp = "0";
                while (inp != "1" && inp != "2") {
                    std::cout << std::endl << "Lequel veut tu acheter ? (1/2)" << std::endl << "> " << std::flush;
                    std::cin >> inp;
                }
                if (inp == "1") {
                    attraction1->setProprio(joueur->getCouleur());
                } else {
                    attraction2->setProprio(joueur->getCouleur());
                }
            }

            break;
        }
        case Cases::GOTO_CAFE: {
            std::cout << "Un chocolat chaud ? En direction le café ! (-3$)" << std::endl;
            joueur->addMoula(-3);
            Fortune *fortune = plato.get_case_fortune();
            fortune->addMoula(3);
            joueur->setPosition(26);
            break;
        }
        case Cases::TRAIN: {
            std::cout << "On prends le train !!" << std::endl;
            plato.relancer_de();
            break;
        }
        case Cases::IMPOTS: {
            const Impots *impots = dynamic_cast<const Impots *>(case_);
            std::cout << "Participe à " << impots->getNom() << "(-2$)" << std::endl;
            joueur->addMoula(impots->getHagra());
            break;
        }
        case Cases::CAFE:
        case Cases::DEPART:
        case Cases::BASE:
        default: break ;
    }
}

void Jeu::jouer() {
    plato.lancer_jeu();

    const int taille_plato = static_cast<int>(plato.get_plato_size());

    while (true) {
        Joueur *joueur = plato.joueur_suivant();
        const int lance = plato.lancer_de();

        std::cout << plato.get_proprio_formate(joueur->getCouleur())
                << " lances un " << lance << ". Il a " << joueur->getMoula() << "$." << std::endl;

        if (bool tour_complet = joueur->moveBy(lance, taille_plato)) {
            joueur->addMoula(3);
            std::cout << "Il passe par la case départ ! (+3$)" << std::endl;
        }

        do_work(joueur);

        std::cout << std::endl;

        if (joueur->getMoula() <= 0) {
            std::cout << plato.get_proprio_formate(joueur->getCouleur()) << " fait banqueroute..." << std::endl;
            break;
        }
    }

    const std::vector<Joueur *> leaderboard = plato.get_leaderboard();

    std::cout << std::endl << "Ranking : " << std::endl;
    for (const Joueur *joueur: leaderboard) {
        std::cout << plato.get_proprio_formate(joueur->getCouleur()) << " avec "
        << joueur->getMoula() << "$." << std::endl;
    }
}
