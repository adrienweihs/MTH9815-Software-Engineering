#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

using namespace std;
using namespace boost::interprocess;

int main(int argc,char *argv[]) {
	// create a shared memory to read number
	shared_memory_object shm(open_only, "SharedMemo", read_only);
	
	//Map the whole shared memory in this process
	mapped_region region(shm, read_only);
	
	// get what we stored in this memory
	int *i = static_cast<int*>(region.get_address());
	
	cout<<"Client fetch an integer: "<<*i<<endl;
	
	// remove the shared memory's name 
	shared_memory_object::remove("SharedMemo");

	return 0;
}
