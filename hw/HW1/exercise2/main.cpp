#include "LinkedList.cpp"
#include "Node.cpp"
#include "ListIterator.cpp"
#include "DNode.cpp"
#include "DoublyLinkedList.cpp"
#include <iostream>
#include <functional>

using namespace std;

template<typename T>
void print(T l){
	cout<<"print: ";
	auto it=l.Iterator();int i=0;
	while(it.HasNext() and i++<l.Size()){
		cout<<it.Next()<<" - ";
	}
	cout<<endl;
	return;
}


int main(int argc, char **argv)
{
    cout<<"*********************"<<endl;
	cout<<"we defined a print function to test ListIterator"<<endl;
	DoublyLinkedList<int> l;
	int a=1,b=2,c=3,d=4;
	
	cout<<"Add 1, 2, 4: ";
	l.Add(a);l.Add(b);l.Add(d);
    cout<<endl;
    print<DoublyLinkedList<int> >(l);
	
    cout<<"Get index 0: "<<l.Get(0)<<endl;
	cout<<"Get index 1: "<<l.Get(1)<<endl;
    cout<<"Get index 2: "<<l.Get(2)<<endl;
	
    cout<<"Index of 1: "<<l.IndexOf(a)<<endl;
	cout<<"Index of 2: "<<l.IndexOf(b)<<endl;
    cout<<"Index of 4: "<<l.IndexOf(d)<<endl;
	
    cout<<"*********************"<<endl;
    c = 33;
	cout<<"Insert 33 at index 2: ";
	l.Insert(c,2);print(l);
    cout<<"Insert 33 at index 0: ";
    l.Insert(c,0);print(l);
    
    cout<<"Get index 0: "<<l.Get(0)<<endl;
    cout<<"Get index 1: "<<l.Get(1)<<endl;
    cout<<"Get index 2: "<<l.Get(2)<<endl;
    cout<<"Get index 3: "<<l.Get(3)<<endl;
    cout<<"Get index 4: "<<l.Get(4)<<endl;
    
    //l.Insert(c,-1);print<DoublyLinkedList<int> >(l);
	cout<<"*********************"<<endl;
	cout<<"Remove the first element: "<<l.Remove(0)<<endl;
	print(l);
    cout<<"Remove the last element: "<< l.Remove(3) << endl;
    print(l);
    
    //to see after removing, if everything is ok.
    cout<<"*********************"<<endl;
    cout<<"Get index 0: "<<l.Get(0)<<endl;
    cout<<"Get index 1: "<<l.Get(1)<<endl;
    cout<<"Get index 2: "<<l.Get(2)<<endl;
    
    cout<<"Index of 1: "<<l.IndexOf(a)<<endl;
    cout<<"Index of 2: "<<l.IndexOf(b)<<endl;
    cout<<"Index of 33: "<<l.IndexOf(c)<<endl;
    
	
	return 0;
}
