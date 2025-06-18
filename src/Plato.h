#ifndef PLATO_H
#define PLATO_H

#include <random>
#include <string>
#include <vector>

#include "linked_list/LinkedList.h"
#include "Cases.h"
#include "Carte.h"
#include "Joueur.h"


class Plato
{
public :
	Plato();

	void lancer_jeu();
	int lancer_de();

	void relancer_de();

	void ajouter_joueur(std::string nom_joueur, Couleur::Couleur couleur);
	Joueur* joueur_suivant();
	Joueur* get_joueur(Couleur::Couleur couleur) const;
	Carte* piocher_carte();

	bool joueur_fait_bankeroute() const;

	Case* get_case(const int index) {return this->cases[index];}

	Attraction *get_stand_couleur(const Couleur::Couleur couleur);

	size_t get_plato_size();

private :
	std::mt19937 random_generator = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<> distrib{1,6};
	LinkedList<Case*> cases;
	LinkedList<Carte*> cartes;
	std::vector<Joueur*> joueurs;
	bool jeu_en_cours = false;
	std::vector<Joueur*>::iterator joueur_it; //
};

#endif
