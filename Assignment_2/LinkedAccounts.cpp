#include <iostream>
#include <string>
#include "LinkedAccounts.h"
#include <fstream>

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
	cout << "(*) [VIP]: VIP account" << endl;
	cout << "    [REG]: Regular account" << endl;
	cout << "    [GUE]: Guest account" << endl << endl;
}

void LinkedAccounts::display_accounts(string rank) {
	account_node* currentPtr = this->head;
	while (currentPtr != NULL) {
		if (currentPtr->getData()->get_rank() == rank) {
			currentPtr->getData()->display();
			cout << endl << endl;
		}
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

void LinkedAccounts::change_account(Account * old_account, Account * new_account)
{
	account_node* currentPtr = this->head;
	while (currentPtr != NULL) {
		if (currentPtr->getData() == old_account) {
			new_account->set_ID(currentPtr->getData()->get_ID());
			new_account->set_name(currentPtr->getData()->get_name());
			new_account->set_address(currentPtr->getData()->get_address());
			new_account->set_phone(currentPtr->getData()->get_phone());
			new_account->set_rental_num(currentPtr->getData()->get_rental_num());
			new_account->set_rental_list(currentPtr->getData()->get_rental_list());
			delete currentPtr->getData();
			currentPtr->setData(new_account);
			return;
		}
		currentPtr = currentPtr->getNext();
	}
	cout << "ERROR: Can not find this account in list." << endl;
}

bool LinkedAccounts::display_has_string(string text)
{
	bool found = false;
	account_node* current_pointer = this->head;
	while (current_pointer != NULL) {
		if (current_pointer->getData()->get_ID().find(text) != string::npos || current_pointer->getData()->get_name().find(text) != string::npos) {
			found = true;
			current_pointer->getData()->display();
			cout << endl;
		}
		current_pointer = current_pointer->getNext();
	}
	return found;
}

void LinkedAccounts::write_file(ofstream* my_file_)
{
	account_node* current_pointer = this->head;
	string rank;
	while (current_pointer != NULL) {
		*my_file_ << current_pointer->getData()->get_ID();
		*my_file_ << ',';
		*my_file_ << current_pointer->getData()->get_name();
		*my_file_ << ',';
		*my_file_ << current_pointer->getData()->get_address();
		*my_file_ << ',';
		*my_file_ << current_pointer->getData()->get_phone();
		*my_file_ << ',';
		*my_file_ << current_pointer->getData()->get_rental_num();
		*my_file_ << ',';
		rank = current_pointer->getData()->get_rank();
		rank[0] = toupper(rank[0]);
		*my_file_ << rank;
		*my_file_ << "\n";
		current_pointer->getData()->get_rental_list()->write_file(my_file_);
		current_pointer = current_pointer->getNext();
	}
}

bool LinkedAccounts::item_ID_in_c_list(string ID)
{
	account_node* current_account = this->head;
	while (current_account != NULL) {
		if (current_account->getData()->get_rental_list()->ID_is_in_list(ID)) {
			return true;
		}
		current_account = current_account->getNext();
	}
	return false;
}
