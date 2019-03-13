#pragma once
#include "Node.hpp"
#include <stdexcept>

template<typename T>
class ListIterator;

template<typename T>
class LinkedList
{
private:
	std::shared_ptr<Node<T> > head;
	int size;
public:
	LinkedList();
	~LinkedList();
	
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

