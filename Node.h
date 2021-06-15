//
// Created by Adi on 13/06/2021.
//

#ifndef SORTEDLIST_NODE_H
#define SORTEDLIST_NODE_H
#include "sortedList.h"

class Node
{
    int value;
    Node *next;

public:
    explicit Node(const int& value, Node *next = nullptr);
    ~Node() = default;
    const int& getValue() const;

    void setNext(Node *next);

    Node *getNext() const;
};

const int& Node::getValue() const
{
    return value;
}

void Node::setNext(Node *next)
{
    this->next = next;
}

Node* Node::getNext() const
{
    return next;
}

Node::Node(const int &value, Node *next) : value(value), next(next)
{
}
///


#endif //SORTEDLIST_NODE_H
