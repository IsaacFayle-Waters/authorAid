#include "dbInteract.h"
#include <iostream>
#include <string>
#include <sqlite3.h>

std::string tableBaseCreate()
{
	std::string tableString = 
		"CREATE TABLE CHARACTER("
		"ID INT PRIMARY KEY     NOT NULL, "
		"NAME           TEXT        NULL, "
		"AGE            INT			NULL, "
		"DESCRIPTION    TEXT		NULL, "
		"MOTIVE         TEXT		NULL, "
		"GENDER         TEXT		NULL, "
		"NOTES          TEXT		NULL );"
		
		"CREATE TABLE SCENE("
		"ID INT PRIMARY KEY     NOT NULL,  "
		"LOCATION       TEXT		NULL,  "
		"TIME_DATE      TEXT        NULL,  "
		"SCENE_NAME		TEXT		NULL,  "
		"GEN_DSCRPT     TEXT		NULL,  "
		"NOTES			TEXT		NULL,  "			
		"SCENE_NUM		INT			NULL,  "
		"CHARACTERS     BLOB		NULL,  "
		"NUM_CRCTRS		INT			NULL );"
		
		"CREATE TABLE CHAPTER("
		"ID INT PRIMARY KEY      NOT NULL, "
		"CHPTR_NUM		INT			 NULL, "
		"CHPTR_NAME		TEXT		 NULL, "
		"SCENES			BLOB		 NULL, "
		"NUM_SCENES		INT		 NOT NULL, "
		"NOTES          TEXT         NULL);"
		
		"CREATE TABLE NGI("
		"ID INT PRIMARY KEY		 NOT NULL, "
		"TITLE			TEXT		 NULL, "
		"SETTING		TEXT		 NULL, "
		"GENRE			TEXT		 NULL, "
		"GEN_DSCRPT		TEXT		 NULL, "
		"CHAPTERS		BLOB		 NULL, "
		"NUM_CHAPTERS   INT		 NOT NULL, "
		"NOTES			TEXT		 NULL);"			
		;

	return tableString;
}

std::string queryAllFieldsTable(std::string tableName)
{
	std::string qry = "SELECT * FROM " + tableName + ";";
	return qry;
}
std::string dropT(std::string table)
{	
	std::string sql = "DROP TABLE ["+ table +"];";
	return sql;
}
//Might find that this is redundant, but helpful for now in populating db.
std::string insertCharacter(Character character,int index)
{
	std::string newdex = std::to_string(index);
	std::string name = character.getName();
	int ageTemp = character.getCharacterAge();
	std::string age = std::to_string(ageTemp);
	std::string description = character.getDescription();
	std::string motive = character.getMotive();
	std::string gender = character.getGender();
	std::string notes = character.getNotes();
	std::string sql("INSERT INTO CHARACTER VALUES("+ newdex +",'"+ name +"',"+ age +",'"+description+"',"
					"'"+ motive +"','"+gender+"', '"+notes+"');");

	return sql;
}
