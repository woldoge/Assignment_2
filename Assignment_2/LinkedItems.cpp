#include <iostream>
#include <string>
#include "LinkedItems.h"

using namespace std;

void LinkedItems::append(Item* data)
{
	if (this->head == NULL) { // If the list is empty
		this->head = new item_node(data);
		return;
	}
	item_node *currentPtr = this->head;
	while (currentPtr->getNext() != NULL) // Scanning through the lsit of data from head to tail
		currentPtr = currentPtr->getNext();
	currentPtr->setNext(new item_node(data));
	return;
}

void LinkedItems::insertHead(Item* data)
{
	item_node* temp = this->head;
	this->head = new item_node(data);
	this->head->setNext(temp);
	return;
}

void LinkedItems::removeHead()
{
	item_node *currentPtr = head->getNext();
	delete head;
	head = currentPtr;
}


void LinkedItems::removeNode(Item* data)
{
	item_node *currentPtr = this->head;
	if (currentPtr->getData() == data) // If data matched at the head
		this->removeHead();
	else
	{
		while ((currentPtr->getNext()->getData() != data) && (currentPtr->getNext()->getNext() != NULL)) { // Loop through the datas until get to the matched data or the tail
			currentPtr = currentPtr->getNext();
		}
		if (currentPtr->getNext()->getData() != data) // When the tail data is not matched
			cout << "Account not found" << endl;
		else
		{
			if (currentPtr->getNext()->getNext() == NULL) // When the next node is not tail
				this->removeNode(currentPtr->getData());
			else // When the next node is tail
			{
				item_node *tempPtr = currentPtr->getNext();
				currentPtr->setNext(tempPtr->getNext());
				delete tempPtr;
			}
		}
	}
}

Item* LinkedItems::get_by_ID(string ID) {
	item_node *currentPtr = this->head;
	while (currentPtr != NULL) { // Loop through the datas until get to the matched data or the tail
		if (currentPtr->getData()->get_ID() == ID) {
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
	}
	cout << "Cannot get data" << endl;
	return NULL;
}

void LinkedItems::deleteList()
{
	item_node *currentPtr = head;
	while (currentPtr != NULL) // Scanning through list from head to tail, delete each head and make the next item node become the head
	{
		currentPtr = currentPtr->getNext();
		delete head;
		head = currentPtr;
	}
	return;
}

void LinkedItems::display_IDs() {
	item_node* currentPtr = this->head;
	if (currentPtr == NULL){ // If the list is NULL
		cout << "None";
	}
	while (currentPtr != NULL) { // Scanning through the list from head to tail
		cout <<'[' << currentPtr->getData()->get_ID() << "] ";
		currentPtr = currentPtr->getNext(); // Moving to the next node
	}
	return;
}

void LinkedItems::display_items()
{
	item_node* currentPtr = this->head;
	while (currentPtr != NULL) { // Scanning through the list from head to tail
		currentPtr->getData()->display();
		cout << endl;
		currentPtr = currentPtr->getNext();
	}
	return;
}

bool LinkedItems::ID_is_in_list(string ID)
{
	item_node* current_Ptr = this->head;
	while (current_Ptr != NULL) {
		if (current_Ptr->getData()->get_ID() == ID) {
			return true;
		}
		current_Ptr = current_Ptr->getNext();
	}
	return false;
}

int LinkedItems::items_num()
{
	int num = 0;
	item_node* current_pointer = head;
	while (current_pointer != NULL) {
		num += 1;
		current_pointer = current_pointer->getNext();
	}
	return num;
}

void LinkedItems::display_OOS()
{
	item_node* current_Ptr = this->head;
	while (current_Ptr != NULL) {
		if (current_Ptr->getData()->get_loan_status() == "borrowed")
		{
			current_Ptr->getData()->display();
		}
		current_Ptr = current_Ptr->getNext();
	}
}
