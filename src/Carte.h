#pragma once
#include <string>
#include <utility>

#include "Couleurs.h"

class Carte {
public:
	// Ici, on indique que les autres Carte peuvent redéfinir to_string, lorsqu'elles héritent de Carte
	virtual ~Carte() = default;
	virtual std::string to_string() const {return "Carte()";};
};

class CarteAller : public Carte {
private:
	std::string destination;
public:
	// std::move > const&
	CarteAller(std::string Destination) : destination(std::move(Destination)) {}
	std::string to_string() const override { return "CarteAller(" + destination + ")"; }
};

class CarteStand : public Carte {
private:
	Couleur::Couleur couleur;
public:
	CarteStand(const Couleur::Couleur couleur) : couleur(couleur) {}
	std::string to_string() const override { return std::string("CarteStand(") + Couleur::to_string(couleur) + ")";}
};
