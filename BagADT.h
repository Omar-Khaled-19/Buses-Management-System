#pragma once


template <class T>
class BagADT 
{
public:
	virtual int getCurrentSize() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool add(const T& newEntry) = 0;
	virtual bool remove(const T& anEntry) = 0;
	virtual void clear() = 0;
};


