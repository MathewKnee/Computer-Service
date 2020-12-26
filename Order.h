#pragma once
#include <string>
class Order
{
private:
	std::string device;
	std::string placed;
	int client_id;
	int state;
	std::string description;
public:
	Order(std::string, std::string,int,int, std::string);
	friend class Service;
};

