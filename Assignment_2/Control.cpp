#include "Control.h"
#include <iostream>
using namespace std;

Control::Control(string customers_file, string  items_file) {
	this->is_running = true;
	this->customers_file = customers_file;
	this->items_file = items_file;
}
void Control::__init__() {
	c_list = new LinkedAccounts;
	i_list = new LinkedItems;
	ifstream c_file = ifstream(customers_file, ios::in);
	ifstream i_file = ifstream(items_file, ios::in);
	string line;
	int num_line = 1;
	string data;
	// Handling error
	if (!c_file.is_open() || !i_file.is_open()) {
		cout << "Can't open file" << endl;
		return;
	}
	// When file is successfully opened
	// Handling local variables
	Account *current_account = NULL;
	Item* current_item = NULL;
	int pos = 0;
	// Getting items list (i_list) updated
	while (getline(i_file, line)) { // reading line by line
		if (line[0] == 'I') { // if line contains item data
			if (line.find(",Game") != string::npos) { // if line contains VIP account
				current_item = new Game();
			}
			else if (line.find(",Record") != string::npos) { // if line contains Regular account
				current_item = new Record();
			}
			else if (line.find(",DVD") != string::npos) { // if line contains Guest account
				current_item = new DVD();
			}
			i_list->append(current_item);
			for (int i = 0; i < 7; i++) { // Setting 7 pieces of data to the current account
				if (line.find(",Game") != string::npos && i == 6) { // Ignore the 7 piece if line is a game's data
					continue;
				}
				data = line.substr(pos, line.find(',', pos) - pos);
				switch (i)
				{
				case 0: // ID
					current_item->set_ID(data);
					break;
				case 1: // title
					current_item->set_title(data);
					break;
				case 2: // ignore the type of item
					break;
				case 3: // loan_type
					current_item->set_loan_type(data);
					break;
				case 4: // copies
					current_item->set_copies(atoi(data.c_str()));
					break;
				case 5: // fee
					current_item->set_fee(stod(data));
				case 6: // genre (when item is not game)
					current_item->set_genre(data);
				}
				pos += line.find(',', pos) + 1 - pos; // Moving the position to the next data
			}
			pos = 0;
		}
		num_line += 1;
	}
	num_line = 1; // Reset line counter
	// Getting cunstomers list (c_list) updated
	while (getline(c_file, line)) { // reading line by line
		if (line[0] == 'C') { // if line is customer's info data
			if (line.find(",VIP") != string::npos) { // if line contains VIP account
				current_account = new VIPAccount();
			}
			else if (line.find(",Regular") != string::npos) { // if line contains Regular account
				current_account = new RegularAccount();
			}
			else if (line.find(",Guest") != string::npos) { // if line contains Guest account
				current_account = new  GuestAccount();
			}
			c_list->append(current_account);
			for (int i = 0; i < 5; i++) { // Setting 5 pieces of data to the current account
				data = line.substr(pos, line.find(',', pos) - pos);
				switch (i)
				{
				case 0: // ID
					current_account->set_ID(data);
					break;
				case 1: // name
					current_account->set_name(data);
					break;
				case 2: // address
					current_account->set_address(data);
					break;
				case 3: // phone
					current_account->set_phone(data);
					break;
				case 4: // rental_num
					current_account->set_rental_num(atoi(data.c_str()));
					break;
				}
				pos += line.find(',', pos) + 1 - pos; // Moving the position to the next data
			}
			pos = 0;
		}
		else if (line[0] == 'I') { // add item to rental_list of current account if line is customer's rental data
			current_account->__borrow(line);
		}
	}
	
	// Closing files
	c_file.close();
	i_file.close();
	// Display
	cout << "--------Welcome to Genie video store.--------" << endl << endl;
	cout << "- DIO: Oh? You are approaching our store?" << endl << endl;
	cout << "- DIO: I am DIO BRANDO, as your assistant." << endl << endl;
	// Initiate __main__
	Control::__main__();
}

void Control::__main__()
{
	while (this->is_running) {
		menu();
	}
}

