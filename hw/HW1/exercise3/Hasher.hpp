#pragma once

template <typename K>
class Hasher
{
public:
	virtual int hasher(K a) = 0;

};

