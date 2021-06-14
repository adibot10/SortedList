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
    class const_iterator;

public:
    SortedList()=default; //c'tor
    ~SortedList();
    SortedList(const SortedList sorted_list);
    SortedList& operator=(const SortedList& sorted_list);
    void insert(int data);
    void putStart(Node new_node);
    void putMiddle(Node ptr, Node new_node);
    void putEnd(Node ptr, Node new_node);
    int length ();
    void remove();
};

//copy c'tor
SortedList::SortedList(const SortedList& sorted_list):
        head(sorted_list.head), size(sorted_list.size)
{
}


SortedList& SortedList::operator=(const SortedList& sorted_list)
{
    if(this==&sorted_list)
    {
        return *this;
    }
    head=sorted_list.head;
    size=sorted_list.size;
    return *this;
}


void SortedList::insert(int data)
{
    Node* new_node= new Node;
    new_node->value=data;
    new_node->next= nullptr;
    if(head== nullptr)
    {
        head=new_node;
        size++;
        return;
    }
    Node* ptr=head;
    if(head->value >= new_node->value)
    {
        putStart(new_node);
        return;
    }
    while (ptr->next!= nullptr && ptr->next->value <= new_node->value)
    {
        ptr=ptr->next;
    }
    if(ptr->next== nullptr)
    {
        putEnd(ptr, new_node);
        return;
    }
    if ( ptr->next->value > new_node->value)
    {
        putMiddle(ptr, new_node);
        return;
    }

}

void SortedList::putStart(Node* new_node)
{
    *new_node->next = head;
    head = new_node;
    size++;
}

void SortedList::putMiddle(Node* ptr, Node* new_node)
{
    *new_node->next = *ptr->next;
    *ptr->next = new_node;
    size++;
}

void SortedList::putEnd(Node* ptr, Node* new_node)
{
    *new_node->next = nullptr;
    *ptr->next = new_node;
    size++;
}

void SortedList::remove(SortedList::const_iterator iterator)
{
    const_iterator* ptr=head;
    if(ptr==iterator)
    {
        head=head->next;
        ptr->iterator= nullptr;
    }
    while(!(ptr->next==iterator)&&(!(ptr->next== nullptr)))
    {
        ptr++;
    }
    if()
}




int SortedList::length()
{
    return size;
}

SortedList SortedList:: filter(bool (*predict)(Node))
{

}

const_iterator








/////////////////////////////////////////////////////////////////////////////
class SortedList::const_iterator
{
    Node* iterator;
public:
    const_iterator()=default;
    ~const_iterator();
    const_iterator(const const_iterator new_iterator);
    const_iterator& operator=(const const_iterator& new_iterator);
    void operator++();
    bool operator==(const const_iterator& new_iterator);
    friend class SortedList;
};

SortedList::const_iterator::const_iterator(const const_iterator& new_iterator):
        iterator(new_iterator.iterator);
{
}

const_iterator& SortedList::const_iterator::operator=(const const_iterator& new_iterator)
{
    if(this==&new_iterator)
    {
        return *this;
    }
    iterator=new_iterator.iterator;
    return *this;
}


void SortedList::const_iterator::operator++()
{
    if(iterator== nullptr)
    {
        throw std::out_of_range;
    }
    iterator=iterator->next;
}


bool SortedList::const_iterator::operator==(const const_iterator& new_iterator)
{
    if(iterator==new_iterator)
    {
        return true;
    }
    /*if (!(iterator->value < new_iterator.iterator->value)&&!(new_iterator.iterator->value < iterator->value))
    {
        return true;
    }*/
    return false;
}

const int& SortedList::const_iterator::operator*()
{
    const int a=iterator->value;
    return &a;
}



#endif //SORTEDLIST_SORTEDLIST_H
