#include "ListIterator.hpp"

template <typename T>
ListIterator<T>::ListIterator()
{
}

template <typename T>
ListIterator<T>::ListIterator(std::shared_ptr<DNode<T> > node){
	now = node;
}


template <typename T>
ListIterator<T>::~ListIterator()
{
}

// Return whether there is another element to return in this iterator
template <typename T>
bool ListIterator<T>::HasNext(){
	if(now->next!=nullptr)
		return true;
	else
		return false;
}

// Return the next element in this iterator
template <typename T>
T& ListIterator<T>::Next(){
	now=now->next;
	return now->val;
}


template<typename T>
ListIterator<T>& ListIterator<T>::operator=(ListIterator<T>& l){
	now=l.now;
	return *this;
}

