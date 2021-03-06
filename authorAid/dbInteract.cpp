#include "dbInteract.h"
#include <iostream>
#include <sstream>
#include <string>
#include <sqlite3.h>
#include <vector>

std::vector <std::string> returnCount;
std::string data2("");

void tableBaseCreate(char dbNameString[])
{  //INTEGER PRIMARY KEY MAY AUTOMATE THE INDEXING
	std::string sql = 
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
		"SCENE_NUM		INT		NOT	NULL,  "
		"CHARACTERS     TEXT		NULL,  "
		"NUM_CRCTRS		INT		NOT	NULL,  "
		"EXISTS_BOOL    INT     NOT NULL); "
		
		"CREATE TABLE IF NOT EXISTS CHAPTER("
		"ID INT PRIMARY KEY      NOT NULL, "
		"CHPTR_NUM		INT			 NULL, "
		"CHPTR_NAME		TEXT		 NULL, "
		"SCENES			TEXT		 NULL, "
		"NUM_SCENES		INT		 NOT NULL, "
		"GEN_DSCRPT		TEXT		 NULL, "
		"NOTES          TEXT         NULL, "
		"EXISTS_BOOL    INT      NOT NULL);"
		
		"CREATE TABLE IF NOT EXISTS NGI("
		"ID INT PRIMARY KEY		 NOT NULL, "
		"TITLE			TEXT		 NULL, "
		"SETTING		TEXT		 NULL, "
		"GENRE			TEXT		 NULL, "
		"GEN_DSCRPT		TEXT		 NULL, "
		"CHAPTERS		TEXT		 NULL, "
		"NUM_CHAPTERS   INT		 NOT NULL, "
		"NOTES			TEXT		 NULL, "
		"EXISTS_BOOL    INT      NOT NULL);"

		"CREATE TABLE IF NOT EXISTS WORLD("
		"ID INT PRIMARY KEY      NOT NULL, "
		"CHA_COUNT      INT		 NOT NULL, "
		"LOC_COUNT		INT		 NOT NULL, "
		"SCENE_COUNT    INT		 NOT NULL, "
		"NAME			TEXT		 NULL, "
		"DESCRIPTION    TEXT         NULL, "
		"NOTES          TEXT         NULL, "
		"EXISTS_BOOL    INT      NOT NULL, "
		"CHAPT_COUNT    INT      NOT NULL, "
		"NGI_COUNT      INT      NOT NULL, "
		"NGIS           TEXT         NULL);"
		;

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, NULL, NULL);
	errorInsert(exit);
	sqlite3_close(db);
}

