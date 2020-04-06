#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Scene.h"
//Create base tables. At the moment, only creates character table. 
void tableBaseCreate(char dbNameString[]);
//Display all in Table.
void queryAllFieldsTable(std::string tableName, char dbNameString[]);
//Delete table
void dropT(std::string table, char dbNameString[]);
//Remove row from table
void removeIDFromTable(std::string table, int id, char dbNameString[]);
//select something from table
void selectFrom(std::string selection, std::string fromTable, int limit, int offset, char dbNameString[], bool printOnly);
//Update values
std::string updateDb(std::string table, std::string column, std::string value, int id);
//Insert new item into table, via specific sql string.
std::string insertSpecific(std::string table, std::string column, std::string value, int id, bool idOnOff);
//Character loader/Updater
void insertCharacter(Character character, int index, int Update_1_Insert_0, char dbNameString[]);
//Scene loader/Updater
void insertScene(Scene scene, int index, int Update_1_Insert_0, char dbNameString[], std::string chtrList);
//Read and write character counter to World
int countersWorld(char dbNameString[], int chaCount, std::string readOrWrite);
//Read and write scene counter to World
int sceneCountersWorld(char dbNameString[], int sceneCount, std::string readOrWrite);
//db insert error
void errorInsert(int exit);
//Callback functions. Second one displays the info, and is probably just for testing.
int callbackDbInter(void* data, int argc, char** argv, char** azColName);
int callbackDbPrint(void* data, int argc, char** argv, char** azColName);

