//
// Created by romain on 23/05/25.
//

#ifndef LINK_H
#define LINK_H


template<typename T>
class Link {
private:
    T data;
    Link* previousLink;
    Link* nextLink;
public:
    Link(T data, Link *previousLink, Link *nextLink) : data(data), previousLink(previousLink), nextLink(nextLink) {}
    T getData() const {return this->data;};
    Link *getPreviousLink() {return this->previousLink;};
    Link *getNextLink() {return this->nextLink;};
    void setData(int value) {this->data = value;};
    void setPreviousLink(Link *link) {this->previousLink = link;};
    void setNextLink(Link *link) {this->nextLink = link;};
};



#endif //LINK_H
