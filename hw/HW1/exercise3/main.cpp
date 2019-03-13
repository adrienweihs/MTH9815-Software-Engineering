#include "Hashtable.cpp"
#include <iostream>

using namespace std;

// a concrete class example for testing
class myhasher :public Hasher<int>{
public:
	int hasher(int a) {
		return a % 5;
	}
};

// // a concrete class example for testing
class myequal :public EqualityPredicate<int> {
public:
	bool predicate(int a,int b){
		return a == b;
	}
};



int main(){
	
	myhasher hasher;
	myequal predicate;
	std::cout << predicate.predicate(1, 1) << std::endl;
	std::cout << predicate.predicate(1, 0) << std::endl;
	
	//auto phasher=make_shared<Hasher<int> >(hasher);
	//auto ppredicate=make_shared<EqualityPredicate<int> >(predicate);
	
	shared_ptr<Hasher<int> > phasher=make_shared<myhasher>();
	shared_ptr<EqualityPredicate<int> > ppredicate=make_shared<myequal>();

	Hashtable<int, int> mytable(phasher,ppredicate,5);
	std::pair<int, int> p1(41, 4);
	std::pair<int, int> p2(134, 5);
	std::pair<int, int> p3(491, 9);
	std::pair<int, int> p4(8, 7);
	std::pair<int, int> p5(52, 6);
	mytable.add(p1);
	mytable.add(p2);
	mytable.add(p3);
	mytable.add(p4);
	mytable.add(p5);
	std::cout << mytable.getvalue(491) << std::endl;
	std::cout << mytable.getvalue(8) << std::endl;
	std::cout << mytable.getvalue(52) << std::endl;
	std::cout << mytable.getvalue(41) << std::endl;
	std::cout << mytable.getvalue(134) << std::endl;
	
	
	return 0;
}