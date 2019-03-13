#include "LinkedList.hpp"
#include <iostream>
using namespace std;

template<typename T>
LinkedList<T>::LinkedList()
{
	head=std::make_shared<Node<T> >();
	size=0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
}

// Add the specified element at the end of the list
template <typename T>
void LinkedList<T>::Add(T& value){
	auto curr=head;
	for(int i=0;i<size;i++)
		curr=curr->next;
		
	curr->next=std::make_shared<Node<T> >(value);
	
	++size;
	return;
}

// Add the specified element at the specified index
template <typename T>
void LinkedList<T>::Insert(T& value, int index){
	if(index>=size){
		throw std::out_of_range("Insert index out of range");
		return;
	}
	
	auto curr=head;
	for(int i=0;i<index;++i){
		curr=curr->next;
	}

	auto rest=curr->next;
	curr->next=std::make_shared<Node<T> >(value);
	curr->next->next=rest;
	++size;
	return;
}

// Get the element at the specified index
template <typename T>
T& LinkedList<T>::Get(int index){
	if(index>=size){
		throw std::out_of_range("Get index out of range");
	}
	
	auto curr=head;
	for(int i=0;i<index;++i){
		curr=curr->next;
	}
	
	return curr->next->val;
}

// Retrieve the index of the specified element (-1 if it does not exist in the list
template <typename T>
int LinkedList<T>::IndexOf(T& value){
	auto curr=head;
	int index=0;
	while(curr->next){
		curr=curr->next;
		if(curr->val==value){
			return index;
		}
		++index;
	}
	return -1;
}

// Remove the element at the specified index and return it
template <typename T>
T& LinkedList<T>::Remove(int index){
	if(index>=size){
		throw std::out_of_range("Remove index out of range");
	}
	
	auto curr=head;
	for(int i=0;i<index;++i){
		curr=curr->next;
		--index;
	}
	
	auto temp=curr->next;
	curr->next=curr->next->next;
	
	--size;
	return temp->val;
}

// Return the size of the list
template <typename T>
int LinkedList<T>::Size(){
	return size;
}


// Return an iterator on this list
template <typename T>
ListIterator<T> LinkedList<T>::Iterator(){
	ListIterator<T> res(head);
	return res;
}
