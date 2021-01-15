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

void Control::access_account() {
	string _input;
	cout << "- DIO: Choose your account by typing its ID." << endl << endl;
	while (true) {
		cout << "1. Show list of all accounts" << endl;
		cout << "0. Go back" << endl;
		cout << "Your Account ID (Cxxx): ";
		_input = take_user_input();
		if (_input == "exit" || _input == "Exit") { // When the command is to exit
			exit();
			return;
		}
		if (_input == "1") {
			this->c_list->display_accounts();
			cout << endl;
			continue;
		}
		if (_input == "0") {
			return;
		}
		
		if (!input_is_accountID(_input)) { // Check if input is a number
			cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
			continue;
		}
		if (!c_list->ID_is_in_list(_input)) {
			cout << "- DIO: WRYYYYY! An account with an ID like this is not here." << endl << endl;
			continue;
		}
		current_account = c_list->get_by_ID(_input);
		cout << endl;
		return;
	}
}
void Control::menu() {
	cout << "Enter an option (number) below as your command." << endl;
	if (current_account == NULL && current_item == NULL) {
		cout << "1. Access an account (for update, rent, return, promote)" << endl;
		cout << "2. Add a new customer" << endl;
		cout << "3. Access an item (for update, delete, add stock)" << endl;
		cout << "4. Display all items" << endl;
		cout << "5. Display out - of - stock items" << endl;
		cout << "6. Display all customers" << endl;
		cout << "7. Display group of customers" << endl;
		cout << "8. Add a new item" << endl;
	}
	if (current_account != NULL) {
		cout << "0. Log out this acount" << endl;
		cout << "1. Update account info" << endl;
		cout << "2. Rent an item" << endl;
		cout << "3. Return an item" << endl;
		cout << "4. Display all items" << endl;
		cout << "5. Display out - of - stock items" << endl;
		cout << "6. Promote this account" << endl;
	}
	if (current_item != NULL) {
		cout << "0. Go back" << endl;
		cout << "1. Update this item atributes" << endl;
		cout << "2. Delete this item" << endl;
		cout << "3. Add stock" << endl;
		cout << "4. Display all items" << endl;
		cout << "5. Display out - of - stock items" << endl;
	}
	
	string input;
	input = take_user_input();
	if (input == "exit" || input == "Exit") { // When the command is to exit
		exit();
		return;
	}
	// Checking whether input is a number
	if (!input_is_number(input)) {
		cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
		return;
	}
	if (!this->is_running) { // Exit the program when is_running is false
		return;
	}
	
	switch (stoi(input)) // Initiate input choice
	{
	case 0:
		if (current_account != NULL) {
			log_out(current_account);
			break;
		}
		if (current_item != NULL) {
			log_out(current_item);
			break;
		}

		cout << "- DIO: WRYYYYY! Invalid input number!" << endl << endl;
		break;
	case 1:
		if (current_account == NULL && current_item == NULL) {
			access_account();
			break;
		}
		if (current_account != NULL) {
			update_account_wizard();
			break;
		}
		if (current_item != NULL) {
			update_item_wizard();
			break;
		}
	case 2:
		if (current_account == NULL && current_item == NULL) {
			add_account_wizard();
			break;
		}
		if (current_account != NULL) {
			borrow_wizard();
			break;
		}
		if (current_item != NULL) {
			delete_item();
			break;
		}
	case 3:
		if (current_account == NULL && current_item == NULL) {
			access_item();
			break;
		}
		if (current_account != NULL) {
			return_item();
			break;
		}
		if (current_item != NULL) {
			add_stock();
			break;
		}

	case 4:
		i_list->display_items();
		cout << endl;
		break;
	case 5:
		i_list->display_OOS();
		cout << endl;
		break;
	case 6:
		if (current_account == NULL && current_item == NULL) {
			this->c_list->display_accounts();
			break;
		}
		if (current_account != NULL) {
			this->promote_account();
			break;
		}
	case 7:
		if (current_account == NULL && current_item == NULL) {
			this->display_group_of_customer();
			break;
		}
	case 8:
		if (current_account == NULL && current_item == NULL) {
			cout << "Maintainace" << endl;
			break;
		}
	default:
		cout << "- DIO: WRYYYYY! Invalid input number!" << endl << endl;
		break;
	}

}

