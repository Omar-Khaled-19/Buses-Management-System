#pragma once
#include "priorityqueue.h"
#include "Passenger.h"
#include "PQnode.h"

template<class T>
class Modified_Perority_Queue : public PriorityQueue<Passenger*>
{

public:
	bool remove_Specific(int id);
};

template<class T>
inline bool Modified_Perority_Queue<T>::remove_Specific(int id)
{
	PQNode<Passenger*>* temp = frontPtr;
	PQNode<Passenger*>* advanced = frontPtr->getNext();
	Passenger* p_ptr = nullptr;
	int temp_id;

	p_ptr = temp->getItem();
	temp_id = p_ptr->get_id();
	if (temp_id == id) {
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