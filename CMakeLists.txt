cmake_minimum_required(VERSION 3.30)
project(monopoly-junior)

set(CMAKE_CXX_STANDARD 20)

add_executable(monopoly-junior
        main.cpp
        src/Cases.h
        src/Couleurs.h
        src/Carte.h
        src/rtti.hpp
        src/Cases.cpp
        src/linked_list/LinkedList.cpp
        src/linked_list/LinkedList.h
        src/linked_list/Link.h
        src/Decks.h
        src/Plato.cpp
        src/Joueur.h
        src/Jeu.cpp
        src/Jeu.h
        src/Joueur.cpp
)
