#include "Hashtable.hpp"

template <typename K, typename V>
Hashtable<K,V>::Hashtable(std::shared_ptr<Hasher<K> > hasher_, std::shared_ptr<EqualityPredicate<K> > equalpred_, int size):table(size)
{
	hasher=hasher_;
	equalpred=equalpred_;
}

template <typename K, typename V>
Hashtable<K,V>::~Hashtable()
{
}

template <typename K, typename V>
void Hashtable<K,V>::add(std::pair<K, V> pair) {
	int position = hasher->hasher(pair.first);
	std::list<std::pair<K, V>> currlist = table[position];
	for (auto pairintable : currlist) {
		if (equalpred->predicate(pair.first, pairintable.first)) {
			return;
		}
	}
	table[position].push_back(pair);
	 
	return;
}


template <typename K, typename V>
V Hashtable<K, V>::getvalue(K key) {	
	int position = hasher->hasher(key);
	std::list<std::pair<K, V>> currlist = table[position];
	for (auto pairintable : currlist) {
		if (equalpred->predicate(key,pairintable.first)) {
			return pairintable.second;
		}
	}
	 
	return V();
}