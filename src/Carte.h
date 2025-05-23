#pragma once
#include <string>
#include "Carte.h"

class Carte {
};

class CarteAller : public Carte {
private:
	std::string Destination;
};

class CarteStand : public Carte {
private:
	std::string Couleur;
};