void queryAllFieldsTable(std::string tableName,char dbNameString[])
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string query = "SELECT * FROM " + tableName + ";";
	exit = sqlite3_exec(db, query.c_str(), callbackDbPrint, NULL, NULL);
	errorInsert(exit);
	sqlite3_close(db);
}
void dropT(std::string table, char dbNameString[])
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string sql = "DROP TABLE ["+ table +"];";
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, NULL, NULL);
	errorInsert(exit);
	sqlite3_close(db);
}
//remove in relation to id
void removeIDFromTable(std::string table,int id,char dbNameString[])
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string sID = std::to_string(id);
	std::string sql = "DELETE FROM "+ table +" WHERE ID = "+sID+";";
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, NULL, NULL);
	errorInsert(exit);
	sqlite3_close(db);
}
//Select field(s) from specific table
void selectFrom(std::string selection, std::string fromTable,int limit, int offset,char dbNameString[],bool printOnly)
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	//consider using 'WHERE ID =ID' instead?
	std::string lim = std::to_string(limit);
	std::string offs = std::to_string(offset);
	std::string sql = "SELECT " + selection + " FROM " + fromTable +" LIMIT "+ lim +" OFFSET "+ offs +";";
	std::cout << sql << std::endl;
	if (printOnly == true) {
		exit = sqlite3_exec(db, sql.c_str(), callbackDbPrint, NULL, NULL);
	}
	else if (printOnly == false) {
		returnCount.clear();
		exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	}
	else {
		std::cerr << "ERROR SELECT!" << std::endl;
	}
	errorInsert(exit);
	sqlite3_close(db);
	//return sql;
}
void selectFromWhere(std::string selection, std::string fromTable, std::string where, std::string what, char dbNameString[], bool printOnly)
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	//SELECT SCENE_NAME, LOCATION, TIME_DATEFROM SCENEWHERE SCENE_NUM = 1;
	std::string sql = "SELECT " + selection + " FROM " + fromTable + " WHERE " + where + "= " + what + ";";
	std::cout << sql << std::endl;
	if (printOnly == true) {
		exit = sqlite3_exec(db, sql.c_str(), callbackDbPrint, NULL, NULL);
	}
	else if (printOnly == false) {
		returnCount.clear();
		exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	}
	else {
		std::cerr << "ERROR SELECT!" << std::endl;
	}
	errorInsert(exit);
	sqlite3_close(db);
}
void updateDb(std::string table, std::string column, std::string value, int id,char dbNameString[])
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	std::string sID = std::to_string(id);
	
	std::string sql("UPDATE "+table+" SET "+column+" = '"+value+"' WHERE ID = "+sID+";");
	std::cout << sql << std::endl;
	returnCount.clear();
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	sqlite3_close(db);
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
void insertCharacter(Character character,int index, int Update_1_Insert_0, char dbNameString[])
{  
	std::string sql;

	std::string newdex = std::to_string(index);
	std::string name = character.getName();
	int ageTemp = character.getCharacterAge();
	std::string age = std::to_string(ageTemp);
	std::string description = character.getDescription();
	std::string motive = character.getMotive();
	std::string gender = character.getGender();
	std::string notes = character.getNotes();
	bool exists = character.getExistence();
	
	std::string bool_exists = "0";
	if (exists == true) {
		bool_exists = "1";
	}

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	if (Update_1_Insert_0 == 0) {
		sql = ("INSERT INTO CHARACTER VALUES(" + newdex + ",'" + name + "'," + age + ",'" + description + "',"
			"'" + motive + "','" + gender + "', '" + notes + "', " + bool_exists + ");");
	}
	else if (Update_1_Insert_0 == 1) {
		sql = ("UPDATE CHARACTER SET NAME = '" + name + "', AGE = " + age + ", DESCRIPTION = '" + description + "', "    
						"MOTIVE = '" + motive + "', GENDER = '" + gender + "', NOTES = '" + notes + "' WHERE ID = " + newdex + ";");
	}
	else {
		std::cout << std::endl << "ERROR character SELECTION" << std::endl;
	}
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	sqlite3_close(db);
}

