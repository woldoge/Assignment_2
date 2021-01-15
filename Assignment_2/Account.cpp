#include "Account.h"
#include <iostream>
#include <string>

using namespace std;

VIPAccount::VIPAccount(string ID, string name, string address, string phone) {
	this->ID = ID;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->customer_type = "VIP";
}
void VIPAccount::__borrow(Item* item) {
	if (item->borrow(1)) { // If there are enough cpoies to borrow
		this->rental_list->append(new Item(item->get_ID())); // Append a copy to rental list
		cout << "- DIO: Item is successfully borrowed." << endl;
		cout << "ROAD ROLLER DA! 10 points for you." << endl;
		this->point_balance += 10;
		this->rental_num = rental_list->items_num();
	}
	else { // If fail to borrow
		cout << "Yare Yare Daze, cannot borrow, no borrow no point." << endl;
	}
}
void VIPAccount::__return(Item* item) {}

void VIPAccount::display()
{
	cout << "[VIP] ";
	Account::display();
	cout << "Points: " << this->point_balance << endl;
}


RegularAccount::RegularAccount(string ID, string name, string address, string phone) {
	this->ID = ID;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->customer_type = "regular";
}
void RegularAccount::__borrow(Item* item) {
	Account::__borrow(item);
}
void RegularAccount::__return(Item* item) {}

void RegularAccount::display()
{
	cout << "[REG] ";
	Account::display();
}

GuestAccount::GuestAccount(string ID, string name, string address, string phone) {
	this->ID = ID;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->customer_type = "guess";
}
void GuestAccount::__borrow(Item* item) {
	if (this->rental_list->items_num() >= this->max_rent) {
		cout << "DIO: Tsk tsk! You already holding two items";
		return;
	}
	Account::__borrow(item);
}
void GuestAccount::__return(Item* item) {}

void GuestAccount::display()
{
	cout << "[GUE] ";
	Account::display();
}


void Account::display()
{
	cout << "ID: " << this->ID << " | Name: " << this->name << endl;
	cout << "Address: " << this->address << endl;
	cout << "Phone number: " << this->phone << endl;
	cout << "Number of rented items: " << this->rental_num << endl;
	cout << "Renting items: ";
	this->rental_list->display_IDs();
	cout << endl;
}


void Account::__borrow(string ID)
{;
	this->rental_list->append(new Item(ID));
	this->rental_num = rental_list->items_num();
}

void Account::__borrow(Item * item)
{
	if (item->borrow(1)) { // If there are enough cpoies to borrow
		this->rental_list->append(new Item(item->get_ID())); // Append a copy to rental list
		this->rental_num = rental_list->items_num();
		this->promote_point += 1;
		cout << "DIO: Item is successfully borrowed." << endl;
	}
	else { // If fail to borrow
		cout << "Yare Yare Daze, cannot borrow this iten." << endl;
	}
}

void Account::return_item(Item * item)
{
	if (this->rental_list->ID_is_in_list(item->get_ID())) { // Check if there is this copy in the account
		this->rental_list->delete_by_ID(item->get_ID());
		this->rental_num = rental_list->items_num();
		item->add_copies(1);
	}
	else {
		cout << "- DIO: This account does not have this item" << endl;
	}
}
