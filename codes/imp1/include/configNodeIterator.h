
#ifndef CONFIG_NODE_ITERATOR
#define CONFIG_NODE_ITERATOR

//  An interface for list used in the program
class List
{
public:
    List();                             // A defunct constructor
    virtual bool isGPU()=0;
    virtual bool isEmpty()=0;
    virtual void insertNode(configNode* data)=0;
    virtual bool deleteNode(configNode* data)=0;
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
    configNode* getHead();                // Return the node at the head
    void moveHead();                      // Move to the next position
};

//------------------------ Iterator classes below this line -------------------------------------------------

// An interface for iterating over the configNodes, this iterator is not ahving the option of the lookback
class configNodeIterator
{
public:
    configNodeIterator();                  // defunct constructor
    virtual bool isGPU()=0;
    virtual bool hasNext()=0;             
    virtual configNode* next()=0;
    virtual void pop()=0;
};

class linkListIterator : public configNodeIterator 
{
private:
    linkList* list;
    Node* head;             // NOTE: this is different from the head of the original list which is circular
public:
    linkListIterator(linkList* lst);
    ~linkListIterator();
    bool isGPU();
    bool hasNext();
    configNode* next();
    void pop();
};

#endif
