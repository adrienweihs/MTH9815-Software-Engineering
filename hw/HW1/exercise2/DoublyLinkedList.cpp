#include "DoublyLinkedList.hpp"
#include "LinkedList.hpp"
#include <iostream>
using namespace std;


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{//default constructor
    head=std::make_shared<DNode<T> >();
    tail=std::make_shared<DNode<T> >();
    size=0;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){}


// Add the specified element at the end of the list
template <typename T>
void DoublyLinkedList<T>::Add(T& value){
    auto curr=head;
    //update curr to the end
    for(int i=0;i<size;i++)
        curr=curr->next;
    
    //update the linked list to the new one
    curr->next=std::make_shared<DNode<T> >(value);
    tail = curr->next;
    tail->prev = curr;
    
    //increase the size by one
    ++size;
    return;
}


// Add the specified element at the specified index
template <typename T>
void DoublyLinkedList<T>::Insert(T& value, int index){
    //If the index is out of range, throw an error
    if(index >= size || index < 0){
        throw std::out_of_range("Insert index out of range");
        return;
    }
    
    std::shared_ptr<DNode<T> > curr = head;

    //find the specified index in the list
    if (index < size / 2) {//start from the head
        for(int i = 0; i < index;++i){
            curr = curr->next;
        }
    } else {//start from the end
        curr = tail;
        for(int i = size-1; i >= index;--i){
            curr=curr->prev;
        }
    }
    
    //update the list
    std::shared_ptr<DNode<T> > rest = curr->next;
    curr->next=std::make_shared<DNode<T> >(value);
    curr->next->next=rest;
    rest->prev = curr->next;
    rest->prev->prev = curr;
    
    //increase the size
    ++size;
    return;
}


// Get the element at the specified index
template <typename T>
T& DoublyLinkedList<T>::Get(int index){
    if(index >= size || index < 0)
        //if the index is out of range
        throw std::out_of_range("Get index out of range");
    else if (index == 0)
        //return the first element
        return head->next->val;
    else if (index == size - 1)
        //return the tail element
        return tail->val;
    
    std::shared_ptr<DNode<T> > curr = head;
    //find the specified index in the list
    if (index < size / 2) {//start from the head
        for(int i = 0; i < index;++i){
            curr = curr->next;
        }
    } else {//start from the tail
        curr = tail;
        for(int i = size-1; i >= index;--i){
            curr=curr->prev;
        }
    }
    
    return curr->next->val;
}


// Retrieve the index of the specified element (-1 if it does not exist in the list
template <typename T>
int DoublyLinkedList<T>::IndexOf(T& value){
    auto curr=head;
    int index=0;
    
    while(curr->next!=nullptr){
        curr = curr->next;
        if(curr->val==value){
            return index;
        }
        ++index;
    }
    
    return -1;
}


// Remove the element at the specified index and return it
template <typename T>
T& DoublyLinkedList<T>::Remove(int index){
    if(index>=size||index<0){
        throw std::out_of_range("Remove index out of range");
    }
    
    std::shared_ptr<DNode<T> > curr = head;
    //find the specified index in the list
    if (index < size / 2) {//start from the head
        for(int i = 0; i < index;++i){
            curr = curr->next;
        }
    } else {//start from the end
        curr = tail;
        for(int i = size-1; i >= index;--i){
            curr=curr->prev;
        }
    }
    
    //the value which we want to remove
    auto temp=curr->next;
    
    //update the linked list
    if (curr -> next ->next == nullptr)
        tail = curr;
    else{
        curr -> next = curr -> next -> next;
        curr -> next -> prev = curr;
    }
    
    //decrese the size by 1
    --size;
    
    //return the removed value
    return temp->val;
}

// Return the size of the list
template <typename T>
int DoublyLinkedList<T>::Size(){
    return size;
}


// Return an iterator on this list
template <typename T>
ListIterator<T> DoublyLinkedList<T>::Iterator(){
    ListIterator<T> res(head);
    return res;
}


