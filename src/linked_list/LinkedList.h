//
// Created by romain on 23/05/25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Link.h"

template <typename T>
class LinkedList {
private:
    Link<T> *getLink(int position);
    Link<T> *firstLink;
    Link<T> *lastLink;
    int _size;
    bool size_dirty;
public:
    LinkedList();
    int size();
    void add(T value);
    void insert(T value, int position);
    void remove(int position);
    T operator[](int position);
};



#endif //LINKEDLIST_H
