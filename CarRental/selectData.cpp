#include "tableManip.h"
#include <sqlite3.h>
#include <iostream>
#include <string>

#include <conio.h> // Used for password masking windows only header

#include "bcrypt.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
static int loginCallback(void* NotUsed, int argc, char** argv, char** azColName);
static int getPass(void* NotUsed, int argc, char** argv, char** azColName);

int logedIn = 0;
std::string name;
int isAdmin = 0;
std::string hPass;

int selectData::logIn(const std::string dir) {
	sqlite3* DB;
	std::string userName;
	std::string userPass;
	std::string hashedPass;
	std::string sql;
	std::string temp = dir + "carRental.db";
	const char* d = temp.c_str();

	logedIn = getIsLogedin();

	int exit = sqlite3_open(d, &DB);
	
	std::cout << "Enter your username: ";
	std::cin >> userName;

	std::cin.ignore();
	std::cout << "Enter your password: ";

	// masking password
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			if (userPass.size() > 0) {
				userPass.erase(userPass.size() - 1, 1);
				std::cout << "\b \b";
			}
		}
		else {
			userPass.push_back(ch);
			std::cout << "*";
		}
	}
	userPass.pop_back(); // Removes Enter character
	std::cout << std::endl;


	hashedPass = bcrypt::generateHash(userPass);

	sql = "SELECT COUNT(*) FROM userList WHERE NAME=\'" + userName + "\';";
	exit = sqlite3_exec(DB, sql.c_str(), loginCallback, NULL, NULL);

	sql = "SELECT PASSWORD FROM userList WHERE NAME=\"" + userName + "\";";
	exit = sqlite3_exec(DB, sql.c_str(), getPass, NULL, NULL);
	if (bcrypt::validatePassword(userPass, ::hPass)) logedIn = 1;
	else logedIn = 0;

	if (logedIn == 1) {
		sql = "SELECT NAME, ADMIN FROM userList WHERE NAME=\'" + userName + "\' AND PASSWORD=\'" + hashedPass + "\';";
		exit = sqlite3_exec(DB, sql.c_str(), loginCallback, NULL, NULL);
		setLogedInName(userName);
		setIsAdmin(::isAdmin);
		return 1;
	}

	std::cout << "Failed to login, username or password incorrect" << std::endl;
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
	if (logedIn) {
		if (*argv[1] == '1') {
			isAdmin = 1;
		}
		else isAdmin = 0;
	}
	if (*argv[0] == '1') logedIn = 1;
	else logedIn = 0;
	return 0;
}
static int getPass(void* NotUsed, int argc, char** argv, char** azColName) {
	hPass = argv[0];
	return 0;
}