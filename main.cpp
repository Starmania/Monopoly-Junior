#include <iostream>

#include "src/Carte.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Carte* carte = new CarteAller(14);
    Carte* carte2 = new CarteStand(Couleur::ORANGE);

    std::cout << carte->to_string() << std::endl;
    std::cout << carte2->to_string() << std::endl;

    delete carte;
    delete carte2;

    return 0;
}
