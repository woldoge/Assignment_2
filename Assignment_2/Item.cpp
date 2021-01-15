#include "Item.h"
#include <string>
#include <iostream>

Item::Item(string ID) {
	this->ID = ID;
}

bool Item::borrow(int num)
{
	if (this->loan_status == "borrowed") { // If there are enough available copies
		cout << "- DIO: There are not enough copies." << endl;
		return false;
	}
	this->available_copies -= num; // add number of borrowed items
	update_status();
	return true;
}

void Item::update_status()
{
	if (this->available_copies <= 0) {
		this->loan_status = "borrowed";
	}
	else {
		this->loan_status = "available";
	}
}

void Item::add_copies(int num)
{
	this->available_copies += num;
}

void Item::display()
{
	cout << "ID: " << this->ID << " | Title: " << this->title << endl;
	cout << "Loan type: " << this->loan_type << endl;
	cout << "In-stock copies: " << this->available_copies << endl;
	cout << "Rental fee: " << this->fee << endl;
	cout << "Loan status: " << this->loan_status << endl;
}


Record::Record(string ID, string title, string loan_type, int copies, double fee, string genre) {
	this->ID = ID;
	this->title = title;
	this->loan_type = loan_type;
	this->available_copies = copies;
	this->fee = fee;
	this->genre = genre;
	update_status();
}

void Record::display()
{
	Item::display();
	cout << "Genre: " << this->genre << endl;
}

DVD::DVD(string ID, string title, string loan_type, int copies, double fee, string genre) {
	this->ID = ID;
	this->title = title;
	this->loan_type = loan_type;
	this->available_copies = copies;
	this->fee = fee;
	this->genre = genre;
	update_status();
}

void DVD::display()
{
	Item::display();
	cout << "Genre: " << this->genre << endl;
}

Game::Game(string ID, string title, string loan_type, int copies, double fee) {
	this->ID = ID;
	this->title = title;
	this->loan_type = loan_type;
	this->available_copies = copies;
	this->fee = fee;
	update_status();
}