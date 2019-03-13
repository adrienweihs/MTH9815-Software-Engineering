#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

using namespace std;
using namespace boost::interprocess;

int main(int argc,char *argv[]) {
	// create a shared memory to store number
	shared_memory_object shm(create_only, "SharedMemo", read_write);

	// set the size to store a integer
	shm.truncate(100);
	
	// map memory to this region 
	mapped_region region(shm, read_write);
	
	// get an address and create a integer
	int *i = static_cast<int*>(region.get_address());
	*i = 998;
	
	// what we store in this memory
	cout<<"Server store an integer: "<<*i<<endl;
	
	return 0;
}
