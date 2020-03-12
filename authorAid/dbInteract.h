#pragma once
#include <string>
#include "Character.h"
//Create base tables. At the moment, only creates character table. 
std::string tableBaseCreate();
//Display all in Table.
std::string queryAllFieldsTable(std::string tableName);
std::string dropT(std::string table);

//Character loader
//possibly tempory function because I'm bored. Find better way later.
//More of a test
std::string insertCharacter(Character character, int index);


