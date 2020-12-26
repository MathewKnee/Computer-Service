#include "client.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"

client::client(int id_, std::string name_, std::string surname_) {
	id = id_;
	name = name_;
	surname = surname_;
	type = 2;
}

std::vector<std::string> client::hello() {
	std::vector<std::string> ret;
	ret.push_back("Welcome on the main page!");
	ret.push_back(name);
	ret.push_back(surname);
	ret.push_back("Help:");
	ret.push_back("To place orders go to Orders");
	return ret;
}
std::vector<int> client::getPermissions() {
	std::vector<int> ret;
	ret.push_back(1);
	ret.push_back(0);
	ret.push_back(1);
	ret.push_back(0);
	ret.push_back(0);
	ret.push_back(0);
	ret.push_back(0);
	return ret;
}

