#include "Service.h"

Service::Service(std::string db,std::string usr,std::string passwd) {
	db_address = db;
	root_usr = usr;
	root_pswd = passwd;
	curr_User = nullptr;
}
Service::~Service() {

}
bool Service::login(std::string usr, std::string passwd) {
	try {
		sql::mysql::MySQL_Driver* driver;
		driver = sql::mysql::get_mysql_driver_instance();
		std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
		con->setSchema("serwis");
		std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT type,id,name,surname FROM users WHERE username = ? AND passwd = ?"));

		p_stmt->setString(1, usr);
		p_stmt->setString(2, passwd);

		std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());
		if (res->rowsCount() == 1) {
			res->next();
			int type = res->getInt("type");
			int id = res->getInt("id");
			std::string name = res->getString("name");
			std::string surname = res->getString("surname");
			if (type == 0) {
				curr_User = std::shared_ptr<admin>(new admin(id, name, surname));
			}
			else if (type == 1) {
				curr_User = std::shared_ptr<employee>(new employee(id, name, surname));
			}
			else if (type == 2) {
				curr_User = std::shared_ptr<client>(new client(id, name, surname));
			}
		}
		else {
			return false;
		}
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

void Service::operator+=(std::shared_ptr<Order> ord) {
	if (curr_User && (curr_User->getPermissions())[0]) {
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::auto_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::auto_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("INSERT INTO order_queue (device,client_id,state,description) VALUES (?,?,?,?)"));

			p_stmt->setString(1, ord->device);
			p_stmt->setInt(2, ord->client_id);
			p_stmt->setInt(3, ord->state);
			p_stmt->setString(4, ord->description);


			p_stmt->executeQuery();
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	

}
void Service::operator-=(std::shared_ptr<Order> ord) {
	if (curr_User && (curr_User->getPermissions())[6]) {
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::auto_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::auto_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("DELETE FROM order_queue WHERE device = ? AND client_id = ? AND state = ? AND description = ? AND placed = ? LIMIT 1"));

			p_stmt->setString(1, ord->device);
			p_stmt->setInt(2, ord->client_id);
			p_stmt->setInt(3, ord->state);
			p_stmt->setString(4, ord->description);
			p_stmt->setString(5, ord->placed);

			p_stmt->executeQuery();
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
bool Service::markAsFinished(int id) {
	try {
		sql::mysql::MySQL_Driver* driver;
		driver = sql::mysql::get_mysql_driver_instance();
		std::auto_ptr<sql::Connection>con(driver->connect("tcp://127.0.0.1:3306", "root", ""));
		con->setSchema("serwis");
		std::auto_ptr<sql::PreparedStatement> p_stmt1(con->prepareStatement("UPDATE order_queue SET state = 2 WHERE ID = ?"));
		p_stmt1->setInt(1, id);
		p_stmt1->executeQuery();
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}
std::vector<std::vector<std::string>> Service::showOrders() {
	std::vector<std::vector<std::string>> ret;
	
	
	std::vector<int> perm = curr_User->getPermissions();
	if (curr_User && perm[2]){
		if (curr_User->type == 0) {
			std::vector<std::string> header_row;
			header_row.push_back("ID");
			header_row.push_back("Device");
			header_row.push_back("Client ID");
			header_row.push_back("Placed");
			header_row.push_back("State");
			header_row.push_back("Description");
			ret.push_back(header_row);
			try {
				sql::mysql::MySQL_Driver* driver;
				driver = sql::mysql::get_mysql_driver_instance();
				std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
				con->setSchema("serwis");
				std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT * FROM order_queue"));
				std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());

				while (res->next()) {
					std::vector<std::string> row;

					row.push_back(std::to_string(res->getInt("ID")));
					row.push_back(res->getString("device"));
					row.push_back(std::to_string(res->getInt("client_id")));
					row.push_back(res->getString("placed"));
					int state = res->getInt("state");
					std::string state_str;
					if (state == 0) {
						state_str = "waiting";
					}
					else if (state == 1) {
						state_str = "taken";
					}
					else if (state == 2) {
						state_str = "finished";
					}
					row.push_back(state_str);
					row.push_back(res->getString("description"));
					ret.push_back(row);
				}
			}
			catch (sql::SQLException& e) {
				std::cerr << e.what() << std::endl;
				std::vector<std::string> row;
				for (int i = 0; i < 6; i++) row.push_back("ERROR");
				ret.push_back(row);
			}
		}
		else if (curr_User->type == 1) {
			std::vector<std::string> header_row;
			header_row.push_back("ID");
			header_row.push_back("Device");
			header_row.push_back("Placed");
			header_row.push_back("State");
			header_row.push_back("Description");
			ret.push_back(header_row);
			try {
				sql::mysql::MySQL_Driver* driver;
				driver = sql::mysql::get_mysql_driver_instance();
				std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
				con->setSchema("serwis");
				std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT * FROM order_queue WHERE state = 0"));
				std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());

				while (res->next()) {
					std::vector<std::string> row;

					row.push_back(std::to_string(res->getInt("ID")));
					row.push_back(res->getString("device"));
					row.push_back(res->getString("placed"));
					int state = res->getInt("state");
					std::string state_str;
					if (state == 0) {
						state_str = "waiting";
					}
					else if (state == 1) {
						state_str = "taken";
					}
					else if (state == 2) {
						state_str = "finished";
					}
					row.push_back(state_str);
					row.push_back(res->getString("description"));
					ret.push_back(row);
				}
			}
			catch (sql::SQLException& e) {
				std::cerr << e.what() << std::endl;
				std::vector<std::string> row;
				for (int i = 0; i < 5; i++) row.push_back("ERROR");
				ret.push_back(row);
			}
		}
		else if (curr_User->type == 2) {
			std::vector<std::string> header_row;
			header_row.push_back("Device");
			header_row.push_back("Placed");
			header_row.push_back("State");
			header_row.push_back("Description");
			ret.push_back(header_row);
			try {
				sql::mysql::MySQL_Driver* driver;
				driver = sql::mysql::get_mysql_driver_instance();
				std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
				con->setSchema("serwis");
				std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT * FROM order_queue WHERE client_id = ?"));
				p_stmt->setInt(1, curr_User->id);
				std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());

				while (res->next()) {
					std::vector<std::string> row;

					
					row.push_back(res->getString("device"));
					row.push_back(res->getString("placed"));
					int state = res->getInt("state");
					std::string state_str;
					if (state == 0) {
						state_str = "waiting";
					}
					else if (state == 1) {
						state_str = "taken";
					}
					else if (state == 2) {
						state_str = "finished";
					}
					row.push_back(state_str);
					row.push_back(res->getString("description"));
					ret.push_back(row);
				}
			}
			catch (sql::SQLException& e) {
				std::cerr << e.what() << std::endl;
				std::vector<std::string> row;
				for (int i = 0; i < 4; i++) row.push_back("ERROR");
				ret.push_back(row);
			}
		}
		
	}
	else {
		std::vector<std::string> row;
		for (int i = 0; i < 6; i++) row.push_back("ERROR");
		ret.push_back(row);
	}
	return ret;
}
bool Service::addUser(std::string username, std::string passwd, int type, std::string name, std::string surname) {
	if (curr_User && (curr_User->getPermissions())[3]) {
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("INSERT INTO users (username,passwd,type,name,surname) VALUES (?,?,?,?,?)"));

			p_stmt->setString(1, username);
			p_stmt->setString(2, passwd);
			p_stmt->setInt(3, type);
			p_stmt->setString(4, name);
			p_stmt->setString(5, surname);

			p_stmt->executeQuery();
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}
	else return false;
}

