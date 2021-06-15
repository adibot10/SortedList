//
// Created by Adi on 13/06/2021.
//

#ifndef SORTEDLIST_SORTEDLIST_H
#define SORTEDLIST_SORTEDLIST_H
#include "Node.h"
using std::exception;
#include <stdexcept>


template <class T>
class SortedList
{
    Node<T>* head;
    int size;
    //friend class Node<T>*;
    void putStart(Node<T>* new_node);
    void putMiddle(Node<T>* previous_node, Node<T>* new_node);
    void clean();
public:
    class const_iterator;
    SortedList()=default; //c'tor
    ~SortedList();
    SortedList(const SortedList& sorted_list);
    SortedList& operator=(const SortedList& sorted_list);
    void insert(const T& data);
    void remove(const const_iterator& iterator);
    template<class Function>
    SortedList filter(Function predict) const;
    template<class Function>
    SortedList apply (Function function) const;
    int length() const;
    const_iterator begin() const;
    const_iterator end() const;
};

template <class T>
class SortedList<T>::const_iterator
{
    Node<T>* node;
    explicit const_iterator(Node<T>* node);

public:
    const_iterator(const const_iterator& iterator) = default;
    const_iterator& operator=(const const_iterator& other) = default;
    ~const_iterator() = default;
    friend class SortedList;
    const_iterator& operator++();
    const_iterator operator++(int);
    const T& operator*() const;
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
};

//copy c'tor
template <class T>
SortedList<T>::SortedList(const SortedList<T>& sorted_list):
        head(nullptr), size(0)
{
    *this = sorted_list;
}
template <class T>
SortedList<T>::~SortedList()
{
    clean();
}
template <class T>
void SortedList<T>::clean()
{
    if (head == nullptr)
    {
        return;
    }
    Node<T>* temp=head;
    while (head->getNext()!= nullptr)
    {
        head=head->getNext();
        delete temp;
        temp=head;
    }
    delete temp;
    head = nullptr;
    size = 0;
}

template <class T>
SortedList<T>& SortedList<T>::operator=(const SortedList<T>& sorted_list)
{
    if(this==&sorted_list)
    {
        return *this;
    }
    clean();
    for (T value : sorted_list) {
        insert(value);
    }
    return *this;
}

template <class T>
void SortedList<T>::insert(const T& data)
{
    Node<T>* new_node = new Node<T>(data);
    if(head == nullptr || !(head->getValue() < new_node->getValue()))
    {
        putStart(new_node);
        return;
    }
    Node<T>* previous_node = head;
    while (previous_node->getNext() != nullptr && previous_node->getNext()->getValue() < new_node->getValue())
    {
        previous_node = previous_node->getNext();
    }
    putMiddle(previous_node, new_node);
}

template <class T>
void SortedList<T>::putStart(Node<T>* new_node)
{
    new_node->setNext(head);
    head = new_node;
    size++;
}

template <class T>
void SortedList<T>::putMiddle(Node<T>* previous_node, Node<T>* new_node)
{
    new_node->setNext(previous_node->getNext());
    previous_node->setNext(new_node);
    size++;
}

template <class T>
void SortedList<T>::remove(const SortedList::const_iterator& iterator)
{
    if(head==iterator.node)
    {
        head=head->getNext();
        delete iterator.node;
        return;
    }
    Node<T>* ptr=head;
    while(ptr->getNext()!=nullptr && ptr->getNext()!=iterator.node)
    {
        ptr=ptr->getNext();
    }
    ptr->setNext(ptr->getNext()->getNext());
    delete iterator.node;
}
template <class T>
int SortedList<T>::length() const
{
    return size;
}

template <class T>
template <class Function>
SortedList<T> SortedList<T>::filter(Function predict) const
{
    SortedList<T> sorted_list = SortedList<T>();
    for (T value : *this)
    {
        if (predict(value))
        {
            sorted_list.insert(value);
        }
    }
    return sorted_list;
}

template <class T>
template <class Function>
SortedList<T> SortedList<T>::apply (Function function) const
{
    SortedList<T> sorted_list=SortedList<T>();
    for (T value : *this)
    {
        sorted_list.insert(function(value));
    }
    return sorted_list;
}


template <class T>
typename SortedList<T>::const_iterator SortedList<T>::begin() const
{
    return const_iterator(head);
}
template <class T>
typename SortedList<T>::const_iterator SortedList<T>::end() const
{
    return const_iterator(nullptr);
}






/////////////////////////////////////////////////////////////////////////////
template <class T>
typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
{
    if(node == nullptr)
    {
        throw std::out_of_range("Out of range");
    }
    node = node->getNext();
    return *this;
}
template <class T>
typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    ++*this;
    return temp;
}

template <class T>
bool SortedList<T>::const_iterator::operator==(const const_iterator& other) const
{
    if(node == other.node)
    {
        return true;
    }
    return false;
}
template <class T>
const T& SortedList<T>::const_iterator::operator*() const
{
    return node->getValue();
}
template <class T>
SortedList<T>::const_iterator::const_iterator(Node<T> *node) : node(node)
{
}
template <class T>
bool SortedList<T>::const_iterator::operator!=(const SortedList<T>::const_iterator &other) const
{
    return !(*this == other);
}


#endif //SORTEDLIST_SORTEDLIST_H
