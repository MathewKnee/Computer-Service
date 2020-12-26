#include "admin.h"

#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"

admin::admin(int id_, std::string name_, std::string surname_) {
	id = id_;
	name = name_;
	surname = name_;
	type = 0;
}

std::vector<std::string> admin::hello() {
	std::vector<std::string> ret;
	ret.push_back("Welcome on the main page!");
	ret.push_back(name);
	ret.push_back(surname);
	ret.push_back("Help:");
	ret.push_back("To manipulate orders go to Orders");
	ret.push_back("To manage users go to Users");
	ret.push_back("To check performance of the company go to Performance Monitor");
	return ret;
}
std::vector<int> admin::getPermissions() {
	std::vector<int> ret;
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(1);
	ret.push_back(1);
	return ret;
}
