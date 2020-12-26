#pragma once
#include "User.h"
class employee : public User
{
public:
	std::vector<std::string> hello(); 
	std::vector<int> getPermissions();
	employee(int,std::string, std::string);
};