bool Control::input_is_accountID(string input) {
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
void Control::log_out(Account* account)
{
	this->current_account = NULL;
}
void Control::log_out(Item* item)
{
	this->current_item = NULL;
}
void Control::update_account_wizard()
{
	string _input;
	cout << "Oh! You want to update your account infomation?" << endl;
	cout << "What attribute you want to update?" << endl;
	cout << "0. Go back" << endl;
	cout << "1. Name" << endl;
	cout << "2. Phone" << endl;
	cout << "3. Address" << endl;
	cout << "What you enter should be '[option]-[what you want this to become]'" << endl;
	cout << "For xample: 1-Jotaro Kujo" << endl << endl;
	while (true) {
		_input = take_user_input();
		cout << endl;
		if (_input == "exit" || _input == "Exit") { // When the command is to exit
			exit();
			return;
		}
		if (_input == "0" || _input == "Exit") { // When the command is to exit
			return;
		}
		if (_input.find(',') != string::npos) { // When ',' is in the input
			cout << "DIO: Yare yare daze! Your input must not have ',' " << endl;
			continue;
		}
		if (_input.length() > 2 && _input[0] == '1' &&_input[1] == '-') { // 1. set name
			this->current_account->set_name(_input.substr(2));
			cout << "DIO: Your account name has been set!" << endl << endl;
			return;
		}
		if (_input.length() > 2 && _input[0] == '2' &&_input[1] == '-') { // 1. set phone
			this->current_account->set_phone(_input.substr(2));
			cout << "DIO: Your account phone has been set!" << endl << endl;
			return;
		}
		if (_input.length() > 2 && _input[0] == '3' &&_input[1] == '-') { // 1. set address
			this->current_account->set_address(_input.substr(2));
			cout << "DIO: Your account address has been set!" << endl << endl;
			return;
		}
	}
	cout << "- DIO: WRYYYYY! What you typed is not valid" << endl << endl;
}
void Control::update_item_wizard()
{
	string _input;
	cout << "Oh! You want to update your account infomation?" << endl;
	cout << "What attribute you want to update?" << endl;
	cout << "0. Go back" << endl;
	cout << "1. Title" << endl;
	cout << "2. Loan type ('2-day' or '1-week')" << endl;
	cout << "3. Rental fee" << endl;
	cout << "What you enter should be '[option]-[what you want this to become]'" << endl;
	cout << "For xample: 1-JoJo's Bizarre Adventure: Golden Wind" << endl << endl;
	while (true) {
		_input = take_user_input();
		cout << endl;
		if (_input == "exit" || _input == "Exit") { // When the command is to exit
			exit();
			return;
		}
		if (_input == "0" || _input == "Exit") { // When the command is to exit
			return;
		}
		if (_input.find(',') != string::npos) { // When ',' is in the input
			cout << "DIO: Yare yare daze! Your input must not have ',' " << endl;
			continue;
		}
		if (_input.length() > 2 && _input[0] == '1' &&_input[1] == '-') { // 1. set title
			this->current_item->set_title(_input.substr(2));
			cout << "DIO: Your item title has been set!" << endl << endl;
			return;
		}
		if (_input.length() > 2 && _input[0] == '2' &&_input[1] == '-') { // 1. set loan type
			if (_input.substr(2) == "2-day" || _input.substr(2) == "1-week") { // check if user input is 2-day or 1-week 
				this->current_item->set_loan_type(_input.substr(2));
				cout << "DIO: Your item loan type been set!" << endl << endl;
				return;
				cout << "DIO: Loan type should be only 2-day or 1-week" << endl<< endl;
			}
		}
		if (_input.length() > 2 && _input[0] == '3' &&_input[1] == '-') { // 1. set rental fee
			if (input_is_number(_input)) {
				this->current_item->set_fee(stod(_input.substr(2)));
				cout << "DIO: Your account rental fee has been set!" << endl << endl;
				return;
			}
			cout << "Input is not a number." << endl << endl;
		}
	}
	cout << "- DIO: WRYYYYY! What you typed is not valid" << endl << endl;
}
void Control::access_item()
{
	string _input;
	cout << "- DIO: Choose your item by typing its ID." << endl << endl;
	while (true) {
		cout << "1. Show list of all items" << endl;
		cout << "0. Go back" << endl;
		cout << "Your Item ID (Ixxx-xxxx): ";
		_input = take_user_input();
		if (_input == "exit" || _input == "Exit") { // When the command is to exit
			exit();
			return;
		}
		if (_input == "1") {
			this->i_list->display_items();
			cout << endl;
			continue;
		}
		if (_input == "0") {
			return;
		}

		if (!input_is_itemID(_input)) { // Check if input is a number
			cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
			continue;
		}
		if (!i_list->ID_is_in_list(_input)) {
			cout << "- DIO: WRYYYYY! An item with an ID like this is not here." << endl << endl;
			continue;
		}
		current_item = i_list->get_by_ID(_input);
		cout << endl;
		return;
	}
}
void Control::add_account_wizard()
{
	string _input;
	string name;
	string phone;
	string address;
	string type;
	string ID;
	int stage = 1;
	cout << "DIO: Oh? So you want to add new account?" << endl << endl;
	while (true) {
		cout << "0. Go back" << endl;
		if (stage == 1) {
			cout << "Enter name" << endl;
			_input = take_user_input();
			if (_input == "exit" || _input == "Exit") {
				exit();
			}
			if (_input == "0") {
				return;
			}
			if (_input.find(',') != string::npos) {
				cout << "DIO: No ',' allowed";
				continue;
			}
			name = _input;
			stage += 1;
		}
		if (stage == 2) {
			cout << "Enter phone" << endl;
			_input = take_user_input();
			if (_input == "exit" || _input == "Exit") {
				exit();
			}
			if (_input == "0") {
				stage-=1;
			}
			if (_input.find(',') != string::npos) {
				cout << "DIO: No ',' allowed";
				continue;
			}
			phone = _input;
			stage += 1;
		}
		if (stage == 3) {
			cout << "Enter address" << endl;
			_input = take_user_input();
			if (_input == "exit" || _input == "Exit") {
				exit();
			}
			if (_input == "0") {
				stage -= 1;
			}
			if (_input.find(',') != string::npos) {
				cout << "DIO: No ',' allowed";
				continue;
			}
			address = _input;
			stage += 1;
		}
		if (stage == 4) {
			cout << "Enter account rank" << endl;
			_input = take_user_input();
			if (_input == "exit" || _input == "Exit") {
				exit();
			}
			if (_input == "0") {
				stage -= 1;
			}
			if (_input.find(',') != string::npos) {
				cout << "DIO: No ',' allowed";
				continue;
			}
			if (_input == "VIP"|| _input == "REG" || _input == "GUE") {
				type = _input;
				stage += 1;
				continue;
			}
			cout << "Wrong account rank code" << endl << endl;;
		}
		if (stage == 5) {
			cout << "Enter account ID" << endl;
			_input = take_user_input();
			if (_input == "exit" || _input == "Exit") {
				exit();
			}
			if (_input == "0") {
				stage -= 1;
			}
			if (input_is_accountID(_input)) {
				if (_input.find(',') != string::npos) {
					cout << "DIO: No ',' allowed";
					continue;
				}
				if (c_list->ID_is_in_list(_input)) {
					cout << "DIO: ID is already exist" << endl;
					continue;
				}
				ID = _input;
				stage += 1;
				continue;
			}
			cout << "Invalid ID" << endl << endl;
		}
		if (stage == 6) {
			if (type == "VIP") {
				this->c_list->append(new VIPAccount(ID,name, address, phone));
			}
			if (type == "REG") {
				this->c_list->append(new VIPAccount(ID,name, address, phone));
			}
			if (type == "GUE") {
				this->c_list->append(new VIPAccount(ID,name, address, phone));
			}
			cout << "DIO: New account created!" << endl << endl;
			return;
		}

	}
}
void Control::add_stock()
{
	string _input;
	cout << " - DIO: Oh? You want to add more copies?" << endl;
	cout << " Enter you number of new copies." << endl << endl;
	while (true) { // get user input as a num
		_input = take_user_input();
		cout << endl;
		if (_input == "exit" || _input == "Exit") {
			exit();
			return;
		}
		if (_input == "0") {
			return;
		}
		if (input_is_number(_input)) {
			this->current_item->add_copies(stoi(_input));
			cout << "DIO: WRYYYY! Stock added" << endl << endl;
			return;
		}
		cout << "What you enterer is not a whole number" << endl << endl;
	}
}
void Control::delete_item()
{
	i_list->removeNode(this->current_item);
	this->current_item = NULL;
	cout << "ROAD ROLLER DA! Your item is deleted" << endl << endl;
}
void Control::display_group_of_customer()
{
	string _input;
	while (true) {
		cout << "- DIO: What type of accounts you want to show? VIP, regular or guess?" << endl;
		cout << "0. Go back" << endl;
		cout << "1. Guess accounts" << endl;
		cout << "2. VIP accounts" << endl;
		cout << "3. Regular accounts" << endl;
		_input = take_user_input();
		cout << endl;
		if (_input == "exit" || _input == "Exit") {
			exit();
			return;
		}
		if (_input == "0") {
			return;
		}
		if (_input == "1") {
			this->c_list->display_accounts("guess");
			continue;
		}
		if (_input == "2") {
			this->c_list->display_accounts("VIP");
			continue;
		}
		if (_input == "3") {
			this->c_list->display_accounts("regular");
			continue;
		}
		cout << "- DIO: Invalid input!" << endl << endl;
	}
}
void Control::promote_account()
{
	if (this->current_account->get_rank() == "VIP") {
		cout << "- DIO: You are currently at the highest rank!" << endl << endl;
		return;
	}
	Account* new_account;;
	if (this->current_account->get_rank() == "regular"|| current_account->get_rank() == "guess") {
		if (current_account->get_rank() == "regular") {
			new_account = new VIPAccount();
		}

		else{
			new_account = new RegularAccount();
		}
		c_list->change_account(current_account, new_account);
	}
}
void Control::return_item()
{
	cout << "Oh? So you want yo return an item?" << endl;
	cout << "0. Go back" << endl;
	cout << "1. Show your current list of borrowed item;" << endl;
	cout << "Enter your item ID you want to return (Ixxx-xxxx)" << endl;
	cout << "For example: I009-2077" << endl;
	string _input;
	while (true)
	{
		_input = take_user_input();
		cout << endl;
		if (_input == "exit" || _input == "Exit") {
			exit();
			return;
		}
		if (_input == "0") {
			return;
		}
		if (_input == "1") {
			this->current_account->display();
			continue;
		}
		if (input_is_itemID(_input)){
			if (this->current_account->get_rental_list()->ID_is_in_list(_input)) {
				Item* item = i_list->get_by_ID(_input);
				this->current_account->return_item(item);
				cout << "Successfully returned" << endl << endl;
				return;
			}
			else {
				cout << "Yare yare daze, you have not borrowed this item, yet" << endl << endl;
			}
			continue;
		}
		cout << "Invalid input!" << endl << endl;
		
	}
}
bool Control::input_is_itemID(string input) {
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
	string _input;
	cout << "- DIO: Oh! You want to borrow an item?" << endl;
	cout << "- DIO: Choose your item you want to borrow by typing its ID." << endl << endl;
	while (true) {
		cout << "0. Go back" << endl;
		cout << "1. Show item list" << endl;
		cout << "Your want-to-borrow item ID (Ixxx-xxxx): ";
		cin >> _input; // Get input from console
		cout << endl;
		if (_input == "exit" || _input == "Exit") { // When the command is to exit
			exit();
			return;
		}
		if (_input == "0") { // Return to previous step
			cout << endl;
			return;
		}
		if (_input == "1") { // Display list of item
			i_list->display_items();
			cout << endl;
			continue;
		}
		if (!input_is_itemID(_input)) { // Check if input is an item ID
			cout << "- DIO: WRYYYYY! Invalid input." << endl << endl;
			continue;
		}
		if (!i_list->ID_is_in_list(_input)) {
			cout << "- DIO: WRYYYYY! This item is not in out system." << endl << endl;
			continue;
		}
		this->current_item = i_list->get_by_ID(_input);
		this->current_account->__borrow(this->current_item);
		this->current_item = NULL;
		cout << endl << endl;
		return;
	}
}

string Control::take_user_input()
{
	string _input;
	if (current_account != NULL) {
		cout << '[' << current_account->get_ID() << ']';
	}
	if (current_item != NULL) {
		cout << '[' << current_item->get_ID() << ']';
	}
	cout << "Your option: ";
	cin >> _input; // Take input from console
	cout << endl;
	cout << "-----------------------------------------" << endl;
	return _input;
}