bool Service::removeUser(int id) {
	if (curr_User && (curr_User->getPermissions())[4]) {
		if (curr_User->id != id) {
			try {
				sql::mysql::MySQL_Driver* driver;
				driver = sql::mysql::get_mysql_driver_instance();
				std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
				con->setSchema("serwis");
				std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("DELETE FROM users WHERE ID = ?"));

				p_stmt->setInt(1, id);

				p_stmt->executeQuery();
			}
			catch (sql::SQLException& e) {
				std::cerr << e.what() << std::endl;
				return false;
			}
		}
		else {
			return false;
		}
		return true;
	}
	else return false;
}
std::vector<std::vector<std::string>> Service::showUsers() {
	std::vector<std::vector<std::string>> ret;
	std::vector<std::string> header_row;
	header_row.push_back("ID");
	header_row.push_back("Username");
	header_row.push_back("Password");
	header_row.push_back("Type");
	header_row.push_back("Name");
	header_row.push_back("Surname");
	ret.push_back(header_row);
	if (curr_User && (curr_User->getPermissions())[5]) {
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT * FROM users"));
			std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());
			while (res->next()) {
				std::vector<std::string> row;

				row.push_back(std::to_string(res->getInt("ID")));
				row.push_back(res->getString("username"));
				row.push_back("*******");
				int user_type = res->getInt("type");
				std::string user_type_str;
				if (user_type == 0) {
					user_type_str = "admin";
				}
				else if (user_type == 1) {
					user_type_str = "employee";
				}
				else if (user_type == 2) {
					user_type_str = "client";
				}
				row.push_back(user_type_str);
				row.push_back(res->getString("name"));
				row.push_back(res->getString("surname"));

				ret.push_back(row);
			}
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			std::vector<std::string> row;
			for (int i = 0; i < 6; i++) row.push_back("ERROR");
			ret.push_back(row);
		}
		return ret;
	}
	else {
		std::vector<std::string> row;
		for (int i = 0; i < 6; i++) row.push_back("ERROR");
		ret.push_back(row);
	}
}

