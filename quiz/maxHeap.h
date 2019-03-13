#include <vector>
#include <iostream>

using namespace std;

class maxHeap{
private:
	vector<int> a;
	int size;
	
	int parent(int i){
		return i/2;
	}
	int left(int i){
		return 2*i;
	}
	int right(int i){
		return 2*i+1;
	}
	
	void max_heapify(int i){
		int l=left(i),r=right(i),largest;
		if(l<=size && a[l]>a[i])
			largest=l;
		else largest=i;
		if(r<=size && a[r]>a[largest])
			largest=r;
		
		if(largest!=i){
			int temp=a[i];
			a[i]=a[largest];
			a[largest]=temp;
			max_heapify(largest);
		}
		return;
	}

public:
	maxHeap(){
		size=0;
	}
	
	void Add(int n){
		a.push_back(n);
		size+=1;
		int index=size-1;
		int p=parent(index);
		while(index!=0 && a[index]>a[p]){
			int temp=a[index];
			a[index]=a[p];
			a[p]=temp;
			index=p;
			p=parent(index);
		}
		return;
	}
	
	int Remove(int index=0){
		if(size==0){
			cout<<"the heap is empty. CANNOT remove!"<<endl;
			return 0;
		}
		if(index>=size){
			cout<<"out of range. CANNOT remove!"<<endl;
			return 0;
		}
		int res=a[index];
		a[index]=a[size-1];
		size-=1;
		a.pop_back();
		max_heapify(index);
		return res;
	}
	
	void print_heap(){
		for(auto item:a){
			cout<<item<<",";
		}cout<<endl;
		return;
	}
	
};