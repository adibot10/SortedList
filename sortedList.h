//
// Created by Adi on 13/06/2021.
//

#ifndef SORTEDLIST_SORTEDLIST_H
#define SORTEDLIST_SORTEDLIST_H
#include "Node.h"
using std::exception;
#include <stdexcept>

class SortedList
{
    Node* head;
    int size;
    //friend class Node*;
    void putStart(Node* new_node);
    void putMiddle(Node* previous_node, Node* new_node);
    void clean();
public:
    class const_iterator;
    SortedList()=default; //c'tor
    ~SortedList();
    SortedList(const SortedList& sorted_list);
    SortedList& operator=(const SortedList& sorted_list);
    void insert(const int& data);
    void remove(const const_iterator& iterator);
    template<class Function>
    SortedList filter(Function predict) const;
    template<class Function>
    SortedList apply (Function function) const;
    int length() const;
    const_iterator begin() const;
    const_iterator end() const;
};


class SortedList::const_iterator
{
    Node* node;
    explicit const_iterator(Node* node);

public:
    const_iterator(const const_iterator& iterator) = default;
    const_iterator& operator=(const const_iterator& other) = default;
    ~const_iterator() = default;
    friend class SortedList;
    const_iterator& operator++();
    const_iterator operator++(int);
    const int& operator*() const;
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
};

//copy c'tor
SortedList::SortedList(const SortedList& sorted_list):
        head(nullptr), size(0)
{
    *this = sorted_list;
}

SortedList::~SortedList()
{
    clean();
}

void SortedList::clean()
{
    if (head == nullptr)
    {
        return;
    }
    Node* temp=head;
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

SortedList& SortedList::operator=(const SortedList& sorted_list)
{
    if(this==&sorted_list)
    {
        return *this;
    }
    clean();
    for (int value : sorted_list) {
        insert(value);
    }
    return *this;
}


void SortedList::insert(const int& data)
{
    Node* new_node = new Node(data);
    if(head == nullptr || !(head->getValue() < new_node->getValue()))
    {
        putStart(new_node);
        return;
    }
    Node* previous_node = head;
    while (previous_node->getNext() != nullptr && previous_node->getNext()->getValue() < new_node->getValue())
    {
        previous_node = previous_node->getNext();
    }
    putMiddle(previous_node, new_node);
}

void SortedList::putStart(Node* new_node)
{
    new_node->setNext(head);
    head = new_node;
    size++;
}

void SortedList::putMiddle(Node* previous_node, Node* new_node)
{
    new_node->setNext(previous_node->getNext());
    previous_node->setNext(new_node);
    size++;
}

void SortedList::remove(const const_iterator& iterator)
{
    if(head==iterator.node)
    {
        head=head->getNext();
        delete iterator.node;
        return;
    }
    Node* ptr=head;
    while(ptr->getNext()!=nullptr && ptr->getNext()!=iterator.node)
    {
        ptr=ptr->getNext();
    }
    ptr->setNext(ptr->getNext()->getNext());
    delete iterator.node;
}

int SortedList::length() const
{
    return size;
}

template <class Function>
SortedList SortedList::filter(Function predict) const
{
    SortedList sorted_list = SortedList();
    for (int value : *this)
    {
        if (predict(value))
        {
            sorted_list.insert(value);
        }
    }
    return sorted_list;
}

template <class Function>
SortedList SortedList::apply (Function function) const
{
    SortedList sorted_list=SortedList();
    for (int value : *this)
    {
        insert (function(value));
    }
    return sorted_list;
}



SortedList::const_iterator SortedList::begin() const
{
    return const_iterator(head);
}

SortedList::const_iterator SortedList::end() const
{
    return const_iterator(nullptr);
}






/////////////////////////////////////////////////////////////////////////////
SortedList::const_iterator& SortedList::const_iterator::operator++()
{
    if(node == nullptr)
    {
        throw std::out_of_range("Out of range");
    }
    node = node->getNext();
    return *this;
}

SortedList::const_iterator SortedList::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    ++*this;
    return temp;
}


bool SortedList::const_iterator::operator==(const const_iterator& other) const
{
    if(node == other.node)
    {
        return true;
    }
    return false;
}

const int& SortedList::const_iterator::operator*() const
{
    return node->getValue();
}

SortedList::const_iterator::const_iterator(Node *node) : node(node)
{
}

bool SortedList::const_iterator::operator!=(const SortedList::const_iterator &other) const
{
    return !(*this == other);
}


#endif //SORTEDLIST_SORTEDLIST_H
