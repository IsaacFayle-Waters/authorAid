#include "dbInteract.h"
#include <iostream>
#include <sstream>
#include <string>
#include <sqlite3.h>
#include <vector>

std::vector <std::string> returnCount;
std::string data2("");

std::string tableBaseCreate()
{  //INTEGER PRIMARY KEY MAY AUTOMATE THE INDEXING
	std::string tableString = 
		"CREATE TABLE IF NOT EXISTS CHARACTER("
		"ID INT PRIMARY KEY     NOT NULL, "
		"NAME           TEXT        NULL, "
		"AGE            INT			NULL, "
		"DESCRIPTION    TEXT		NULL, "
		"MOTIVE         TEXT		NULL, "
		"GENDER         TEXT		NULL, "
		"NOTES          TEXT		NULL, "
		"EXISTS_BOOL    INT      NOT NULL);"
		
		"CREATE TABLE IF NOT EXISTS SCENE("
		"ID INT PRIMARY KEY     NOT NULL,  "
		"LOCATION       TEXT		NULL,  "
		"TIME_DATE      TEXT        NULL,  "
		"SCENE_NAME		TEXT		NULL,  "
		"GEN_DSCRPT     TEXT		NULL,  "
		"NOTES			TEXT		NULL,  "			
		"SCENE_NUM		INT			NULL,  "
		"CHARACTERS     BLOB		NULL,  "
		"NUM_CRCTRS		INT			NULL );"
		
		"CREATE TABLE IF NOT EXISTS CHAPTER("
		"ID INT PRIMARY KEY      NOT NULL, "
		"CHPTR_NUM		INT			 NULL, "
		"CHPTR_NAME		TEXT		 NULL, "
		"SCENES			BLOB		 NULL, "
		"NUM_SCENES		INT		 NOT NULL, "
		"NOTES          TEXT         NULL);"
		
		"CREATE TABLE IF NOT EXISTS NGI("
		"ID INT PRIMARY KEY		 NOT NULL, "
		"TITLE			TEXT		 NULL, "
		"SETTING		TEXT		 NULL, "
		"GENRE			TEXT		 NULL, "
		"GEN_DSCRPT		TEXT		 NULL, "
		"CHAPTERS		BLOB		 NULL, "
		"NUM_CHAPTERS   INT		 NOT NULL, "
		"NOTES			TEXT		 NULL);"

		"CREATE TABLE IF NOT EXISTS WORLD("
		"ID INT PRIMARY KEY      NOT NULL, "
		"CHA_COUNT      INT		 NOT NULL, "
		"LOC_COUNT		INT		 NOT NULL, "
		"SCENE_COUNT    INT		 NOT NULL, "
		"NAME			TEXT		 NULL, "
		"DESCRIPTION    TEXT         NULL, "
		"NOTES          TEXT         NULL, "
		"EXISTS_BOOL    INT      NOT NULL);"
		;

	return tableString;
}

std::string queryAllFieldsTable(std::string tableName)
{
	//Use with the bellow in main
	//exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL)
	std::string qry = "SELECT * FROM " + tableName + ";";
	return qry;
}
std::string dropT(std::string table)
{	
	std::string sql = "DROP TABLE ["+ table +"];";
	return sql;
}
//remove in relation to id
std::string removeIDFromTable(std::string table,int id)
{
	std::string sID = std::to_string(id);
	std::string sql = "DELETE FROM "+ table +" WHERE ID = "+sID+";";

	return sql;
}
//Select field(s) from specific table
std::string selectFrom(std::string selection, std::string fromTable,int limit, int offset)
{	//consider using 'WHERE ID =ID' instead?
	std::string lim = std::to_string(limit);
	std::string offs = std::to_string(offset);

	std::string sql = "SELECT " + selection + " FROM " + fromTable +" LIMIT "+ lim +" OFFSET "+ offs +";";

	return sql;
}
std::string updateDb(std::string table, std::string column, std::string value, int id)
{	 
	std::string sID = std::to_string(id);
	
	std::string sql("UPDATE "+table+" SET "+column+" = '"+value+"' WHERE ID = "+sID+";");
	
	return sql;
}
//insert something into a table. Name of Table, 
std::string insertSpecific(std::string table, std::string column, std::string value, int id, bool idOnOff)
{
	if (idOnOff == true) {
		std::string sID = std::to_string(id);
		std::string sql("INSERT INTO " + table + " (ID," + column + ") VALUES (" + sID + ", '" + value + "');");
		return sql;
	}
	else if (idOnOff == false) {
		std::string sql("INSERT INTO " + table + " (ID," + column + ") VALUES ('NULL," + value + "');");
		std::cout <<std::endl << sql << std::endl;
		return sql;
	}
	else {
		std::cout << std::endl << "ERROR SELECTION" << std::endl;
		return "";
	}
}
//Might find that this is redundant, but helpful for now in populating db.
std::string insertCharacter(Character character,int index, int Update_1_Insert_0)
{  
	std::string newdex = std::to_string(index);
	std::string name = character.getName();
	int ageTemp = character.getCharacterAge();
	std::string age = std::to_string(ageTemp);
	std::string description = character.getDescription();
	std::string motive = character.getMotive();
	std::string gender = character.getGender();
	std::string notes = character.getNotes();
	if (Update_1_Insert_0 == 0) {
		std::string sql("INSERT INTO CHARACTER VALUES(" + newdex + ",'" + name + "'," + age + ",'" + description + "',"
			"'" + motive + "','" + gender + "', '" + notes + "');");
		return sql;
	}
	else if (Update_1_Insert_0 == 1) {
		std::string sql("UPDATE CHARACTER SET NAME = '" + name + "', AGE = " + age + ", DESCRIPTION = '" + description + "', "    
						"MOTIVE = '" + motive + "', GENDER = '" + gender + "', NOTES = '" + notes + "' WHERE ID = " + newdex + ";");
		return sql;
	}
	else {
		std::cout << std::endl << "ERROR SELECTION" << std::endl;
		return "";
	}
}

int countersWorld(char dbNameString[],int chaCount, std::string readOrWrite)
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string chaCounter = std::to_string(chaCount);

	if (readOrWrite == "read") {
		int ret = 0;
		
		std::string sqlRead("SELECT CHA_COUNT FROM WORLD;"); 
		exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
		std::string retCount = returnCount.at(0);

		std::stringstream myStream(retCount);
		myStream >> ret;
		returnCount.clear();
		errorInsert(exit);
		return ret;
	}
	else if (readOrWrite == "write") {
		
		std::string sqlWrite("UPDATE WORLD SET CHA_COUNT = " + chaCounter + ";");
		exit = sqlite3_exec(db, sqlWrite.c_str(),0, 0, NULL);
		errorInsert(exit);
	}
	else {
		std::cerr << "Counter error" << std::endl;
	}
	sqlite3_close(db);
}

void errorInsert(int exit) {
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
	}
}

int callbackDbInter(void* data, int argc, char** argv, char** azColName) {
	
	int i;
	//Recieve data
	for (i = 0; i < argc; i++) {
		if (argv[i]) {
			returnCount.push_back(argv[i]);	
		}
	}
	return 0;
}
