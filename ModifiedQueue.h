#pragma once
#include "priorityqueue.h"
#include "Passenger.h"
#include "PQnode.h"

template<class T>
class ModifiedQueue : public LinkedQueue<Passenger*>
{

public:
	bool remove_Specific(int id);
	//bool Dequeue_First(string type,Passenger* ptr); // dequeues the first item of a specific type and returns a ptr to it
};

template<class T>
inline bool ModifiedQueue<T>::remove_Specific(int id)
{
	Node<Passenger*>* advanced = nullptr;
	Node<Passenger*>* temp = frontPtr;
	if (frontPtr!=nullptr)
	advanced = frontPtr->getNext();
	
	Passenger* p_ptr = nullptr;
	int temp_id;
	if (isEmpty())
		return false;
	if (temp != nullptr)
	{
		p_ptr = temp->getItem();
		temp_id = p_ptr->get_id();
	}
	if (temp_id == id) 
	{
		Node<Passenger*>* deleted = frontPtr;
		frontPtr = frontPtr->getNext();
		delete deleted;
		counter--;
		return true;

	}

	while (!isEmpty() && advanced) {
		p_ptr = advanced->getItem();
		temp_id = p_ptr->get_id();
		if (temp_id == id)
		{
			temp->setNext(advanced->getNext());
			delete advanced;
			counter--;
			return true;
		}
		else {
			advanced->setNext(advanced->getNext());
			temp->setNext(temp->getNext());
		}
	}
	return false;
}


//template<class T>
//inline bool ModifiedQueue<T>::Dequeue_First(string type,Passenger* ptr)
//
//
//{
//PQNode<Passenger*>* temp = frontPtr;
//PQNode<Passenger*>* advanced = frontPtr->getNext();
//	Passenger* p_ptr = nullptr;
//	string temp_type;
//	if (temp != nullptr)
//	{
//		p_ptr = temp->getItem();
//		temp_type = p_ptr->get_type();
//	}
//
//
//	if (temp_type == type)
//	{
//		PQNode<Passenger*>* deleted = frontPtr;
//		frontPtr = frontPtr->getNext();
//		ptr = deleted->getItem();
//		counter--;
//		return true;
//	}
//
//	while (!isEmpty()) 
//	{
//		if (advanced != nullptr)
//		{
//			p_ptr = advanced->getItem();
//			temp_type = p_ptr->get_type();
//		}
//		if (temp_type == type)
//		{
//			temp->setNext(advanced->getNext());
//			ptr = advanced->getItem();
//			counter--;
//			return true;
//		}
//		else 
//		{
//			advanced->setNext(advanced->getNext());
//			temp->setNext(temp->getNext());
//		}
//   }
//	return false;
//}