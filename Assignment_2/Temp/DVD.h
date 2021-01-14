#pragma once

#include "Item.h"
#include <string>
#include <iostream>

class DVD :public Item {
private:
	string genre;
public:
	DVD();
	~DVD();
};