#pragma once
#include "User.h"

class admin : public User
{
public:
	std::vector<std::string> hello();
	std::vector<int> getPermissions();
	admin(int,std::string,std::string);
};

