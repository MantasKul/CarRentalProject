#pragma once

#include <string>
#include <vector>

// Class for adding/deleting table
class createDeleteTable {
	std::vector<std::string> tableNameList;
public:
	int createTable(const std::string);
};

// Populating or Updating an existing table
class manipTable {
public:
	int addData(const std::string);
	int registerUser(const std::string);
	int rentACar(const std::string*, std::string name);
	int removeRent(const std::string*, std::string name);
	int changeCarNotes(const std::string*);
};

// Data selection
class selectData {
	std::string logedInName;
	int isAdmin;
	int isLogedin;
public:
	void getCarList(const std::string);
	int logIn(const std::string);
	
	void setLogedInName(std::string n) { logedInName = n; };
	std::string getLogedInName() { return logedInName; };

	void setIsLogedin(int i = 0) { isLogedin = i; };
	int getIsLogedin() { return isLogedin; };

	void setIsAdmin(int i = 0) { isAdmin = i; };
	int getIsAdmin() { return isAdmin; };
};