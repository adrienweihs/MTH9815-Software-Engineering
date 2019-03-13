#pragma once
#include "Node.hpp"
#include "DNode.h"
#include "LinkedList.hpp"
#include "DoublyLinkedList.hpp"

template<typename T>
class ListIterator
{
private:
    std::shared_ptr<DNode<T> > now;
public:
	ListIterator();
	ListIterator(std::shared_ptr<DNode<T> > node);
	~ListIterator();
	
	//Node<T>* Get();
	
	// Return whether there is another element to return in this iterator
	bool HasNext();

	// Return the next element in this iterator
	T& Next();
	
	ListIterator<T>& operator=(ListIterator<T>& l);
};

