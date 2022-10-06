#include "tableManip.h"
#include <sqlite3.h>
#include <iostream>

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
static int loginCallback(void* NotUsed, int argc, char** argv, char** azColName);

int logedIn = 0;
std::string name;

int selectData::logIn(const std::string dir) {
	sqlite3* DB;
	std::string userName;
	std::string userPass;
	std::string sql;
	std::string temp = dir + "carRental.db";
	const char* d = temp.c_str();

	int exit = sqlite3_open(d, &DB);
	
	std::cout << "Enter your username: ";
	std::cin >> userName;
	std::cout << "Enter your password: ";
	std::cin >> userPass;

	sql = "SELECT COUNT(*) FROM userList WHERE NAME=\'" + userName + "\' AND PASSWORD=\'" + userPass + "\';";
	exit = sqlite3_exec(DB, sql.c_str(), loginCallback, NULL, NULL);

	if (logedIn == 1) {
		sql = "SELECT NAME FROM userList WHERE NAME=\'" + userName + "\' AND PASSWORD=\'" + userPass + "\';";
		exit = sqlite3_exec(DB, sql.c_str(), loginCallback, NULL, NULL);
		std::cout << "Loged in succesfully" << std::endl;
		setLogedInName(userName);
		return 1;
	}

	std::cout << "Failed to login" << std::endl;
	return 0;
}

void selectData::getCarList(const std::string dir) {
	sqlite3* DB;
	int choice;
	std::string sql;

	std::string temp = dir + "carRental.db";
	const char* d = temp.c_str();
	int exit = sqlite3_open(d, &DB);

	std::cout << "Select 1 to get a full list of cars, select 2 for available car list" << std::endl;
	std::cout << "Your choice: ";
	std::cin >> choice;	

	switch (choice) {
	case 1:
		sql = "SELECT * FROM carList";
		break;
	case 2:
		sql = "SELECT * FROM carList WHERE AVAILABILITY = '1'";
		break;
	default:
		std::cout << "Choose 1 or 2 please" << std::endl;
		break;
	}


	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	std::cout << "| ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << " | ";
	}
	std::cout << std::endl;
	return 0;
}
static int loginCallback(void* NotUsed, int argc, char** argv, char** azColName) {
	name = argv[0];
	if (*argv[0] == '1') logedIn = 1;
	return 0;
}