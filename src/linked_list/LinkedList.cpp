//
// Created by romain on 23/05/25.
//

#include "LinkedList.h"
#include "../Joueur.h"

#include <stdexcept>

template<typename T>
Link<T>* LinkedList<T>::getLink(const int position) {
    if (position >= size() or position < -size()) {
        throw std::out_of_range("LinkedList::getLink");
    }
    Link<T> *link;
    if (position < 0) {
        link = lastLink;
        for (int i = -1; i > position; i--) {
            link = link->getPreviousLink();
        }
    } else {
        link = firstLink;
        for (int i = 0; i < position; i++) {
            link = link->getNextLink();
        }
    }
    return link;
}

template<typename T>
LinkedList<T>::LinkedList() : firstLink(nullptr), lastLink(nullptr), _size(0), size_dirty(false) {}

template<typename T>
int LinkedList<T>::size() {
    if (!size_dirty) return _size;

    Link<T> *link = firstLink;
    int size = 0;
    while (link != nullptr) {
        link = link->getNextLink();
        size++;
    }

    _size = size;
    size_dirty = false;

    return size;
}

template<typename T>
void LinkedList<T>::add(T value) {
    Link<T>* link = new Link<T>(value, this->lastLink, nullptr);

    size_dirty = true;

    if (this->lastLink!=nullptr) {
        this->lastLink->setNextLink(link);
    }
    this->lastLink = link;

    if (firstLink == nullptr) {
        firstLink = link;
    }
}

template<typename T>
void LinkedList<T>::insert(T value, const int position) {
    const int s = size();
    if (position < 0) {
        throw std::invalid_argument("Position must be positive");
    }
    if (position > s) {
        throw std::invalid_argument("Position must be between");
    }

    if (position == s) {
        // Just add it at the end of the LinkedList
        return add(value);
    }

    if (position == 0) {
        Link<T> *link = getLink(position);
        Link<T>* newLink = new Link<T>(value, nullptr, link);

        size_dirty = true;

        link->setPreviousLink(newLink);
        firstLink = newLink;
        return;
    }

    // At this point, we can say that the size is at least 2, and we're not at any extremities of the list.

    Link<T> *link = getLink(position);
    Link<T>* previousLink = link->getPreviousLink();

    Link<T>* newLink = new Link<T>(value, previousLink, link);

    size_dirty = true;

    link->setPreviousLink(newLink);
    previousLink->setNextLink(newLink);
}

template<typename T>
T LinkedList<T>::pop(const int position) {
    Link<T>* link = getLink(position);

    Link<T>* previousLink = link->getPreviousLink();
    Link<T>* nextLink = link->getNextLink();

    size_dirty = true;

    if (previousLink == nullptr) {
        // Link is the first link of the LinkedList
        firstLink = nextLink;
    } else {
        previousLink->setNextLink(nextLink);
    }

    if (nextLink == nullptr) {
        // Link is the last link of the LinkedList
        lastLink = previousLink;
    } else {
        nextLink->setPreviousLink(previousLink);
    }

    // Remove any refs so it could be GC'ed
    link->setNextLink(nullptr);
    link->setPreviousLink(nullptr);

    const T value = link->getData();

    delete link;

    return value;
}

template<typename T>
T LinkedList<T>::operator[](const int position) {
    return getLink(position)->getData();
}

class Case;
class Carte;
class Joueur;

template class LinkedList<Case*>;
template class LinkedList<Carte*>;
template class LinkedList<Joueur*>;