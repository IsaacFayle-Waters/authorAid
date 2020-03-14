#pragma once
#include <string>
#include "Character.h"
//Create base tables. At the moment, only creates character table. 
std::string tableBaseCreate();
//Display all in Table.
std::string queryAllFieldsTable(std::string tableName);
//Delete table
std::string dropT(std::string table);
//Remove table
std::string removeIDFromTable(int id);
//select something from table
std::string selectFrom(std::string selection, std::string fromTable, int limit, int offset);

//Character loader
//possibly tempory function because I'm bored. Find better way later.
//More of a test
std::string insertCharacter(Character character, int index);


