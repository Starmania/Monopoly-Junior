#pragma once

#include "Cases.h"
#include "Carte.h"
#include <vector>

std::vector<Case*> cases = {
	new Depart(0),
	new Chance(1),
	new Attraction(2, 1, Couleur::VIOLET, "Jeu de ballon"),
	new Attraction(3, 1, Couleur::VIOLET, "Barbe à papa"),
	new Chance(4),
	new Train(5, Couleur::JAUNE),
	new Attraction(6, 2, Couleur::BLANC, "Théatre de marionettes"),
	new Attraction(7, 2, Couleur::BLANC, "Barbe à papa"),
	new Impots(8, 2, "voir le feu d'artifice"),
	new Chance(9),
	new Cafe(10),
	new Attraction(11, 2, Couleur::ROSE, "Manège"),
	new Attraction(12, 2, Couleur::ROSE, "Pédalos"),
	new Train(13, Couleur::VERT),
	new Attraction(14, 3, Couleur::ORANGE, "Tobogan aquatique"),
	new Attraction(15, 3, Couleur::ORANGE, "Mini-golf"),
	new Fortune(16),
	new Chance(17),
	new Attraction(18, 3, Couleur::ROUGE, "Jeux Vidéo"),
	new Attraction(19, 3, Couleur::ROUGE, "La Maison Hantée"),
	new Chance(20),
	new Train(21, Couleur::BLEU),
	new Attraction(22, 4, Couleur::JAUNE, "Promenade en Hélicoptère"),
	new Attraction(23, 4, Couleur::JAUNE, "Promenade à poney"),
	new Impots(24, 2, "voir le ballet des dauphins"),
	new Chance(25),
	new GotoCafe(26),
	new Attraction(27, 4, Couleur::VERT, "Autos tamponneuses"),
	new Attraction(28, 4, Couleur::VERT, "Grande roue"),
	new Train(29, Couleur::ROUGE),
	new Attraction(30, 5, Couleur::BLEU, "Grand Huit"),
	new Attraction(31, 5, Couleur::BLEU, "Montagnes Russes")
};

std::vector<Carte*> cartes = {


};
