/*
	Car list that has:
	- carID
	- License plat
	- Make
	- Model
	- Color
	- Availablility
	
	Renters list:
	- rentID
	- Full name (split in two?)
	- Car's ID that is being rented (any other car info?)
	- Perhaps other notes, like known dents/other issues (for company and renter insurance)


*/

<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <string>

#include "tableManip.h"

using namespace std;

const string dbdir = "c:\\CarRentalDB\\";

int main() {
	int choice = 0;
	createDeleteTable crT;
	manipTable mT;



	do {
		cout << "Choose your option: " << endl;
		cout << "1 - Create new table" << endl;
		cout << "2 - Add data to an existing table" << endl;
		cout << "0 - exit" << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			crT.createTable(dbdir);
			break;
		case 2:
			mT.addData(dbdir);
			break;
		default:
			cout << "Choose a number from the choices presented above." << endl;
			break;
		}
	} while (choice != 0);
}
=======
//Adding some changes for the memes
>>>>>>> 88bce0aee3225c7af39a63554d419db8e906050a
