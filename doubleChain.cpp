#include "doubleChain.h"
#include "linearList.h"
#include <string>

template<class T>
doubleChain<T>::doubleChain()
{// Constructor.
    firstNode = NULL;
    listSize = 0;
}

template<class T>
doubleChain<T>::doubleChain(int initialCapacity)
{// Constructor.
    if (initialCapacity < 1)
        throw std::invalid_argument("Initial capacity = " + std::to_string(initialCapacity) + " Must be > 0");
    firstNode = NULL;
    listSize = 0;
}

template<class T>
doubleChain<T>::doubleChain(const doubleChain& theList)
{// Copy constructor.
    listSize = theList.listSize;

    if (0 == listSize)
    {// theList is empty
        firstNode = NULL;
        return;
    }
    dchainNode<T>* sourceNode = theList.firstNode;
                    // node in theList to copy from
    firstNode = new dchainNode<T>(sourceNode->element);
                    // copy first element of theList
    sourceNode = sourceNode->next;
    dchainNode<T>* targetNode = firstNode;
    dchainNode<T>* k;
    int i;

    for(i = 1; i<listSize; i++)
    {// copy remaining elements
        k = new dchainNode<T>(sourceNode->element);
        targetNode->next = k;
        k->last = targetNode;
        targetNode = k;
        sourceNode = sourceNode->next;
    }
    targetNode->next = firstNode; // end the chain
    firstNode->last = targetNode;
}

template<class T>
doubleChain<T>::~doubleChain()
{// Chain destructor. Delete all nodes in chain.
    firstNode->last->next = NULL;
    while (firstNode != NULL)
    {// delete firstNode
        dchainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void doubleChain<T>::checkIndex(int theIndex) const{
	if(theIndex < 0 || theIndex >=listSize){
		throw std::out_of_range("index = " + std::to_string(theIndex) + " size = " + std::to_string(listSize));
	}
}

template<class T>
T& doubleChain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

   // move to desired node
    dchainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)currentNode = currentNode->next;

    return currentNode->element;
}

template<class T>
int doubleChain<T>::indexOf(const T& theElement) const{
    dchainNode<T>* currentNode = firstNode;
    int index = 0;  // index of currentNode
    while (index < listSize && currentNode->element != theElement){
        currentNode = currentNode->next;
        index++;
    }
    if (index >= listSize )
        return -1;
    else
        return index;
}

template<class T>
void doubleChain<T>::insert(int theIndex, const T& theElement){
    if (theIndex != listSize)
        checkIndex(theIndex);
    if (listSize == 0)
    {
        firstNode = new dchainNode<T>(theElement);
        firstNode->next = firstNode;
        firstNode->last = firstNode;
    }

    else
    {  // find predecessor of new element
        dchainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; ++i) p = p->next;
        dchainNode<T>* k = new dchainNode<T>(theElement);
        k->next = p->next;
        k->next->last = k;
        p->next = k;
        k->last = p;
    }
    ++listSize;
}

template<class T>
void doubleChain<T>::erase(int theIndex){
    checkIndex(theIndex);
    dchainNode<T>* deleteNode;
      // use p to get to predecessor of desired node
    dchainNode<T>* p = firstNode;
    for (int i = 0; i < theIndex - 1; ++i) p = p->next;

    deleteNode = p->next;
    deleteNode->last->next = deleteNode->next;
    deleteNode->next->last = deleteNode->last;

    --listSize;
    delete deleteNode;
}

template<class T>
void doubleChain<T>::output(std::ostream& out) const
{
   dchainNode<T> *p = firstNode;
   out <<std::endl;
   out << p->element <<" ";
   p=p->next;
   while(p != firstNode){
	   out << p->element <<" ";
	   p = p->next;
   }
   out << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const doubleChain<T>& x){
	x.output(out);
	return out;
}
