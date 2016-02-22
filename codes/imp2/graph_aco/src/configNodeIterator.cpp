/*
 * configNodeIterator.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

// Implementation  of the config node Iterators
#include"configNodeIterator.h"
#include"configNode.h"
#include<iostream>
using namespace std;

List::~List()
{
	// TODO : Trivial code
}


// A non-trivial constructor
linkList::linkList()
{
    head = NULL;   // to avoid dangling pointers
}

// CAUTION: possible point for memory leak
linkList::~linkList()
{
    while( head != NULL )
        delete_head();
}

void linkList::delete_head()
{
    if( head->next == head && head->prev == head ) // i.e. single element list
    {
        delete head->info;
        delete head;
        head = NULL;
    } else {
        Node* tmp = head->next;
        tmp->prev = head->prev;
        tmp->prev->next = tmp;
        delete head->info;
        delete head;
        head = NULL;
    }
}

bool linkList::isGPU()
{   return false;   }

bool linkList::isEmpty()
{
    if( head == NULL )
        return true;
    else
        return false;
}

void linkList::insertNode(configNode* data)
{
    if( head == NULL ) {
        head = new Node;
        head->info = data;
        head->prev = head;
        head->next = head;
    } else {
        Node* tmp = new Node;
        tmp->info = data;
        tmp->next = head;
        tmp->prev = head->prev;
        tmp->prev->next = tmp;
        head->prev = tmp ;
        head = tmp;
    }
}

bool linkList::deleteNode(configNode* data)
{
    if(data == head->info) {
        delete_head();
        return true;
    }
    Node* tmp = head->next;
    while( tmp != head )
    {
        if( data == head->info ) {
            delete_head();
            return true;
        } else {
            tmp = tmp->next;
        }
    }
    return false;
}

bool linkList::deleteAll()
{
    while( head != NULL )
        delete_head();
    return true;
}

// Returns the "Node" containing the head
Node* linkList::_getHead()
{
    return head;
}

// Returns the "configNode" containing the head
configNode* linkList::getHead()
{
    return head->info;
}

void linkList::moveHead()
{
    head=head->next;
}

//------------------------- Implementation of the Iterator classes below this line --------------------------

configNodeIterator::~configNodeIterator()
{
	// TODO : trivial code
}

linkListIterator::linkListIterator(linkList* lst)
{
    list=lst;
    head = lst->_getHead();
}

// TRIVIAL , for security and completeness purpose
linkListIterator::~linkListIterator()
{
    list = 0;
    head = 0;
}

bool linkListIterator::isGPU()
{
    return false;
}

bool linkListIterator::hasNext()
{
    if( list->_getHead()->next == head )
        return false;
    else
        return true;
}

configNode* linkListIterator::next()
{
    return list->getHead();
}

void linkListIterator::pop()
{
    list->moveHead();
}




