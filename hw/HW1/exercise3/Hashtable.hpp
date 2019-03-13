#pragma once
#include "Hasher.hpp"
#include "EqualityPredicate.hpp"
#include <list>
#include <vector>
#include <memory>

template <typename K, typename V>
class Hashtable
{
private:
	std::vector<std::list<std::pair<K, V>>> table;
	std::shared_ptr<Hasher<K> > hasher;
	std::shared_ptr<EqualityPredicate<K> > equalpred;
	
public:
	Hashtable(std::shared_ptr<Hasher<K> > hasher_, std::shared_ptr<EqualityPredicate<K> > equalpred_, int size);
	~Hashtable();
	
	void add(std::pair<K,V> pair);
	V getvalue(K key);

};

