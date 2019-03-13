#include "LinkedList.cpp"
#include "Node.cpp"
#include "ListIterator.cpp"
#include <iostream>
#include <functional>

using namespace std;

template<typename T>
void print(LinkedList<T> l){
	cout<<"print: ";
	auto it=l.Iterator();int i=0;
	while(it.HasNext() and i++<10){
		cout<<it.Next()<<" -> ";
	}
	cout<<endl;
	return;
}


int main(int argc, char **argv)
{
	cout<<"we defined a print function to test ListIterator"<<endl;
	LinkedList<int> l;
	int a=1,b=2,c=3,d=4;
	
	cout<<"Add 1, 2, 4: ";
	l.Add(a);l.Add(b);l.Add(d);print(l);
	
	cout<<"Get index 1: "<<l.Get(1)<<endl;
	
	cout<<"Index of 2: "<<l.IndexOf(b)<<endl;
	
	cout<<"Insert 3 at index 2: ";
	l.Insert(c,2);print(l);
	
	cout<<"Remove the first element: "<<l.Remove(0)<<endl;
	print(l);
	
	cout<<"Add 3: ";
	l.Add(c);
	cout<<"Size now is: ";
	cout<<l.Size()<<endl;
	print(l);
	
	
	return 0;
}
