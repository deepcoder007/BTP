/*
 * configNodeIterator.h
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

#ifndef CONFIGNODEITERATOR_H_
#define CONFIGNODEITERATOR_H_

#include"constants.h"
#include"commons.h"

class configNode;

//  An interface for list used in the program
class List
{
public:
    virtual ~List();
    virtual bool isGPU()=0;
    virtual bool isEmpty()=0;
    virtual void insertNode(configNode* data)=0;
    virtual bool deleteNode(configNode* data)=0;
    virtual bool deleteAll()=0;
    virtual configNode* getHead()=0;
    virtual void moveHead()=0;
};

// For the CPU implementation
// NOTE: The list will be constructed in a circular fashion for more flexibility
struct Node
{
    configNode* info;
    Node* next;
    Node* prev;
};

// A link list to store the configNode structures -> I am implementing it as a circular list
// for better flexibility and for performance reasons
/*
 * TOOD: instead of using one Node to store one configNode,
 * it will be better to store multiple configNodes like 10-100
 * for better performance because it will help avoiding multiple
 * read-write.
 */
class linkList: public List
{
private:
    Node* head;
    void delete_head();                   // delete the head
public:
    linkList();
    ~linkList();
    bool isGPU();
    bool isEmpty();                       // For optimization and error handling reasons
    void insertNode(configNode* data);   // Insert this node to the top of the list
    bool deleteNode(configNode* data);   // Delete this node from this list, return true if successful
    bool deleteAll();                    // CAUTION: dangerous operation to perform
    Node* _getHead();                     // Returns the Node instead of the configNode
    configNode* getHead();                // Return the configNode at the head
    void moveHead();                      // Move to the next position
};

//------------------------ Iterator classes below this line -------------------------------------------------

// An interface for iterating over the configNodes, this iterator is not ahving the option of the lookback
class configNodeIterator
{
public:
    virtual ~configNodeIterator();
    virtual bool isGPU()=0;
    virtual bool hasNext()=0;
    virtual configNode* next()=0;
    virtual void pop()=0;
};

/*
 * The iterator class for iterating the linkLists we devised above
 */
class linkListIterator : public configNodeIterator
{
private:
    Node* head;        // NOTE: this is different from the head of the original list which is circular
    Node* curr;		   // The node where it is currently pointing
    bool flag;		   // A temporary flag
public:
    linkListIterator(linkList* lst);
    ~linkListIterator();
    bool isGPU();
    bool hasNext();
    configNode* next();
    void pop();
};

#endif /* CONFIGNODEITERATOR_H_ */
