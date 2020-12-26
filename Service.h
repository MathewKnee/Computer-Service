#pragma once
#include "Order.h"
#include "User.h"
#include "admin.h"
#include "employee.h"
#include "client.h"

#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"

class Service 
{
private:
	std::string db_address;
	std::string root_usr;
	std::string root_pswd;

public:
	std::shared_ptr<User> curr_User;
	Service(std::string, std::string, std::string);
	~Service();
	bool login(std::string, std::string);

	void operator+=(std::shared_ptr<Order>);
	void operator-=(std::shared_ptr<Order>);
	bool assignOrder(int, int);
	std::vector<std::vector<std::string>> takenOrders();
	std::vector<std::vector<std::string>> showOrders();
	bool markAsFinished(int);

	bool addUser(std::string, std::string, int, std::string, std::string);
	bool removeUser(int);
	std::vector<std::vector<std::string>> showUsers();

	double showPerformanceRate();
	std::vector<std::vector<std::string>> getDelayedOrders();

};

