#pragma once
#include "priorityqueue.h"
#include "Passenger.h"
#include "PQnode.h"

template<class T>
class Modified_Priority_Queue : public PriorityQueue<Passenger*>
{

public:
	bool remove_Specific(int id);
	bool Dequeue_First(char type, T& ptr); // dequeues the first item of a specific type and returns a ptr to it
};


template<class T>
inline bool Modified_Priority_Queue<T>::remove_Specific(int id)
{
	PQNode<Passenger*>* temp = frontPtr;
	PQNode<Passenger*>* advanced = frontPtr->getNext();
	Passenger* p_ptr = nullptr;
	int temp_id;

	p_ptr = temp->getItem();
	temp_id = p_ptr->get_id();
	if (temp_id == id) 
	{
		PQNode<Passenger*>* deleted = frontPtr;
		frontPtr->setNext(frontPtr->getNext());

	}

	while (!isEmpty()) {
		p_ptr = advanced->getItem();
		temp_id = p_ptr->get_id();
		if (temp_id == id) {
			temp->setNext(advanced->getNext());
			delete advanced;
			return true;
		}
		else {
			advanced->setNext(advanced->getNext());
			temp->setNext(temp->getNext());
		}
	}
	return false;
}



template<class T>
inline bool Modified_Perority_Queue<T>::Dequeue_First(char type,T& ptr)


{
PQNode<Passenger*>* temp = frontPtr;
PQNode<Passenger*>* advanced = frontPtr->getNext();
	Passenger* p_ptr = nullptr;
	char temp_type;

	p_ptr = temp->getItem();
	temp_type = p_ptr->get_type();



	if (temp_type == type)
	{
	    PQNode<Passenger*>* deleted = frontPtr;
		frontPtr->setNext(frontPtr->getNext());
		
	}

	while (!isEmpty()) 
  {		p_ptr = advanced->getItem();
	    temp_type = p_ptr->get_type();

		if (temp_type == char)
		{
			temp->setNext(advanced->getNext());
			ptr = advanced;
			delete advanced;
			
		}
		else 
		{
			advanced->setNext(advanced->getNext());
			temp->setNext(temp->getNext());
		}
}
	return false;
}