#pragma once
#include "bagadt.h"

template <class T>
class ArrayBag : public BagADT<T>
{

private:
	T bagArr[100];
	int count;

public:
	ArrayBag() {
		count = 0;
	}

	int getCurrentSize() const {
		return count;
	}

	bool isEmpty() const {
		if (count == 0)
			return true;
		return false;
	};

	bool add(const T& newEntry) {
		return true;       //to be edited
	};

	bool remove(const T& anEntry) {
		return true;       //to be edited
	};

	void clear() {

	};
};

