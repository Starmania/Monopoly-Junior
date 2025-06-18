#include "Plato.h"
#include "Decks.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <numeric>

Plato::Plato()
{
    Case* previous = nullptr;
    for (Case* case_: Decks::cases) {
        if (previous != nullptr) {
            previous->linkTo(case_);
        }
        this->cases.add(case_);
        previous = case_;
    }

    std::ranges::shuffle(Decks::cartes, random_generator);

    for (Carte* carte: Decks::cartes) {
        this->cartes.add(carte);
    }

}

void Plato::lancer_jeu() {
    if (jeu_en_cours) throw std::logic_error("Jeu déjà en cours");
    if (joueurs.size() < 2) throw std::logic_error("Pas assez de joueurs");

    const int nb_stands = joueurs.size() == 2 ? 15 : 10; // 15 de stands si deux joueurs sinon 10.

    for (Joueur* joueur: joueurs) {
        joueur->setStands(nb_stands);
        joueur->setMoula(31);
    }

    std::vector<int> lancees;

    for (const Joueur* joueur: joueurs) {
        lancees.push_back(lancer_de());
        std::cout << "Le joueur " << Couleur::to_string(joueur->getCouleur())
        << " lances un " << lancees.back() << std::endl;
    }

    std::vector<int> nouvel_index(joueurs.size());
    std::iota(nouvel_index.begin(), nouvel_index.end(), 0);
    // Cree une liste du style {0, 1, 2... , joueur.size() - 1}

    std::ranges::sort(nouvel_index, [&](const int a, const int b) {
        return lancees[a] > lancees[b];
    });

    std::vector<Joueur*> trie(joueurs.size());
    for (size_t i = 0; i < nouvel_index.size(); ++i)
        trie[i] = joueurs[nouvel_index[i]];

    this->joueurs = std::move(trie);

    this->joueur_it = joueurs.begin();

    this->jeu_en_cours = true;
}

int Plato::lancer_de() {
    return distrib(random_generator);
}

void Plato::ajouter_joueur(std::string nom_joueur, const Couleur::Couleur couleur)
{
    if (jeu_en_cours) throw std::logic_error("Impossible d'ajouter des joueurs après le début du jeu");

    // Les couleurs sont uniques entre les joueurs
    for (const Joueur* joueur: joueurs) {
        if (joueur->getCouleur() == couleur) {
            throw std::logic_error(std::string("Un joueur a déjà la couleur") + Couleur::to_string(couleur));
        }
    }
    joueurs.push_back(new Joueur(couleur, std::move(nom_joueur)));
}

Carte* Plato::piocher_carte() {
    Carte* carte = cartes.pop(0);
    cartes.add(carte);
    return carte;
}

std::string Plato::get_proprio_formate(Couleur::Couleur couleur) const {
    if (couleur == Couleur::UNDEFINED) {
        return "la banque";
    }
    const Joueur* joueur = get_joueur(couleur);

    return std::string(joueur->getNom()) + " (" + Couleur::to_string(joueur->getCouleur()) + ")";
}

Attraction *Plato::get_stand_couleur(const Couleur::Couleur couleur) {
    for (int i = 0; i < cases.size(); ++i) {
        Case* case_ = cases[i];
        Attraction* attraction = dynamic_cast<Attraction*>(case_);
        if (!attraction) continue;
        if (couleur == attraction->getCouleur()) return attraction;
    }
    throw std::runtime_error("???????");
}

size_t Plato::get_plato_size() {
    if (!jeu_en_cours) throw std::logic_error("Pas de taille disponible, le jeu n'est pas en cours !");
    return cases.size();
}

Fortune * Plato::get_case_fortune() {
    if (!jeu_en_cours) throw std::logic_error("Impossible d'accéder aux cases, le jeu n'est pas en cours !");
    if (case_fortune != nullptr) return case_fortune;
    for (int i = 0; i < cases.size(); ++i) {
        Case* case_ = cases[i];
        if (case_->getCaseType() == FORTUNE) {
            case_fortune = dynamic_cast<Fortune*>(case_);
            return case_fortune;
        }
    }
    throw std::runtime_error("????????");
}

Joueur* Plato::joueur_suivant() {
    if (!jeu_en_cours) throw std::logic_error("Pas de joueur suivant, le jeu n'est pas en cours !");

    Joueur* joueur = *joueur_it;
    ++joueur_it;

    if (joueur_it == joueurs.end()) {
        joueur_it = joueurs.begin(); // wrap around
    }

    return joueur;
}

void Plato::relancer_de() {
    if (!jeu_en_cours) throw std::logic_error("Pas de joueur suivant, le jeu n'est pas en cours !");

    // Recule l'iterator
    if (this->joueur_it == joueurs.begin()) {
        this->joueur_it = std::prev(joueurs.end());
    } else {
        --joueur_it;
    }
}

Joueur * Plato::get_joueur(const Couleur::Couleur couleur) const {
    for (Joueur* joueur: joueurs) {
        if (joueur->getCouleur() == couleur) {
            return joueur;
        }
    }
    throw std::invalid_argument(std::string("Le joueur de couleur ") + Couleur::to_string(couleur) + " n'existe pas !");
}

std::vector<Joueur*> Plato::get_leaderboard() const {
    std::vector<Joueur*> sortedJoueurs = joueurs;
    std::ranges::sort(sortedJoueurs, [](const Joueur* joueur1, const Joueur* joueur2) {
        return joueur1->getCouleur() > joueur2->getCouleur();
    });
    return sortedJoueurs;
}
