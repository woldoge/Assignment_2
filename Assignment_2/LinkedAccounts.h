#pragma once
#include <iostream>
#include <string>
#include "Account.h"
#include "Item.h"
using namespace std;

class account_node
{
private:
	Account* data;
	account_node *next;
public:
	account_node(Account* data) { this->data = data; }
	~account_node() {}
	account_node* getNext() { return this->next; }
	void setNext(account_node* newNext) { this->next = newNext; }
	Account* getData() { return data; }
	void setData(Account* data) { data = data; }
};

class LinkedAccounts
{
account_node *head;
public:
	LinkedAccounts() { this->head = NULL; }
	~LinkedAccounts() {}
	void insertHead(Account* data);
	void removeHead();
	void append(Account* name);
	void removeNode(Account* name);
	void deleteList();
	Account* get_by_ID(string ID);
	void print_IDs();
	void display_accounts();
	void display_accounts(string rank);
	bool ID_is_in_list(string ID);
	void change_account(Account* old_account, Account* new_account);
};