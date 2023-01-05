#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>

#include "tableManip.h"

const std::string dbdir = "c:\\CarRentalDB\\";

int isNumber(std::string str) {
	for(int i = 0; i < str.length(); i++)
		if(!isdigit(str[i])) return -1;
	return stoi(str);
}

int main() {
	int choice;
	std::string input;
	createDeleteTable crT;
	manipTable mT;
	selectData sD;
	sD.setIsLogedin(0);

	std::string welcome = "Welcome ";
	std::string name = "";
	int currentlyLogedin = 0;
	int isAdmin = 0;

	do {
		std::cout << "//----------------------------------------------------------------\\\\" << std::endl;
		std::cout << welcome << name << " Choose your option: " << std::endl;
		std::cout << "1 - Print the list of cars" << std::endl;
		if (currentlyLogedin == 0) {
			std::cout << "2 - Register" << std::endl;									// Should be Available only if not loged in
			std::cout << "3 - Login" << std::endl;										// Should be Available only if not loged in
		}
		if (currentlyLogedin == 1) {
			std::cout << "2 - Disconnect" << std::endl;									// Should be Available only if loged in
			std::cout << "3 - Rent a car" << std::endl;									// Should be Available only if loged in
			std::cout << "4 - Finish rent" << std::endl;								// If loged in
		}
		if (isAdmin) {
			std::cout << "7 - Create new table" << std::endl;							// Should only be available for admin account
			std::cout << "8 - Add data to an existing table" << std::endl;				// Should only be available for admin account
			std::cout << "9 - Change car's notes" << std::endl;							// Should only be for admin account
		}
		std::cout << "0 - exit" << std::endl;

		std::cout << "//----------------------------------------------------------------\\\\" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> input;
		choice = isNumber(input);
		if (choice < 0) choice = -1;

		std::cout << "//----------------------------------------------------------------\\\\" << std::endl;
		switch (choice) {
			// Getting car list, available always
		case 1:
			sD.getCarList(dbdir);
			break;
			// if not loged in - registering, if loged in - setting values to 0, disconnecting user
		case 2:
			if (currentlyLogedin == 0) {
				mT.registerUser(dbdir);
			}
			else {
				currentlyLogedin = 0;
				sD.setIsLogedin(0);
				isAdmin = 0;
				sD.setIsAdmin(0);
				name = "";
			}
			break;
			// if not loged in - log in, if loged in - rent a car
		case 3:
			if (currentlyLogedin == 0) {
				if (sD.logIn(dbdir) == 1) {
					name = sD.getLogedInName();
					currentlyLogedin = 1;
					isAdmin = sD.getIsAdmin();
				}
				else {
					currentlyLogedin = 0;
					sD.setIsLogedin(0);
				}
			}
			else {
				mT.rentACar(&dbdir, name);
			}
			break;
		case 4:
			if (isAdmin) {
				mT.removeRent(&dbdir, name);
				break;
			}
			else {
				std::cout << "Choose a number from the choices presented above." << std::endl;
				break;
			}
		case 7:
			if (isAdmin) {
				crT.createTable(dbdir);
				break;
			}
			else {
				std::cout << "Choose a number from the choices presented above." << std::endl;
				break;
			}
		case 8:
			if (isAdmin) {
				mT.addData(dbdir);
				break;
			}
			else {
				std::cout << "Choose a number from the choices presented above." << std::endl;
				break;
			}
		case 9:
			if (isAdmin) {
				mT.changeCarNotes(&dbdir);
				break;
			}
			else {
				std::cout << "Choose a number from the choices presented above." << std::endl;
				break;
			}
		case -1:
			std::cout << "The choice must be a positive numerical value." << std::endl;
			break;
		default:
			std::cout << "Choose a number from the choices presented above." << std::endl;
			break;
		}
	} while (choice != 0);
}
