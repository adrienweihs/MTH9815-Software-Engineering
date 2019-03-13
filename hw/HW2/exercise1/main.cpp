#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib> //std::system
#include <cstddef>
#include <cassert>
#include <utility>
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
	
	using namespace boost::interprocess;
	typedef int MyType;


	std::cout << "daddy please input 1" << std::endl;
	std::cout << "child please input 2" << std::endl;
	int type;
	std::cin >> type;

	if (type == 1) {  //Parent process
					  //Remove shared memory on construction and destruction
		struct shm_remove
		{
			shm_remove() { shared_memory_object::remove("MySharedMemory"); }
			~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		} remover;

		//Construct managed shared memory
		managed_shared_memory segment(create_only, "MySharedMemory", 65536);

		//Create an object of MyType initialized to an int
		int integer;
		std::cout << "Please input an int into the shared memory" << std::endl;
		std::cin >> integer;
		
		MyType *instance = segment.construct<MyType>
			("Int instance")  //name of the object
			(integer);            //ctor first argument

								 

		std::cout <<"the int in the shared memory is:"<< integer<< std::endl;
		system("pause");
		


		//Check child has destroyed all objects
		while (segment.find<MyType>("Int instance").first) {
			using namespace std::chrono_literals; // C++14
			std::this_thread::sleep_for(2s);
		}

		std::cout << "The int has been deleted from the child program! Input anything to end the program." << std::endl;
		system("pause");

		return 0;
	
	}
	else {
		
		//Open managed shared memory
		managed_shared_memory segment(open_only, "MySharedMemory");

		std::pair<MyType*, managed_shared_memory::size_type> res;

		//Find the array
		res = segment.find<MyType>("Int instance");
		std::cout << "The int in shard memory is: "<<*res.first << std::endl;
		system("pause");
	
		//We're done, delete all the objects
		segment.destroy<MyType>("Int instance");

	}
	return 0;
}
