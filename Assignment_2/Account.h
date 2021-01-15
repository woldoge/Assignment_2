#pragma once
#include <string>
#include <iostream>
#include "LinkedItems.h"

using namespace std;

class Account {
protected:
	string ID;
	string name;
	string address;
	string phone;
	int rental_num = 0;
	LinkedItems* rental_list = new LinkedItems();
	string customer_type;
	int promote_point = 0;
	int video_rental_num = 0;

public:
	// getors
	string get_ID() { return this->ID; }
	string get_name() { return this->name; }
	string get_address() { return this->address; }
	string get_phone() { return this->phone; }
	int get_rental_num() { return this->rental_num; }
	LinkedItems* get_rental_list() { return this->rental_list; }
	string get_rank() { return this->customer_type; }
	int get_promote_point() { return this->promote_point; }
	// setors
	void set_ID(string ID) { this->ID = ID; }
	void set_name(string name) { this->name = name; }
	void set_address(string address) { this->address = address; }
	void set_phone(string phone) { this->phone = phone; }
	void set_rental_num(int rental_num) { this->rental_num = rental_num; }
	void set_rental_list(LinkedItems* item_list) { this->rental_list = item_list; }
	// Handling functions
	void __borrow(string ID); // Special function for initiate list from file
	// virtual functions
	virtual void __borrow(Item* item);
	virtual void return_item(Item* item);
	virtual void display();
};

class VIPAccount :public Account {
private:
	int point_balance;
public:
	VIPAccount() { this->customer_type = "VIP"; }
	VIPAccount(string ID, string name, string address, string phone);
	~VIPAccount() {}
	// Handling functions
	void __borrow(Item* item);
	void __return(Item* item);
	void display();
};

class RegularAccount :public Account {
public:
	RegularAccount() { this->customer_type = "regular"; }
	RegularAccount(string ID, string name, string address, string phone);
	~RegularAccount() {}
	// Handling functions
	void __borrow(Item* item);
	void __return(Item* item);
	void display();
};

class GuestAccount :public Account {
private:
	const int max_rent = 2;
public:
	GuestAccount() { this->customer_type = "guess"; }
	GuestAccount(string ID, string name, string address, string phone);
	~GuestAccount() {}
	void __borrow(Item* item);
	void __return(Item* item);
	void display();
};