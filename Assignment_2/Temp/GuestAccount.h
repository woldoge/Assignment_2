#pragma once

#include "Account.h"
#include <string>
#include <iostream>

class GuestAccount :public Account {
public:
	GuestAccount();
	~GuestAccount();
};