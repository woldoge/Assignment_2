#pragma once
#include <string>
#include <iostream>
using namespace std;

class Item {
protected:
	string ID;
	string title;
	string loan_type;
	string type = "item";
	int available_copies = 0;
	double fee;
	string loan_status;
public:
	Item() { update_status(); }
	Item(string ID);
	~Item() {}
	// gettors
	string get_ID() { return this->ID; }
	string get_title() { return this->title; }
	string get_loan_type() { return this->loan_type; }
	int get_copies() { return this->available_copies; }
	double get_fee() { return this->fee; }
	string get_type() { return this->type; }
	// setors
	void set_ID(string ID) { this->ID = ID; }
	void set_title(string title) { this->title = title; }
	void set_loan_type(string loan_type) { this->loan_type= loan_type; }
	void set_copies(int copies) { this->available_copies = copies; update_status(); }
	void set_fee(double fee) { this->fee = fee; }
	// handling functions
	bool borrow(int num);
	void update_status();
	void add_copies(int num);
	string get_loan_status() { return this->loan_status; }
	// virtual functions
	virtual void display();
	virtual void set_genre(string genre) {}
	virtual string get_genre() { return ""; }
};

class Record :public Item {
private:
	string genre;
public:
	Record() { this->type = "record"; }
	Record(string ID, string title, string loan_type, int copies, double fee, string genre);
	~Record() {}
	// getors
	string get_genre() { return this->genre; }
	// setors
	void set_genre(string genre) { this->genre = genre;}
	// Handling functions
	void display();
};

class DVD :public Item {
private:
	string genre;
public:
	DVD() { this->type = "DVD"; }
	DVD(string ID, string title, string loan_type, int copies, double fee, string genre);
	~DVD() {}
	// getors
	string get_genre() { return this->genre; }
	// setors
	void set_genre(string genre) { this->genre = genre; }
	void display();
};

class Game :public Item {
public:
	Game() { this->type = "Game"; }
	Game(string ID, string title, string loan_type, int copies, double fee);
	~Game() {}
};