#pragma once

#include "Cases.h"
#include "Carte.h"
#include <vector>

std::vector<Case*> cases = {
	new Depart(0),
	new Chance(1),
	new Attraction(2, 1, Couleur::VIOLET, "Jeu de ballon"),
	new Attraction(3, 1, Couleur::VIOLET, "Barbe � papa"),
	new Chance(4),
	new Train(5, Couleur::JAUNE),
	new Attraction(6, 2, Couleur::BLANC, "Th�atre de marionettes"),
	new Attraction(7, 2, Couleur::BLANC, "Barbe � papa"),
	new Impots(8, 2, "voir le feu d'artifice"),
	new Chance(9),
	new Cafe(10),



	
};

