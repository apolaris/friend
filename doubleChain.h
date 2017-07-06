#include "linearList.h"
#include <iterator>
template <typename T>
struct dchainNode
{
    T element;
    dchainNode<T> *next;
    dchainNode<T> *last;
    dchainNode(){
        next = NULL;
        last = NULL;
        }
    dchainNode(const T& element){
        this->element = element;
        next = NULL;
        last = NULL;
    }

};




template<class T>
class doubleChain : public linearList<T>
{
    public:
        doubleChain();
        ~doubleChain();
        doubleChain(int initialCapacity);
        doubleChain(const doubleChain&);
        bool empty() const {return listSize == 0;}
        int size() const {return listSize;}
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out) const;

        int capacity() const {return 0;}

        class iterator;
        iterator begin() const{return iterator(firstNode);}
        iterator end() const{return iterator(firstNode);}


    protected:
        void checkIndex(int theIndex) const;
        dchainNode<T>* firstNode;  // pointer to first node in chain
        int listSize;             // number of elements in list

    public:
    class iterator :public std::iterator<std::forward_iterator_tag,T>
        {
        public:
                iterator(dchainNode<T>* theNode = NULL)
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
                iterator& operator--()   // preincrement
                        {node = node->last; return *this;}
                iterator operator++(int) // postincrement
                        {iterator old = *this;
                        node = node->next;
                        return old;
                        }
                iterator operator--(int) // postincrement
                        {iterator old = *this;
                        node = node->last;
                        return old;
                        }
            protected:
                dchainNode<T>* node;
        };  // end of iterator class
};
