#pragma once
#include <string>
#include <vector>
class User
{
protected:
	int type;
	int id;
	std::string name;
	std::string surname;
public:
	virtual std::vector<std::string> hello() = 0;
	virtual std::vector<int> getPermissions() = 0;
	friend class Service;
	friend class cMainFrame;
	friend class cAddOrderFrame;
};

