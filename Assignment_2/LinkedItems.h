#pragma once
#include <iostream>
#include <string>
#include "Item.h"
using namespace std;

class item_node
{
private:
	Item* data;
	item_node *next;
public:
	item_node(Item* data) { this->data = data; }
	~item_node() {}
	item_node* getNext() { return this->next; }
	void setNext(item_node* newNext) { this->next = newNext; }
	Item* getData() { return data; }
	void setData(Item* data) { data = data; }
};

class LinkedItems
{
	item_node *head;
public:
	LinkedItems() { this->head = NULL; }
	~LinkedItems() {}
	void insertHead(Item* data);
	void removeHead();
	void append(Item* name);
	void removeNode(Item* name);
	void deleteList();
	Item* get_by_ID(string ID);
	void display_IDs();
	void display_items();
	bool ID_is_in_list(string ID);
	int items_num();
	void display_OOS();
};