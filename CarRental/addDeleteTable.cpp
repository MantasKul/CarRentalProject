#include "tableManip.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <sqlite3.h>
#include <fstream>
#include <algorithm>

// Should add so it would add to a file which has the list, file could be stored in the same CarRentalDB folder
// Return should get from the file as well

int createDeleteTable::createTable(const std::string dir) {
	sqlite3* DB;
	const char* d; // dir with tableName will be combined, used in sqlite3_open()
	//std::vector<std::string> tableNameList = getTableNameList();

	std::string tableName;
	int columnNo;
	std::string columnInput;
	std::vector<std::string> columnInfo;

	// Choosing name and column amount
	std::cout << "Choose a name for the table: ";
	std::cin >> tableName;

	// Checking if table with such name exists exists
	/*if (find(tableNameList.begin(), tableNameList.end(), tableName) != tableNameList.end()) {
		cout << "Table with such name already exists";
		return 0;
	}
	else {
		addTableNameList(tableName);

	}*/
	// combinging directory, tableName and adding ".db", added all that to d to use int sqlite3_open()

	std::string temp = dir + "carRental" + ".db";
	d = temp.c_str();

	std::cout << "Choose how many columns you want in your table: ";
	std::cin >> columnNo;
	std::cin.ignore(); // Added so the getlin() later wouldn't skip first for cycle input

	//adding each column to columnInfo vector
	for (int i = 0; i < columnNo; i++) {
		printf("Enter %d column name, type, other information:\n", i);
		std::getline(std::cin, columnInput);
		columnInfo.push_back(columnInput);
	}

	//creating query string to create a table
	std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
	for (std::string s : columnInfo) {
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
			std::cerr << "Error Create Table" << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table create Successfully" << std::endl;
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

	return 0;
}