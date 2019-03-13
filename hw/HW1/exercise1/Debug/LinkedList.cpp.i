# 1 "LinkedList.cpp"
# 1 "/home/zecophy/Desktop/softwareEngineering/HW1/exercise1//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "LinkedList.cpp"
# 1 "LinkedList.hpp" 1
       

template<typename T>
class LinkedList
{
public:
 LinkedList();
 ~LinkedList();


 void Add(T& value);


 void Insert(T& value, int index);


 T& Get(int index);


 int IndexOf(T& value);


 T& Remove(int index);

};
# 2 "LinkedList.cpp" 2

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
}
