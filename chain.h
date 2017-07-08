/*
 * chain.h
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#ifndef SRC_CHAIN_H_
#define SRC_CHAIN_H_

#include "linearList.h"
template <typename T>
struct chainNode
{
   T element;
   chainNode<T> *next;//可以将chainNode<T>简写为chainNode，因为这是在class chainNode的作用域内

   chainNode() {next = NULL;}
   chainNode(const T& element){
	   this->element = element;
	   next = NULL;
   }
   chainNode(const T& element, chainNode* next)//可以将chainNode<T>简写为chainNode，因为这是在class chainNode的作用域内
   {
	   this->element = element;
	   this->next = next;
   }
};



template<class T>
class chain : public linearList<T>
{
   public:
      chain(int initialCapacity = 10);
      chain(const chain&);//可以将chain<T>简写为chain，因为这是在class chain的作用域内
      ~chain();
        bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(std::ostream& out) const;

	  int capacity() const {return 0;}//只是为了和arrayList保持一致，这个值应该很大，这里取0

	  class iterator;
	  iterator begin() const{return iterator(firstNode);}
	  iterator end() const{return iterator(NULL);}

	  class iteratorRan;
	  iteratorRan beginRan() const {return iteratorRan(firstNode,firstNode);}
	  iteratorRan endRan() const{
		  return iteratorRan(firstNode,NULL);
	  }

   protected:
      void checkIndex(int theIndex) const;
      chainNode<T>* firstNode;  // pointer to first node in chain
      int listSize;             // number of elements in list

   public:
   class iterator :public std::iterator<std::forward_iterator_tag,T>
      {//前向迭代器，这是适合单向链表实现的一种迭代器

      public:
             //采用继承STL提供的迭代器基类 iterator，就不用像书上那样定义下面的参数
	   	   	 // typedefs required by C++ for a forward iterator
             //typedef std::forward_iterator_tag iterator_category;
             //typedef T value_type;
             //typedef std::ptrdiff_t difference_type;
             //typedef T* pointer;
             //typedef T& reference;

             // constructor
             iterator(chainNode<T>* theNode = NULL)
                {node = theNode;}
             // dereferencing operators
              T& operator*() const {return node->element;}
              T* operator->() const {return &node->element;}

              // equality testing
              bool operator!=(const iterator right) const
                    {return node != right.node;}
              bool operator==(const iterator right) const
                    {return node == right.node;}
              // increment
              iterator& operator++()   // preincrement
                        {node = node->next; return *this;}
              iterator operator++(int) // postincrement
              	      {iterator old = *this;
              	       node = node->next;
              	       return old;
              	      }
         protected:
            chainNode<T>* node;
      };  // end of iterator class

   class iteratorRan :public std::iterator<std::random_access_iterator_tag,T>
       {//随机迭代器，只是为了说明怎样实现随机迭代器，对单向链表，这种迭代器效率太低，没有实用性
       public:
              // constructor
              iteratorRan(chainNode<T>* firstNode,chainNode<T>* theNode)
                 {
            	  originalNode = firstNode;
            	  node = theNode;
                 }
              // dereferencing operators
               T& operator*() const {return node->element;}
               T* operator->() const {return &node->element;}

               // equality testing
               bool operator!=(const iteratorRan right) const
                     {return node != right.node;}
               bool operator==(const iteratorRan right) const
                     {return node == right.node;}


               // increment
               iteratorRan& operator++()   // preincrement
                         {node = node->next; return *this;}
               iteratorRan operator++(int) // postincrement
               	      {iteratorRan old = *this;
               	       node = node->next;
               	       return old;
               	      }
               //双向迭代器还必须实现
               iteratorRan& operator--();   // preincrement
               iteratorRan operator--(int); // postincrement

	           //随机迭代器必须再实现以下的操作
	           T& operator[](int index) const;
	           iteratorRan& operator+=(const int dist);
	           iteratorRan& operator-=(const int dist);
	           iteratorRan operator+(const int dist);
	           iteratorRan operator-(const int dist);

	           bool operator<(const iteratorRan right) const;
	           bool operator>(const iteratorRan right) const;
	           bool operator<=(const iteratorRan right) const;
	           bool operator>=(const iteratorRan right) const;


	           //使用using 引入基类中的数据类型
	           //因为iterator继承的基类是带参数的模版类，按照名字查找机制，不会到基类中去找difference_type
	           //请见c++ template书中的第九章。
	           //using typename std::iterator<std::random_access_iterator_tag,T>::difference_type;
	           //或
	           typedef 	typename std::iterator<std::random_access_iterator_tag,T>::difference_type   difference_type;

	           //两个指针相差的距离（单位：数据元素个数）
	          difference_type operator-(const iteratorRan right)const;

       protected:
	         int getIndex() const;
             chainNode<T>* node;
             chainNode<T>* originalNode;
       };  // end of iterator class


};
 #endif /* SRC_CHAIN_H_ */
