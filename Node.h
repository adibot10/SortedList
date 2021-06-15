//
// Created by Adi on 13/06/2021.
//

#ifndef SORTEDLIST_NODE_H
#define SORTEDLIST_NODE_H
#include "sortedList.h"

template <class T>
class Node
{
    T value;
    Node<T>* next;
public:
    explicit Node(const T& value, Node<T> *next_node = nullptr);
    ~Node() = default;
    const T& getValue() const;

    void setNext(Node<T> *next_node);

    Node<T> *getNext() const;
};

template<class T>
const T& Node<T>::getValue() const
{
    return value;
}

template<class T>
void Node<T>::setNext(Node<T>* next_node)
{
    next = next_node;
}

template<class T>
Node<T>* Node<T>::getNext() const
{
    return next;
}
template<class T>
Node<T>::Node(const T &value, Node<T>* next_node) : value(value), next(next_node)
{
}
///


#endif //SORTEDLIST_NODE_H