void insertScene(Scene scene, int index, int Update_1_Insert_0, char dbNameString[], std::string chtrList)
{
	std::string sql;

	std::string newdex = std::to_string(index);
	std::string name = scene.getName();
	std::string location = scene.getLocation();
	int numChtrsInt = scene.getNumberOfCharacters();
	std::string  numChtrs = std::to_string(numChtrsInt);
	int sceneNumInt = scene.getSceneNumber();
	std::string sceneNum = std::to_string(sceneNumInt);
	std::string description = scene.getDescription();
	std::string timeDate = scene.getTimeAndOrDate();
	std::string characters = chtrList;
	std::string notes = scene.getNotes();
	bool exists = scene.getExistence();

	std::string bool_exists = "0";
	if (exists == true) {
		bool_exists = "1";
	}
	
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	if (Update_1_Insert_0 == 0) {
		sql = ("INSERT INTO SCENE (ID, SCENE_NAME,LOCATION,TIME_DATE,GEN_DSCRPT, SCENE_NUM, CHARACTERS, NUM_CRCTRS, NOTES, EXISTS_BOOL) VALUES(" + newdex + ",'" + name + "','" +location + "','" + timeDate + "','"  + description + "',"
			 + newdex + ",'" + characters + "',"+numChtrs+", '" + notes + "', " + bool_exists + ");");
		std::cout << sql << std::endl;
	}
	else if (Update_1_Insert_0 == 1) {
		sql = ("UPDATE SCENE SET SCENE_NAME = '" + name + "', LOCATION = '" + location + "',TIME_DATE = '"+timeDate+"', GEN_DSCRPT = '" + description + "', "
			"SCENE_NUM = " + sceneNum + ", CHARACTERS = '" + characters + "', NUM_CRCTRS = " +numChtrs+ ", NOTES = '" + notes + "' WHERE ID = " + newdex + ";");
		std::cout << sql << std::endl;
	}
	else {
		std::cout << std::endl << "ERROR Scene SELECTION" << std::endl;
	}
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	sqlite3_close(db);
}
void insertChapter(Chapter chapter, int index, int Update_1_Insert_0, char dbNameString[], std::string sceneList)
{
	std::string sql;

	std::string newdex = std::to_string(index);
	int chaptNumInt = chapter.getChapterNumber();
	std::string chaptNum = std::to_string(chaptNumInt);
	std::string name = chapter.getName();
	std::string scenes = sceneList;
	int numScenesInt = chapter.getNumberOfScenes();
	std::string numScenes = std::to_string(numScenesInt);
	std::string genDSCRPT = chapter.getDescription();
	std::string notes = chapter.getNotes();
	bool exists = chapter.getExistence();

	std::string bool_exists = "0";
	if (exists == true) {
		bool_exists = "1";
	}

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	if (Update_1_Insert_0 == 0) {
		sql = ("INSERT INTO CHAPTER (ID, CHPTR_NUM, CHPTR_NAME, SCENES, NUM_SCENES, GEN_DSCRPT, NOTES, EXISTS_BOOL)" 
			"VALUES(" + newdex + "," + chaptNum + ",'" + name + "','" + scenes + "'," + numScenes + ",'"
			+ genDSCRPT + "','" + notes + "', " + bool_exists + ");");
		std::cout << sql << std::endl;
	}
	else if (Update_1_Insert_0 == 1) {
		sql = ("UPDATE CHAPTER SET CHPTR_NUM = " + chaptNum + ", CHPTR_NAME = '" + name + "', SCENES = '" + sceneList + "', NUM_SCENES = "+numScenes+", GEN_DSCRPT = '" + genDSCRPT + "', "
			"NOTES = '" + notes +"', EXISTS_BOOL = "+ bool_exists +" WHERE ID = " + newdex + ";");
		std::cout << sql << std::endl;
	}
	else {
		std::cout << std::endl << "ERROR CHAPTER SELECTION" << std::endl;
	}
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	sqlite3_close(db);
}
void insertNGI(NarativeGeneralInfo ngi, int index, int Update_1_Insert_0, char dbNameString[], std::string chapterList)
{
	std::string sql;

	std::string newdex = std::to_string(index);
	std::string title = ngi.getTitle();
	std::string setting = ngi.getSetting();
	std::string genre = ngi.getGenre();
	std::string genDSCRPT = ngi.getDescription(); 
	std::string chapters = chapterList;
	int numChaptersInt = ngi.getNumberOfChapters();
	std::string numChapters = std::to_string(numChaptersInt);
	std::string notes = ngi.getNotes();
	bool exists = ngi.getExistence();

	std::string bool_exists = "0";
	if (exists == true) {
		bool_exists = "1";
	}
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);

	if (Update_1_Insert_0 == 0) {
		sql = ("INSERT INTO NGI (ID, TITLE, SETTING, GENRE, GEN_DSCRPT, CHAPTERS, NUM_CHAPTERS, NOTES, EXISTS_BOOL)"
			"VALUES(" + newdex + ",'" + title + "','" + setting + "','" + genre + "','" + genDSCRPT + "','"+chapters +"',"+numChapters+",'" + notes + "', " + bool_exists + ");");
		std::cout << sql << std::endl;
	}
	else if (Update_1_Insert_0 == 1) {
		sql = ("UPDATE NGI SET TITLE = '" + title + "', SETTING = '" + setting + "', GENRE = '"+genre+"', CHAPTERS = '" + chapterList + "', NUM_CHAPTERS = " + numChapters + ", GEN_DSCRPT = '" + genDSCRPT + "', "
			"NOTES = '" + notes + "', EXISTS_BOOL = " + bool_exists + " WHERE ID = " + newdex + ";");
		std::cout << sql << std::endl;
	}
	else {
		std::cout << std::endl << "ERROR ngi SELECTION" << std::endl;
	}
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	sqlite3_close(db);
}
void insertWorld(World world, char dbNameString[], std::string ngiList)
{
	std::string sql;
	std::string name = world.getName();
	std::string description = world.getDescription();
	std::string notes = world.getNotes();

	sql = ("UPDATE WORLD SET NAME ='"+ name +"', DESCRIPTION = '"+ description +"', NOTES = '"+ notes +"';");
	std::cout << sql << std::endl;
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	exit = sqlite3_exec(db, sql.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	sqlite3_close(db);

}
//Read and write counters from db
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
//Scene counter (COULD BE MERGED WITH COUNTERS WORLD)
int sceneCountersWorld(char dbNameString[], int sceneCount, std::string readOrWrite)
{

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string sceneCounter = std::to_string(sceneCount);

	if (readOrWrite == "read") {
		int ret = 0;
		returnCount.clear();
		std::string sqlRead("SELECT SCENE_COUNT FROM WORLD;");
		exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
		std::string retCount = returnCount.at(0);

		std::stringstream myStream(retCount);
		myStream >> ret;
		returnCount.clear();
		errorInsert(exit);
		return ret;
	}
	else if (readOrWrite == "write") {

		std::string sqlWrite("UPDATE WORLD SET SCENE_COUNT = " + sceneCounter + ";");
		exit = sqlite3_exec(db, sqlWrite.c_str(), 0, 0, NULL);
		errorInsert(exit);
	}
	else {
		std::cerr << "Counter error" << std::endl;
	}
	sqlite3_close(db);
}

int chapterCountersWorld(char dbNameString[], int chapterCount, std::string readOrWrite)
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string chapterCounter = std::to_string(chapterCount);
	if (readOrWrite == "read") {
		int ret = 0;
		returnCount.clear();
		std::string sqlRead("SELECT CHAPT_COUNT FROM WORLD;");
		exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
		std::string retCount = returnCount.at(0);

		std::stringstream myStream(retCount);
		myStream >> ret;
		returnCount.clear();
		errorInsert(exit);
		return ret;
	}
	else if (readOrWrite == "write") {

		std::string sqlWrite("UPDATE WORLD SET CHAPT_COUNT = " + chapterCounter + ";");
		exit = sqlite3_exec(db, sqlWrite.c_str(), 0, 0, NULL);
		errorInsert(exit);
	}
	else {
		std::cerr << "Counter error" << std::endl;
	}
	sqlite3_close(db);

}

