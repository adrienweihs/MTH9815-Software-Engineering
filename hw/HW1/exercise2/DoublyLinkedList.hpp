#pragma once
#include "DNode.h"
#include "LinkedList.hpp"
#include "DNode.h"

template<typename T>
class ListIterator;

template <typename T>
class DoublyLinkedList : public LinkedList<T>
{
private:
    std::shared_ptr<DNode<T> > head;           //head pointer
    std::shared_ptr<DNode<T> > tail;           //tail pointer
    int size;                                  //size of the doubly linked list
    
public:
	DoublyLinkedList();
	virtual ~DoublyLinkedList();
	
    // Add the specified element at the end of the list
    void Add(T& value);
    
    // Add the specified element at the specified index
    void Insert(T& value, int index);
    
    // Get the element at the specified index
    T& Get(int index);
    
    // Retrieve the index of the specified element (-1 if it does not exist in the list
    int IndexOf(T& value);
    
    // Remove the element at the specified index and return it
    T& Remove(int index);
    
    // Return an iterator on this list
    ListIterator<T> Iterator();
    
    // Return the size of the list
    int Size();
};

