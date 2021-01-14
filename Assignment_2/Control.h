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
	LinkedAccounts* c_list;
	LinkedItems* i_list;
public:
	Control(string customers_file, string  items_file);
	void __init__();
	void __main__();
	void menu();
	void exit();
	void borrow_wizard();
};
