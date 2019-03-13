#include "Node.hpp"

template<typename T>
Node<T>::Node(){
}

template<typename T>
Node<T>::~Node(){
}

template<typename T>
Node<T>::Node(T x):val(x){
	next=nullptr;
}