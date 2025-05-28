#pragma once

#include <string>
#include "linked_list/LinkedList.h"
#include "Cases.h"
#include "Carte.h"

class Plato
{
public :
	Plato();
	void ajouter_joueur(std::string nom_joueur, Couleur::Couleur couleur);

private :
	LinkedList<Case*> cases;
	LinkedList<Carte*> cartes;

};

