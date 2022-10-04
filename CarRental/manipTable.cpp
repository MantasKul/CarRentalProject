#include "tableManip.h"
#include <iostream>
#include <sqlite3.h>
#include <vector>

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
static int getTableCol(void* NotUsed, int argc, char** argv, char** azColName);

int nameExists;
std::string tableCol;

int manipTable::addData(const std::string dir) {
	sqlite3* DB;

	std::string sql = "";
	std::string tempData;
	std::string tName;
	const char* d;
	char* messageError;

	//choose table name
	std::cout << "Choose into which table you want to add the data: ";
	std::cin >> tName;

	std::string temp = dir + "carRental" + ".db";
	d = temp.c_str();
	int exit = sqlite3_open(d, &DB);

	sql = "SELECT name FROM pragma_table_info(\'" + tName + "\');";

	exit = sqlite3_exec(DB, sql.c_str(), getTableCol, NULL, NULL);
	tableCol.pop_back(); // Removes last "," from the list
	std::cout << tName << " tables columns are: " << std::endl << tableCol << std::endl;
	std::cin.ignore();

	std::cout << "Enter 0 to stop data insertion" << std::endl;

	//Add data, write 0 to stop
	while (1) {
		std::cout << "Write data to add: " << std::endl;

		std::getline(std::cin, tempData);
		if (tempData == "0") break;
		sql = "INSERT INTO " + tName + "(" + tableCol + ")" + "VALUES (" + tempData + ");";

		std::cout << "ADDING: " << sql << std::endl;

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error Insert" << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Values Inserted Successfully" << std::endl;
	} 

	sqlite3_close(DB);
	return 0;
}

int manipTable::registerUser(const std::string dir) {
	sqlite3* DB;
	const char* d;
	char* messageError;
	std::string sql;
	std::string userName;
	std::string userPassword;

	std::string temp = dir + "carRental.db";
	d = temp.c_str();

	int exit = sqlite3_open(d, &DB);

	std::cout << "Enter desired user name: ";
	std::cin >> userName;
	// Check if such username exists, if so exit
	nameExists = 0;
	sql = "SELECT COUNT(*) FROM userList WHERE NAME=\'" + userName + "\';";
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	if (nameExists == 1) {
		std::cout << "Username is taken, please choose another" << std::endl;
		nameExists = 0;
		return 0;
	}

	std::cout << "Enter desired password: ";
	std::cin >> userPassword;

	// ID should be auto incremented, by default no car is rented on acc creation, rent time is 0
	sql = "INSERT INTO userList (NAME, PASSWORD, RENTED_CAR, RENT_TIME) VALUES (\"" + userName + "\",\"" + userPassword + "\", -1, \"0\");";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error registering" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "User created successfully" << std::endl;

	sqlite3_close(DB);

	return 0;
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	if (*argv[0] == '1') nameExists = 1;
	return 0;
}

static int getTableCol(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		tableCol += argv[i];
		tableCol += ",";
	}

	return 0;
}