bool Service::assignOrder(int emp_id, int order_id) {
	if (curr_User && (curr_User->getPermissions())[1]) {
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("INSERT INTO assigned_orders (employee_ID,order_ID) VALUES (?,?)"));
			p_stmt->setInt(1, emp_id);
			p_stmt->setInt(2, order_id);
			p_stmt->executeQuery();
			std::shared_ptr<sql::PreparedStatement> p_stmt1(con->prepareStatement("UPDATE order_queue SET state = 1 WHERE ID = ?"));
			p_stmt1->setInt(1, order_id);
			p_stmt1->executeQuery();
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}
	else return false;
}
std::vector<std::vector<std::string>> Service::takenOrders() {
	std::vector<std::vector<std::string>> ret;
	std::vector<std::string> header_row;
	header_row.push_back("ID");
	header_row.push_back("Device");
	header_row.push_back("Placed");
	header_row.push_back("Description");
	ret.push_back(header_row);
	if (curr_User && curr_User->type == 1) {
		
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT ID, device, placed, description FROM order_queue INNER JOIN assigned_orders ON order_queue.ID = assigned_orders.order_ID WHERE assigned_orders.employee_ID = ? AND order_queue.state = 1"));
			p_stmt->setInt(1, curr_User->id);
			std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());
			while (res->next()) {
				std::vector<std::string> row;

				row.push_back(std::to_string(res->getInt("ID")));
				row.push_back(res->getString("device"));
				row.push_back(res->getString("placed"));
				row.push_back(res->getString("description"));
				ret.push_back(row);
			}
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			std::vector<std::string> row;
			for (int i = 0; i < 4; i++) row.push_back("ERROR");
			ret.push_back(row);
		}
		
	}
	else {
		std::vector<std::string> row;
		for (int i = 0; i < 6; i++) row.push_back("ERROR");
		ret.push_back(row);
	}
	return ret;
}

double Service::showPerformanceRate() {
	double ret;
	int number_of_employees;
	int number_of_orders;
	if (curr_User && (curr_User->type == 0 || curr_User->type == 2) ){
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt1(con->prepareStatement("SELECT count(*) FROM users WHERE type = 1"));
			std::shared_ptr<sql::ResultSet> res1(p_stmt1->executeQuery());
			res1->next();
			number_of_employees = res1->getInt(1);
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			ret = 0.0;
		}
	}
	else {
		ret = 0.0;
	}
	if (curr_User && (curr_User->type == 0 || curr_User->type == 2)) {
		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt1(con->prepareStatement("SELECT count(*) FROM order_queue WHERE NOT state = 2"));
			std::shared_ptr<sql::ResultSet> res1(p_stmt1->executeQuery());
			res1->next();
			number_of_orders = res1->getInt(1);
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			ret = 0.0;
		}
	}
	else {
		ret = 0.0;
	}
	ret = ((double)number_of_orders) / ((double)number_of_employees);
	return ret;
}
std::vector<std::vector<std::string>> Service::getDelayedOrders() {
	std::vector<std::vector<std::string>> ret;
	std::vector<std::string> header_row;
	header_row.push_back("ID");
	header_row.push_back("Device");
	header_row.push_back("Client ID");
	header_row.push_back("Placed");
	header_row.push_back("State");
	header_row.push_back("Description");
	ret.push_back(header_row);
	if (curr_User && curr_User->getPermissions()[6]) {

		try {
			sql::mysql::MySQL_Driver* driver;
			driver = sql::mysql::get_mysql_driver_instance();
			std::shared_ptr<sql::Connection>con(driver->connect(db_address, root_usr, root_pswd));
			con->setSchema("serwis");
			std::shared_ptr<sql::PreparedStatement> p_stmt(con->prepareStatement("SELECT * FROM order_queue WHERE DATEDIFF(CURRENT_TIMESTAMP,placed) >= 5"));
			std::shared_ptr<sql::ResultSet> res(p_stmt->executeQuery());
			while (res->next()) {
				std::vector<std::string> row;

				row.push_back(std::to_string(res->getInt("ID")));
				row.push_back(res->getString("device"));
				row.push_back(std::to_string(res->getInt("client_id")));
				row.push_back(res->getString("placed"));
				int state = res->getInt("state");
				std::string state_str;
				if (state == 0) {
					state_str = "waiting";
				}
				else if (state == 1) {
					state_str = "taken";
				}
				else if (state == 2) {
					state_str = "finished";
				}
				row.push_back(state_str);
				row.push_back(res->getString("description"));
				ret.push_back(row);
			}
		}
		catch (sql::SQLException& e) {
			std::cerr << e.what() << std::endl;
			std::vector<std::string> row;
			for (int i = 0; i < 6; i++) row.push_back("ERROR");
			ret.push_back(row);
		}

	}
	else {
		std::vector<std::string> row;
		for (int i = 0; i < 6; i++) row.push_back("ERROR");
		ret.push_back(row);
	}
	return ret;
}