int ngiCountersWorld(char dbNameString[], int ngiCount, std::string readOrWrite)
{
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	std::string ngiCounter = std::to_string(ngiCount);
	if (readOrWrite == "read") {
		int ret = 0;
		returnCount.clear();
		std::string sqlRead("SELECT NGI_COUNT FROM WORLD;");
		exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
		std::string retCount = returnCount.at(0);

		std::stringstream myStream(retCount);
		myStream >> ret;
		returnCount.clear();
		errorInsert(exit);
		return ret;
	}
	else if (readOrWrite == "write") {

		std::string sqlWrite("UPDATE WORLD SET NGI_COUNT = " + ngiCounter + ";");
		exit = sqlite3_exec(db, sqlWrite.c_str(), 0, 0, NULL);
		errorInsert(exit);
	}
	else {
		std::cerr << "Counter error" << std::endl;
	}
	sqlite3_close(db);
}

int returnNumberChtrsScene(int sceneCount, char dbNameString[])
{
	std::string id = std::to_string(sceneCount);
	std::string sqlRead("SELECT NUM_CRCTRS FROM SCENE WHERE ID = "+id+";");
	int ret = 0;
	
	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	returnCount.clear();
	exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);
	
	Scene conv;
	ret = conv.convertToInt(returnCount.at(0));

	sqlite3_close(db);
	returnCount.clear();
	
	return ret;
}

int returnNumberScenesChapter(int chapterCount, char dbNameString[])
{
	std::string id = std::to_string(chapterCount);
	std::string sqlRead("SELECT NUM_SCENES FROM CHAPTER WHERE ID = " + id + ";");
	int ret = 0;

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	returnCount.clear();
	exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);

	World conv;
	ret = conv.convertToInt(returnCount.at(0));

	sqlite3_close(db);
	returnCount.clear();

	return ret;
}

int returnNumberChaptersNGI(int ngiCount, char dbNameString[])
{
	std::string id = std::to_string(ngiCount);
	std::string sqlRead("SELECT NUM_CHAPTERS FROM NGI WHERE ID = " + id + ";");
	int ret = 0;

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(dbNameString, &db);
	returnCount.clear();
	exit = sqlite3_exec(db, sqlRead.c_str(), callbackDbInter, (void*)data2.c_str(), NULL);
	errorInsert(exit);

	World conv;
	ret = conv.convertToInt(returnCount.at(0));

	sqlite3_close(db);
	returnCount.clear();

	return ret;
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

int callbackDbPrint(void* data, int argc, char** argv, char** azColName) {
	int i;
	//Recieve data
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		//Return to global
	}
	printf("\n");
	return 0;
}