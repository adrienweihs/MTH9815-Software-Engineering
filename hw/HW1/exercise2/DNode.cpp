//
//  DNode.cpp
//  doubly_linked
//
//

#include <stdio.h>
#include "DNode.h"

//default constructor
template<typename T>
DNode<T>::DNode(){}

//destructor
template<typename T>
DNode<T>::~DNode(){}

//constructor with new value
template<typename T>
DNode<T>::DNode(T x):val(x){
    next = nullptr;
    prev = nullptr;
}

