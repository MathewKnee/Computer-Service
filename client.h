#pragma once
#include "User.h"
class client : public User
{
public:
	std::vector<std::string> hello();
	std::vector<int> getPermissions();
	client(int, std::string, std::string);
};

