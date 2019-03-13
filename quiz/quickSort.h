#include <vector>
using namespace std;

class quickSort{
private:
	int partition(vector<int>& a,int l,int r){
	auto pivot=a[r];
	auto i=l-1;
	for(int j=l;j<r;++j){
		if(a[j]<=pivot){
			i++;
			int temp=a[j];
			a[j]=a[i];
			a[i]=temp;
		}
	}
	int temp=a[i+1];
	a[i+1]=a[r];
	a[r]=temp;
	return i+1;
}

void QuickSort_helper(vector<int>& a, int l, int r){
	if(l<r){
		int p= partition(a,l,r);
		QuickSort_helper(a,l,p-1);
		QuickSort_helper(a,p+1,r);
	}
	return;
}

void QuickSort(vector<int>& a){
	int l=0;
	int r=a.size()-1;
	QuickSort_helper(a,l,r);
	return;
}


public:
	void operator()(vector<int>& a){
		QuickSort(a);
		return;
	}
	
};
