#pragma once

template <typename K>
class EqualityPredicate
{
public:
	virtual bool predicate(K a, K b) = 0;

};

