#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{		
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "nullptr\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		if (Head == nullptr) {
			Node<T>* newnode = new Node<T>(data);
			Head = newnode;
		}
		Node<T>* newnodeptr = new Node<T>(data);
		Node<T>* curptr = Head;
		while (curptr->getNext()) {
			curptr = curptr->getNext();
		}
		curptr->setNext(newnodeptr);


	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key) {
		if (Head == nullptr) return false;

		Node<T>* curptr = Head;
		while (curptr) {
			if (curptr->getItem() == Key) return true;
			curptr = curptr->getNext();
		}
		return false;

	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value) {
		if (Head == nullptr) return 0;
		int count = 0;
		Node<T>* curptr = Head;
		while (curptr) {
			if (curptr->getItem() == value) count++; 
			curptr = curptr->getNext();
		}
		return count;

	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst() {
		if (Head) {
			Node<T>* curptr = Head;
			Head = Head->getNext();
			delete curptr;
			curptr = nullptr;
		}
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast() {
		if (Head == nullptr) {
			return;
		}
		if (Head->getNext() == nullptr) {
			delete Head; Head = nullptr;
		}
		Node<T>* curptr = Head;
		while (curptr->getNext()->getNext()) {
			curptr = curptr->getNext();
		}
		Node<T>* deletedptr = curptr->getNext();
		curptr->setNext(nullptr);
		delete deletedptr;
		deletedptr = nullptr;
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value) {
		if (Head == nullptr) {
			return false;
		}
		if (Head->getItem() == value) {
			if (Head->getNext() == nullptr) {
				delete Head; Head = nullptr;
				return true;
			}
			Node<T>* curr = Head; 
			Head = Head->getNext();
			delete curr; curr = nullptr;
			return true;
		}

		Node<T>* curptr = Head;
		Node<T>* advancedptr = Head->getNext();
		while (curptr) {
			if (advancedptr->getItem() == value) {

				curptr->setNext(advancedptr->getNext());
				delete advancedptr; advancedptr = nullptr;
				return true;
			}
			advancedptr = advancedptr->getNext();
			curptr = curptr->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value) {
		int count = 0;
		if (Head == nullptr) {
			return false;
		}
		if (Head->getNext() == nullptr) {
			if (Head->getItem() == value) {
				delete Head;
				Head = nullptr;
				return true;
			}
			return false;
		}
		
		while (Head->getItem() == value && Head != nullptr) {
			Node<T>* current = Head;
			Head = Head->getNext();
			delete current; 
			count++;
		}

		Node<T>* curptr = Head;
		Node<T>* advancedptr = Head->getNext();
		while (curptr->getNext()) {
			if (advancedptr->getItem() == value) {
				Node<T>* todelete = advancedptr;
				curptr->setNext(advancedptr->getNext());
				advancedptr = advancedptr->getNext();
					
					count++;
				}

			else {
				advancedptr = advancedptr->getNext();
				curptr = curptr->getNext();
			}
		}
		return ( count>=1 );
	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L

	void Merge(const LinkedList& L) {
		if (Head == nullptr) {
			Head = L.Head;
			return;
		}
		if (Head->getNext() == nullptr) {
			Head->setNext(L.Head);
				return;
		}
		Node<T>* curptr = Head;
		while (curptr) {
			curptr = curptr->getNext();
		}
		curptr = L.Head;
		return;
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		Node<T>* ptr1 = Head;
		Node<T>* ptr2 = nullptr;

		while (Head->getNext()) {

			Head = Head->getNext();
			ptr1->setNext(ptr2);
			ptr2 = ptr1;
			ptr1 = Head;
		}

		Head->setNext(ptr2);

	}
		
};

#endif	
