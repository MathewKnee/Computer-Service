#include "employee.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"

employee::employee(int id_, std::string name_, std::string surname_) {
	id = id_;
	name = name_;
	surname = surname_;
	type = 1;
}

std::vector<std::string> employee::hello() {
	std::vector<std::string> ret;
	ret.push_back("Welcome on the main page!");
	ret.push_back(name);
	ret.push_back(surname);
	ret.push_back("Help:");
	ret.push_back("To manage orders go to Orders");
	return ret;
}
std::vector<int> employee::getPermissions() {
	std::vector<int> ret;
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(0);
	ret.push_back(0);
	ret.push_back(0);
	ret.push_back(0);
	return ret;
}

