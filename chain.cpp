/*
 * chain.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#include "chain.h"
//#include <string>



template<class T>
chain<T>::chain(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
     throw std::invalid_argument("Initial capacity = " + std::to_string(initialCapacity) + " Must be > 0");
   firstNode = NULL;
   listSize = 0;
}


template<class T>
chain<T>::chain(const chain& theList)
{// Copy constructor.
   listSize = theList.listSize;

   if (0 == listSize)
   {// theList is empty
      firstNode = NULL;
      return;
   }
   chainNode<T>* sourceNode = theList.firstNode;
                    // node in theList to copy from
   firstNode = new chainNode<T>(sourceNode->element);
                    // copy first element of theList
   sourceNode = sourceNode->next;
   chainNode<T>* targetNode = firstNode;
                    // current last node in *this
   while (sourceNode != NULL)
   {// copy remaining elements
      targetNode->next = new chainNode<T>(sourceNode->element);
      targetNode = targetNode->next;
      sourceNode = sourceNode->next;
   }
   targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
   while (firstNode != NULL)
   {// delete firstNode
      chainNode<T>* nextNode = firstNode->next;
      delete firstNode;
      firstNode = nextNode;
   }
}

template<class T>
void chain<T>::checkIndex(int theIndex) const{
	if(theIndex < 0 || theIndex >=listSize){
		throw std::out_of_range("index = " + std::to_string(theIndex) + " size = " + std::to_string(listSize)); //C++11标准引入的
	}
}


template<class T>
T& chain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // move to desired node
   chainNode<T>* currentNode = firstNode;
   for (int i = 0; i < theIndex; i++)currentNode = currentNode->next;

   return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const{
  chainNode<T>* currentNode = firstNode;
   int index = 0;  // index of currentNode
   while (currentNode != NULL && currentNode->element != theElement){
     currentNode = currentNode->next;
      index++;
   }
  if (currentNode == NULL)
      return -1;
   else
      return index;
}



template<class T>
void chain<T>::insert(int theIndex, const T& theElement){
   if (theIndex != listSize)
	   checkIndex(theIndex);
   if (theIndex == 0)
      firstNode = new chainNode<T>(theElement, firstNode);
   else
   {  // find predecessor of new element
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; ++i) p = p->next;
      p->next = new chainNode<T>(theElement, p->next);
   }
   ++listSize;
}

template<class T>
void chain<T>::erase(int theIndex){
  checkIndex(theIndex);
  chainNode<T>* deleteNode;
   if (theIndex == 0){
     deleteNode = firstNode;
      firstNode = firstNode->next;
   }
   else
   {  // use p to get to predecessor of desired node
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; ++i) p = p->next;

      deleteNode = p->next;
      p->next = p->next->next; // remove deleteNode from chain
   }
   --listSize;
   delete deleteNode;
}

template<class T>
void chain<T>::output(std::ostream& out) const
{
   chainNode<T> *p = firstNode;
   out <<std::endl;
   while(p != NULL){
	   out << p->element <<" ";
	   p = p->next;
   }
   out << std::endl;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x){
	x.output(out);
	return out;
}

template <class T>
int chain<T>::iteratorRan::getIndex()const{
	chainNode<T> *p = originalNode;
	int index = 0;
	while(p != node){
		index++;
		p = p->next;
	}
	return index;
}

template <class T>
 bool chain<T>::iteratorRan::operator<(const iteratorRan right) const{
	return this->getIndex() < right.getIndex();
}
template <class T>
 bool chain<T>::iteratorRan::operator>(const iteratorRan right) const{
	return this->getIndex() > right.getIndex();
}
template <class T>
 bool chain<T>::iteratorRan::operator<=(const iteratorRan right) const{
	return this->getIndex() <= right.getIndex();
}
template <class T>
bool chain<T>::iteratorRan::operator>=(const iteratorRan right) const{
	return this->getIndex() >= right.getIndex();
}


template <class T>
T& chain<T>::iteratorRan::operator[](int index) const{
	chainNode<T> *p;
	p = originalNode;
	for(int i = 0; i < index; ++i) p = p->next;
	return p->element;

}
template <class T>
typename chain<T>::iteratorRan& chain<T>::iteratorRan::operator--(){   // preincrement
	chainNode<T> *p = originalNode;
	if(p == node) return *this;
	while(p->next != node) p = p->next;
	node = p;
	return *this;
}
template <class T>
typename chain<T>::iteratorRan chain<T>::iteratorRan::operator--(int){ // postincrement
	iteratorRan old = *this;
	chainNode<T> *p = originalNode;
	if(p == node) return old;
	while(p->next != node) p = p->next;
	old.node = p;
	return old;
}

template <class T>
typename chain<T>::iteratorRan& chain<T>::iteratorRan::operator+=(const int dist){
	chainNode<T> *p;
	p = node;
	for(int i = 0; i < dist; ++i) p = p->next;
	node = p;
	return *this;
}
template <class T>
typename chain<T>::iteratorRan& chain<T>::iteratorRan::operator-=(const int dist){
	chainNode<T> *p;
	p = originalNode;
	int index = this->getIndex();
	index -= dist;
	p = originalNode;
	for(int i = 0; i < index; i++) p =p->next;
	node = p;
	return *this;;
}
template <class T>
typename chain<T>::iteratorRan chain<T>::iteratorRan::operator+(const int dist){
	typename chain<T>::iteratorRan temp = *this;
	chainNode<T> *p = node;
	for(int i = 0; i < dist;i++) p =p->next;
	temp.node = p;
	return temp;
}
template <class T>
typename chain<T>::iteratorRan chain<T>::iteratorRan::operator-(const int dist){
	typename chain<T>::iteratorRan temp = *this;
	chainNode<T> *p = originalNode;
	int index = this->getIndex();
	index -= dist;
	p = originalNode;
	for(int i = 0; i < index; i++) p =p->next;
	temp.node = p;
	return temp;
}

/*
//两个指针相差的距离（单位：数据元素）
template <class T>
typename std::iterator<std::random_access_iterator_tag,T>::difference_type chain<T>::iteratorRan::operator-(const  iteratorRan right)const{
	return this->getIndex() - right.getIndex();
}
*/


//两个指针相差的距离（单位：数据元素）
template <class T>
typename chain<T>::iteratorRan::difference_type chain<T>::iteratorRan::operator-(const  iteratorRan right)const{
	return this->getIndex() - right.getIndex();
}
