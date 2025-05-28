//
// Created by romain on 23/05/25.
//
#ifndef CASES_H
#define CASES_H

#include <string>
#include "Couleurs.h"
#include "rtti.hpp"

template<typename Base, typename T>
bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

class Case {
protected:
    int index;
    Case* casePrecedente;
    Case* caseSuivante;

public:
    virtual ~Case() = default;  // Make polymorphic for dynamic_cast
    explicit Case(const int index) : index(index), casePrecedente(nullptr), caseSuivante(nullptr) {}

    Case* linkTo(Case* suivante);

    Case* getCasePrecedente() const { return casePrecedente; }
    Case* getCaseSuivante() const { return caseSuivante; }
    int getIndex() const { return index; }
};

class Attraction final : public Case {
private:
    const int prix;
    const Couleur::Couleur couleur;
    std::string proprietaire;
    const std::string nom;

    static Attraction* as_attraction(Case* case_);

    bool est_meme_proprio(Case* case_) const;

public:
    Attraction(const int index, const int prix, const Couleur::Couleur couleur, std::string nom) : Case(index), prix(prix), couleur(couleur), nom(std::move(nom)) {}

    void setProprio(const std::string& proprio) {proprietaire = proprio;}
    const std::string& getProprietaire() const { return proprietaire; }
    Couleur::Couleur getCouleur() const { return couleur; }

    int getPrix() const;
};

class Fortune final : public Case {
private:
    int moula_accumule;
public:
    Fortune(const int index) : Case(index), moula_accumule(0) {}
    void addMoula(const int moula) {moula_accumule += moula;}
    int getMoula() const { return moula_accumule; }
    int takeMoula() {const int moula = moula_accumule; moula_accumule = 0; return moula; }
};

class Impots final : public Case {
private:
    const int hagra;
    const std::string nom;
public:
    Impots(const int index, const int hagra, std::string nom) : Case(index), hagra(hagra), nom(std::move(nom)) {};
    int getHagra() const { return hagra; }
};

class Cafe final : public Case {
public:
    Cafe(const int index) : Case(index) {}
};

class Depart final : public Case {
public:
    Depart(const int index) : Case(index) {}
};

class Train final : public Case {
    const Couleur::Couleur couleur;
public:
    Train(const int index, const Couleur::Couleur couleur) : Case(index), couleur(couleur) {}
};

class GotoCafe final : public Case {
public:
    GotoCafe(const int index) : Case(index) {}
};

class Chance final : public Case {
public:
    Chance(const int index) : Case(index) {}
};


#endif //CASES_H
