#include "tableManip.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <sqlite3.h>
#include <fstream>

int createDeleteTable::createTable(const string dir) {
	sqlite3* DB;
	const char* d; // dir with tableName will be combined, used in sqlite3_open()

	string tableName;
	int columnNo;
	string columnInput;
	vector<string> columnInfo;

	// Choosing name and column amount
	cout << "Choose a name for the table: ";
	cin >> tableName;
	// combinging directory, tableName and adding ".db", added all that to d to use int sqlite3_open()
	string temp = dir + tableName + ".db";
	d = temp.c_str();
	// Checking if file exists
	ifstream ifile;
	ifile.open(temp);
	if (ifile) {
		cout << "Table with such name already exists" << endl;
		ifile.close();
		return 0;
	}
	ifile.close();

	cout << "Choose how many columns you want in your table: ";
	cin >> columnNo;
	cin.ignore(); // Added so the getlin() later wouldn't skip first for cycle input

	//adding each column to columnInfo vector
	for (int i = 0; i < columnNo; i++) {
		printf("Enter %d column name, type, other information:\n", i);
		getline(cin, columnInput);
		columnInfo.push_back(columnInput);
	}

	//creating query string to create a table
	string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
	for (string s : columnInfo) {
		sql += s + ", ";
	}
	sql.pop_back(); sql.pop_back(); // Removing ", " that has been added in the for cycle at the end, unnecessary
	sql += " );";

	//Creating the Table
	try {
		int exit = 0;
		exit = sqlite3_open(d, &DB);

		char* messageError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK) {
			cerr << "Error Create Table" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Table create Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}

	return 0;
}