bool input_is_number(string input) {
	for (int i = 0; i < input.length(); i++) { // Checking each character
		if ('0' > input[i] || '9' < input[i]) {
			return false;
		}
	}
	return true;
}
void Control::menu() {
	cout << "Enter an option (number) below as your command." << endl;
	cout << "1. Add a new item, update or delete an existing item" << endl;
	cout << "2. Add new customer or update an existing customer" << endl;
	cout << "3. Promote an existing customer" << endl;
	cout << "4. Rent an item" << endl;
	cout << "5. Return an item" << endl;
	cout << "6. Display all items" << endl;
	cout << "7. Display out - of - stock items" << endl;
	cout << "8. Display all customers" << endl;
	cout << "9. Display group of customers" << endl;
	cout << "10. Search items or customers" << endl;
	cout << "Exit. Save the data and exit the program" << endl;
	cout << "Your choice: ";
	string input;
	cin >> input; // Take input from console
	cout << endl;
	if (input == "exit" || input == "Exit") { // When the command is to exit
		exit();
		return;
	}
	// Checking whether input is a number
	if (!input_is_number(input)) {
		cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
		return;
	}
	
	switch (stoi(input)) // Initiate input choice
	{
	case 1:
		cout << "Under maintainance" << endl << endl;
		break;
	case 2:
		cout << "Under maintainance" << endl << endl;
		break;
	case 3:
		cout << "Under maintainance" << endl << endl;
		break;
	case 4:
		borrow_wizard();
		break;
	case 5:
		cout << "Under maintainance" << endl << endl;
		break;
	case 6:
		i_list->display_items();
		break;
	case 7:
		cout << "Under maintainance" << endl << endl;
		break;
	case 8:
		c_list->display_accounts();
		cout << "(*) [VIP]: VIP account" << endl;
		cout << "    [REG]: Regular account" << endl;
		cout << "    [GUE]: Guess account" << endl;
		cout << endl;
		break;
	case 9:
		cout << "Under maintainance" << endl << endl;
		break;
	case 10: 
		cout << "Under maintainance" << endl << endl;
		break;
	default:
		cout << "- DIO: WRYYYYY! Invalid input number!" << endl << endl;
		break;
	}
}

bool input_is_accountID(string input) {
	if (input.length() != 4) { // Check if input has 4 characters
		return false;
	}
	if (input[0] != 'C') { // Check if input's first character is 'I'
		return false;
	}
	if (!input_is_number(input.substr(1, 3))) { // Check if input is number
		return false;
	}
	return true;
}
bool input_is_itemID(string input) {
	if (input.length() != 9) { // Check if input has 4 characters
		return false;
	}
	if (input[0] != 'I') { // Check if input's first character is 'I'
		return false;
	}
	if (input[4] != '-') { // Check if input's 4th character is '-'
		return false;
	}
	if (!input_is_number(input.substr(1, 3))) { // Check if first 4 characters after 'I' is number
		return false;
	}
	if (!input_is_number(input.substr(5, 8))) { // Check if last 4 characters is number
		return false;
	}
	return true;
}

void Control::exit()
{
	this->is_running = false;
	// Dealocate
	this->c_list->deleteList();
	this->i_list->deleteList();
	cout << "*************************************" << endl;
	cout << "- DIO: ZA WARUDO! Your data is saved!" << endl;
}

void Control::borrow_wizard()
{
	bool in_process = true;
	bool enterID_in_process = true;
	Account* account = NULL;
	Item* item = NULL;
	string input;
	cout << "- DIO: Oh! You want to borrow an item?" << endl;
	cout << "- DIO: Choose your account by typing its ID." << endl << endl;
	while (in_process) {
		cout << "1. Show list of all accounts" << endl;
		cout << "0. Go back" << endl;
		cout << "Your Account ID (Cxxx): ";
		cin >> input; // Get input from console
		cout << endl;
		if (input == "exit" || input == "Exit") { // When the command is to exit
			exit();
			return;
		}
		if (input == "1") {
			c_list->display_accounts();
			continue;
		}
		if (input == "0") {
			return;
		}
		if (account == NULL) {
			if (!input_is_accountID(input)) { // Check if input is a number
				cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
				continue;
			}
			if (!c_list->ID_is_in_list(input)) {
				cout << "- DIO: WRYYYYY! An account with an ID like this is not here." << endl << endl;
				continue;
			}
			account = c_list->get_by_ID(input);
			cout << endl;
			cout << "- DIO: Choose your book you want to borrow by typing its ID." << endl << endl;
		}
		while (enterID_in_process) {
			cout << "0. Go back" << endl;
			cout << "1. Show item list" << endl;
			cout << "Your want-to-borrow item ID (Ixxx-xxxx): ";
			cin >> input; // Get input from console
			cout << endl;
			if (input == "exit" || input == "Exit") { // When the command is to exit
				exit();
				return;
			}
			if (input == "0") {
				account = NULL;
				item = NULL;
				cout << endl;
				continue;
			}
			if (input == "1") {
				i_list->display_items();
				cout << endl;
				continue;
			}
			if (!input_is_itemID(input)) { // Check if input is an item ID
				cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
				continue;
			}
			if (!i_list->ID_is_in_list(input)) {
				cout << "- DIO: WRYYYYY! This item is not in out system." << endl << endl;
				continue;
			}
			item = i_list->get_by_ID(input);
			account->__borrow(item);
			cout << endl << endl;
			return;
		}
	}
}

