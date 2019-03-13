//  DNode.h
//  doubly_linked
//
//

#ifndef DNode_h
#define DNode_h

#include <memory>
#include "Node.hpp"

template <typename T>
class DNode : public Node<T>
{
public:
    DNode();            //default constructor
    DNode(T x);         //constructor with new value
    virtual ~DNode();   //destructor
    
    T val;
    std::shared_ptr<DNode<T> > next;    //point to the next one
    std::shared_ptr<DNode<T> > prev;    //point to the previous one
};


#endif /* DNode_h */
