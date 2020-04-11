#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Scene.h"
#include "Chapter.h"
#include "narativeGeneralInfo.h"
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
void selectFromWhere(std::string selection, std::string fromTable, std::string where, std::string what, char dbNameString[], bool printOnl);
//Update values
void updateDb(std::string table, std::string column, std::string value, int id, char dbNameString[]);
  ////////////
 //INSERTERS/
//Insert new item into table, via specific sql string.
std::string insertSpecific(std::string table, std::string column, std::string value, int id, bool idOnOff);
//Character loader/Updater
void insertCharacter(Character character, int index, int Update_1_Insert_0, char dbNameString[]);
//Scene loader/Updater
void insertScene(Scene scene, int index, int Update_1_Insert_0, char dbNameString[], std::string chtrList);
//Chapter loader/Updater
void insertChapter(Chapter chapter, int index, int Update_1_Insert_0, char dbNameString[], std::string sceneList);
//ngi loader/Updater
void insertNGI(NarativeGeneralInfo ngi, int index, int Update_1_Insert_0, char dbNameString[], std::string chapterList);
//Save changes to world
void insertWorld(World world, char dbNameString[], std::string ngiList);

//Read and write character counter to World
  ///////////
 //COUNTERS/
//Character counter
int countersWorld(char dbNameString[], int chaCount, std::string readOrWrite);
//Read and write scene counter to World
int sceneCountersWorld(char dbNameString[], int sceneCount, std::string readOrWrite);
//Read and write chapter counter to World
int chapterCountersWorld(char dbNameString[], int chapterCount, std::string readOrWrite);
//Read and write NGI counter to World
int ngiCountersWorld(char dbNameString[], int ngiCount, std::string readOrWrite);
  /////////////////
 //NUMBER RETURNS/
//Simple return from db of number of characters in a scene
int returnNumberChtrsScene(int sceneCount,char dbNameString[]);
//Simple return from db of number of scenes in a chapter
int returnNumberScenesChapter(int chapterCount, char dbNameString[]);
//Simple return from db of number of chapter in an ngi
int returnNumberChaptersNGI(int ngiCount, char dbNameString[]);
//db insert error
void errorInsert(int exit);
  ////////////
 //CALLBACKS/
//Callback functions. Second one displays the info, and is probably just for testing.
int callbackDbInter(void* data, int argc, char** argv, char** azColName);
int callbackDbPrint(void* data, int argc, char** argv, char** azColName);

