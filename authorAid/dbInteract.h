#pragma once
#include <string>
#include <vector>
#include "Character.h"
//Create base tables. At the moment, only creates character table. 
std::string tableBaseCreate();
//Display all in Table.
std::string queryAllFieldsTable(std::string tableName);
//Delete table
std::string dropT(std::string table);
//Remove table
std::string removeIDFromTable(std::string table, int id);
//select something from table
std::string selectFrom(std::string selection, std::string fromTable, int limit, int offset);
//Update values
std::string updateDb(std::string table, std::string column, std::string value, int id);
//Insert new item into table, via specific sql string.
std::string insertSpecific(std::string table, std::string column, std::string value, int id, bool idOnOff);

//Character loader/Updater
std::string insertCharacter(Character character, int index, int Update_1_Insert_0);
//Read and write chaCounter to World
int countersWorld(char dbNameString[], int chaCount, std::string readOrWrite);
//db error
void errorInsert(int exit);
//
int callbackDbInter(void* data, int argc, char** argv, char** azColName);

