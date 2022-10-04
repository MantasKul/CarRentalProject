#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>

#include "tableManip.h"

const std::string dbdir = "c:\\CarRentalDB\\";

int main() {
	int choice = 0;
	createDeleteTable crT;
	manipTable mT;
	selectData sD;

	std::string name = "Welcome ";
	int currentlyLogedin = 0;

	do {
		std::cout << "//----------------------------------------------------------------\\\\" << std::endl;
		std::cout << name << " Choose your option: " << std::endl;
		std::cout << "1 - Create new table" << std::endl;
		std::cout << "2 - Add data to an existing table" << std::endl;
		std::cout << "3 - Print the list of cars" << std::endl;
		std::cout << "4 - Register" << std::endl;
		std::cout << "5 - Login" << std::endl;
		std::cout << "6 - Disconnect" << std::endl;
		std::cout << "0 - exit" << std::endl;
		std::cout << "//----------------------------------------------------------------\\\\" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cout << "//----------------------------------------------------------------\\\\" << std::endl;
		switch (choice) {
		case 1:
			crT.createTable(dbdir);
			break;
		case 2:
			mT.addData(dbdir);
			break;
		case 3:
			sD.getCarList(dbdir);
			break;
		case 4:
			if (currentlyLogedin == 1) {
				std::cout << "Cannot use this function when loged in, please disconnect to register a new user" << std::endl;
				break;
			}
			mT.registerUser(dbdir);
			break;
		case 5:
			if (currentlyLogedin == 1) {
				std::cout << "Cannot use this function when loged in, please disconnect to register a new user" << std::endl;
				break;
			}
			sD.logIn(dbdir);
			name += sD.getLogedInName();
			currentlyLogedin = 1;
			break;
		case 6:
			std::cout << "Disconnected successfully" << std::endl;
			currentlyLogedin = 0;
			name = "Welcome ";
			break;
		default:
			std::cout << "Choose a number from the choices presented above." << std::endl;
			break;
		}
	} while (choice != 0);
}
