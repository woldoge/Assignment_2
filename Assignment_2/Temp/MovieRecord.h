#pragma once

#include "Item.h"
#include <string>
#include <iostream>

class MovieRecord :public Item {
private:
	string genre;
public:
	MovieRecord();
	~MovieRecord();
};