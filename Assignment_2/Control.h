#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "Account.h"
#include "LinkedAccounts.h"
#include "LinkedItems.h"
#include "Control.h"
using namespace std;

class Control {
private:
	bool is_running;
	string customers_file;
	string items_file;
	LinkedAccounts* c_list = NULL;
	LinkedItems* i_list = NULL;
	Account *current_account = NULL;
	Item *current_item = NULL;
public:
	Control(string customers_file, string  items_file);
	void __init__();
	void __main__();
	void menu();
	void exit();
	void borrow_wizard();
	string take_user_input();
	void access_account();
	bool input_is_accountID(string input);
	bool input_is_itemID(string input);
	void log_out(Account* account);
	void log_out(Item* item);
	void update_account_wizard();
	void update_item_wizard();
	void access_item();
	void add_account_wizard();
	void add_stock();
	void delete_item();
	void display_group_of_customer();
	void promote_account();
	void return_item();
	void search_account();
	void search_item();
	void add_item_wizard();
	bool is_double(string text);


};
