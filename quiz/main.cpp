#include <iostream>
#include "quickSort.h"
#include "maxHeap.h"

using namespace std;

int main(int argc, char **argv)
{
	vector<int> a={3,4,1,2,5};
	quickSort qs;
	qs(a);
	for(auto item:a){
		cout<<item<<",";
	}cout<<endl;
	
	cout<<endl<<endl;
	
	maxHeap heap;
	heap.Add(5);
	heap.print_heap();
	heap.Add(10);
	heap.Add(3);
	heap.Add(1);
	heap.Add(4);
	heap.Add(7);
	heap.print_heap();
	heap.Remove();
	heap.print_heap();
	heap.Remove();
	heap.print_heap();
	heap.Remove(2);
	heap.print_heap();
	heap.Remove(1);
	heap.print_heap();
	
	return 0;
}
