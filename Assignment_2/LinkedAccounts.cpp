#include <iostream>
#include <string>
#include "LinkedAccounts.h"

using namespace std;

void LinkedAccounts ::append(Account* data)
{
	if (this->head == NULL) { // append the node of data to the head when there is no head in the list
		this->head = new account_node(data);
return;
	}
	account_node *currentPtr = this->head;
	while (currentPtr->getNext() != NULL) // Scanning through the list from head to tail
		currentPtr = currentPtr->getNext();
	currentPtr->setNext(new account_node(data));
	return;
}

void LinkedAccounts::insertHead(Account* data)
{
	account_node* temp = this->head;
	this->head = new account_node(data);
	this->head->setNext(temp);
	return;
}

void LinkedAccounts::removeHead()
{
	account_node *currentPtr = head->getNext();
	delete head;
	head = currentPtr;
}


void LinkedAccounts::removeNode(Account* data)
{
	account_node *currentPtr = this->head;
	if (currentPtr->getData() == data)
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
			if (currentPtr->getNext()->getNext() == NULL) // When the data is not tail
				this->removeNode(currentPtr->getData());
			else // When the data is tail
			{
				account_node *tempPtr = currentPtr->getNext();
				currentPtr->setNext(tempPtr->getNext());
				delete tempPtr;
			}
		}
	}
}

Account* LinkedAccounts::get_by_ID(string ID) {
	account_node *currentPtr = this->head;
	while (currentPtr != NULL) { // Loop through the datas until get to the matched data or the tail
		if (currentPtr->getData()->get_ID() == ID) {
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
	}
	cout << "Cannot get data" << endl;
	return NULL;
}

void LinkedAccounts::deleteList()
{
	account_node *currentPtr = head;
	while (currentPtr != NULL) // Scanning through the list from head to tail, delete each head and make the next node become the head
	{
		currentPtr = currentPtr->getNext();
		delete head;
		head = currentPtr;
	}
}

void LinkedAccounts::print_IDs() {
	account_node* currentPtr = this->head;
	cout << currentPtr->getData()->get_ID() << endl;
	while (currentPtr->getNext() != NULL) {
		currentPtr = currentPtr->getNext();
		cout << currentPtr->getData()->get_ID() << endl;
	}
	return;
}

void LinkedAccounts::display_accounts()
{
	account_node* currentPtr = this->head;
	while (currentPtr != NULL) {
		currentPtr->getData()->display();
		cout << endl << endl;
		currentPtr = currentPtr->getNext();
	}
}

bool LinkedAccounts::ID_is_in_list(string ID)
{
	account_node* currentPtr = this->head;
	while (currentPtr != NULL) {
		if (currentPtr->getData()->get_ID() == ID) {
			return true;
		}
		currentPtr = currentPtr->getNext();
	}
	return false;
}
