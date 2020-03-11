#include "dbInteract.h"
#include <string>

std::string tableBaseCreate()
{
	std::string tableString = 
		"CREATE TABLE CHARACTER("
		"ID INT PRIMARY KEY     NOT NULL, "
		"NAME           TEXT    NOT NULL, "
		"AGE            INT     NOT NULL, "
		"DESCRIPTION    TEXT    NOT NULL, "
		"MOTIVE         TEXT    NOT NULL, "
		"GENDER         TEXT    NOT NULL, "
		"NOTES          TEXT    NOT NULL );";

	return tableString;
}

std::string queryAllFieldsTable(std::string tableName)
{
	std::string qry = "SELECT * FROM " + tableName + ";";
	return qry;
}
