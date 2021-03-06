//The aim is to build a flexible app that alows a user to freely keep track of their written creations. For example,
//a user may just feel like jotting down some details about a character, but not know their name, age, 
//or what story the character belongs to yet. Similarly a scene may be imagined without characters, etc.
//
//On the other had the user should have a sturdy framework to work with if they so choose.

//TODO GUI

//TODO Pass some menu options/sections of code as functions instead. Getting a little messy as is.
//Same for some of the dbInteract sections. Code could tip towards being difficult to maintain.
///Too much repeated code///. Example: counter functions could be merged.

//TODO take steps to prevent sql injection
//TODO Investigate memory leak possiblities

//TODO DEBUG insert chtr. Load and update possible problems
//TODO need to find a way to safley delete from db. Update changes yet keep relations.
//Automation version of chapter numbers

//NOTE/TODO Cannot load two things in a row (only trid in scene). The characters become merged.

//TODO File handeling
//TODO eof completion check table. Possiblly better to wait for a while. Complete gui first.

//NOTE! POSSIBLE RE-DESIGN?: INCLUDE Db INTERACTION IN CLASSES INSTEAD? MIGHT MAKE THINGS LESS CONVOLOUTED. 
//Note. Could use sets to prevent already selected elements from being re-selected
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <sqlite3.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>


#include "Scene.h"
#include "Character.h"
#include "narativeGeneralInfo.h"
#include "Chapter.h"
#include "dbInteract.h"
#include "Location.h"

void printSceneInfo(Scene scene, bool charInfoOn);
void printCharacterInfo(Character character);
void printChapterInfo(Chapter chapter);
void printNarativeGeneralInfo(NarativeGeneralInfo ngi);
//OBSOLETE AFTER TEST/BUILD!!!/////////////////////////////////////// 
int callback(void* data, int argc, char** argv, char** azColName);//
void displayAndError(int exit, bool display);//////////////////////
//////////////////////////////////////////////
std::string removeFromStringList(int idToRemove, std::string stringlist);
int inputInt();
std::string inputChtrChoice(std::string message);

//Strings
std::string data("CALLBACK FUNCTION");
char dbNameString[] = "counterTest.db";
char dbNameString0[] = "exampleUpdateTest.db";
char dbNameString2[] = "example.db";

//Return strings from db used in displaying temporary pre-save details
std::vector <std::string> returnThis;
std::vector <std::string> identifyThis;
//May use this later for limiting options to those not already selected. Investigate c++ sets.
std::vector <int> deletedIDs;

//GLOBAL CHARACTER COUNT, CURRENTLY DRAWN FROM CALLBACK FUNCTION, BUT MUST CHANGE TO DB.
int chaCount = 0;//OBSOLETE
int chaCountWorld = 0;
int sceneCountWorld = 0;
int chaptCountWorld = 0;
int ngiCountWorld = 0;

//Used in a display function. Possibly redundent
int idCount = 0;//OBSOLETE
//save error messages. Possibly only used in test functions.
char* errMsg = 0;
//Testing from manually set values on/off
int visTest = 0;
int updateTest = 1;
int testUI = 1;

int main(int argc, char** argv) {
	//Read Counters from World Table
	//countersWorld(dbNameString, 15, "write");
	//chapterCountersWorld(dbNameString, 0, "write");
	//ngiCountersWorld(dbNameString, 1, "write");
	chaCountWorld = countersWorld(dbNameString, 0, "read");
	sceneCountWorld = sceneCountersWorld(dbNameString, 0, "read");
	chaptCountWorld = chapterCountersWorld(dbNameString, 0, "read");
	ngiCountWorld = ngiCountersWorld(dbNameString, 0, "read");
	
	//updateDb("WORLD", "SCENE_COUNT", "9", 1, dbNameString);
	//selectFromWhere("SCENE_NAME, LOCATION, TIME_DATE", "SCENE", "SCENE_NUM", "1", dbNameString, true);
	
	//Create db instance
	sqlite3 *db;
	//exit deals with sqlite read and write	
	int exit = 0;
	
	//Open db
	//TESTING PURPOSES DBs
	if (updateTest == 0){ 
		//WILL NO LONGER WORK - REMOVE
		exit = sqlite3_open(dbNameString0, &db); 
	}
	//COUNTER TEST
	else if (updateTest == 1) {
		exit = sqlite3_open(dbNameString, &db);
		chaCount = countersWorld(dbNameString, 0, "read");
	}
	else {
		//WILL NO LONGER WORK - REMOVE
		exit = sqlite3_open(dbNameString2, &db);
	}
	
	//dropT("NGI", dbNameString);
	//QUERIES AND TABLE SET UP, TEMPORARY UNTIL SYSTEM MORE ROBUST
	//tableBaseCreate(dbNameString);
	//std::string query("UPDATE WORLD SET NGIS = '' WHERE ID = 1;");
	//std::string query("ALTER TABLE WORLD ADD COLUMN NGIS TEXT;");
	//exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	//displayAndError(exit,false);
	//std::string query(removeIDFromTable(5));
	//exit = sqlite3_exec(db, create.c_str(), callback, (void*)data.c_str(), NULL);

	//Visual tests	
	queryAllFieldsTable("WORLD",dbNameString);
	queryAllFieldsTable("SCENE", dbNameString);
	queryAllFieldsTable("CHARACTER", dbNameString);
	queryAllFieldsTable("CHAPTER", dbNameString);
	queryAllFieldsTable("NGI", dbNameString);
	returnThis.clear();
	identifyThis.clear();
	displayAndError(exit, true);
		
	//////////////////////
	//TEMP UI OFF OR ON//
	////////////////////
	if (testUI) {
		int ui = 1;
		/////////////////
		//MAIN UI LOOP//
		///////////////
		while (ui) {
			//MAIN INPUT//
			std::string input;
			std::cout << "Enter an option: (view chtr), (insert chtr), (scene), (chapter), (ngi) (exit). " <<std::endl;
			std::getline(std::cin, input);
			//Exit condition//
			if (input == "exit") {
				ui = 0;
			}
			//View Character//
			else if (input == "view chtr") {
				int idIs;
				std::cout << "Character id is? ";
				idIs = inputInt() - 1;
				selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, idIs, dbNameString, true);
			}
			//Insert a charcter, having assigned some or all details (I don't like switch statements)
			else if (input == "insert chtr") {
				//exit condition
				int exitInsert = 1;
				//Character class temp
				Character tempChtr;
				bool fromLoad = false;
				int tempChaCount = 0;
				///////////////////
				//Main chtr loop//
				/////////////////
				while (exitInsert) {
					std::cout << "Character insert: please choose an attribute to insert." << std::endl <<
						"(n)ame, (a)ge, (d)escription, (m)otive,(g)ender,(notes)." << std::endl <<
						"(v)iew Character, (save), (load), (del)ete, Or (exit)." << std::endl;
					//input string
					std::string inputINS;
					std::getline(std::cin, inputINS);
					
					//Exit Condition
					if (inputINS == "exit") {
						exitInsert = 0;
						break;
					}
					//Enter Name
					else if (inputINS == "n") {
						tempChtr.setName(inputChtrChoice("What name do you want to insert? "));
					}
					//Enter Age
					else if (inputINS == "a") {
						std::cout << "Enter an age: " << std::endl;
						tempChtr.setCharacterAge(inputInt());
					}
					//Enter Description
					else if (inputINS == "d") {
						tempChtr.setDescription(inputChtrChoice("Describe the character: "));
					}
					//Enter Motive
					else if (inputINS == "m") {
						tempChtr.setMotive(inputChtrChoice("What is the character's motive? "));
					}
					//Enter Gender
					else if (inputINS == "g") {
						tempChtr.setGender(inputChtrChoice("Assign a gender? "));
					}
					//Enter Notes
					else if (inputINS == "notes") {
						tempChtr.setNotes(inputChtrChoice("Do you have any notes to make about this character? "));
						//tempChtr.setNotes(veryLongText);
					}
					//View Character
					else if (inputINS == "v") {
						printCharacterInfo(tempChtr);
					}
					//Save Character's details to table or Update Charcter's details.
					else if (inputINS == "save") {
						//Check to see if Character details were loaded, if so, deal with ID position from load
						if (fromLoad == true) {
							chaCountWorld = tempChaCount;
						}
						//If the character is now being inserted for the first time, 
						//it doesn't yet exist, so increment chaCountWorld
						if (tempChtr.getExistence() == false) {
							tempChtr.setExistence();
							chaCountWorld += 1;
							insertCharacter(tempChtr, chaCountWorld, 0, dbNameString);
							countersWorld(dbNameString, chaCountWorld, "write");
						}
						//If the character exists, then it is simply updated. Reset chaCountWorld after.
						else if (tempChtr.getExistence() == true) {
							insertCharacter(tempChtr, chaCountWorld, 1, dbNameString);
							chaCountWorld = countersWorld(dbNameString, 0, "read");
							break;
						}
					}
					//Load Caracter from db To update feilds
					else if (inputINS == "load") {
						///Display all Characters
						selectFrom("ID,NAME", "CHARACTER", chaCountWorld, 0, dbNameString, true);
						//Select Character by ID number
						std::cout << "Select Character ID from list, or -1 to cancel: ";
						//Get input, and set temp for purposes of updating
						int idLoadChoice = tempChaCount  = inputInt();
						if (idLoadChoice < 0 || idLoadChoice > chaCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						//External from dbInteract.cpp. Returns from callback used in selectFrom if printOnly = false
						extern std::vector <std::string> returnCount;
						//Select Return
						selectFrom("ID,NAME,AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, idLoadChoice, dbNameString, false);
						//Destructor
						//Return from selectFrom, adds details to tempchar.
						tempChtr.setCharacterFromDb(returnCount);
						//Clear return
						returnCount.clear();
						//Display loaded character, and check/set existence (Should already exist)
						printCharacterInfo(tempChtr);
						tempChtr.setExistence();
						//Confirm that Character is product of "load"
						fromLoad = true;
					}
					//Delete
					else if (inputINS == "del") {
						selectFrom("ID,NAME", "CHARACTER", chaCount, 0, dbNameString, true);
						std::cout << "Choose by id. -1 to cancel delete process: " << std::endl;
						int delChoice = inputInt();
						std::cout << delChoice;
						removeIDFromTable("CHARACTER", delChoice,dbNameString);
						//Prevent counter from getting out of sync
						if (delChoice == chaCountWorld) {
							chaCountWorld -= 1;
							countersWorld(dbNameString, chaCountWorld, "write");
						}
						//Keep list of deleted ids and re-insert new characters?. Could also write an empty
						//character in to avoid null problems.
						else {
							deletedIDs.push_back(delChoice);
						}
					}
				}	
			}
			 ///////////////
			 //Scene Loop//
		     /////////////
			else if (input == "scene") {
				//exit condition
				int exitScene = 1;
				//Various variables. Most of them probably even needed.
				Scene tempScene;
				int tempSceneCount = 0;
				bool fromLoad = false;
				//Read writcharacter lists
				std::vector <int> characterListForRemovalPurposes;
				std::string chtrList = "";
				int numCharacters = 0;
				while (exitScene) {
					std::cout << "Choose an option: (l)ocation, (t)ime, (n)ame,(d)escription,(notes)"
						"(add chtr), (rem)ove (chtr),(v)iew, (save), (load),(exit). " << std::endl;
					std::string inputSCE;
					std::getline(std::cin, inputSCE);

					//Exit Condition
					if (inputSCE == "exit") {
						exitScene = 0;
						
						break;
					}
					//temp, will become linked with location class
					else if (inputSCE == "l") {
						tempScene.setLocation(inputChtrChoice("What is the location?"));
					}
					//Time
					else if (inputSCE == "t") {
						tempScene.setTimeAndOrDate(inputChtrChoice("What is the time and/or date?"));
					}
					//Scene name
					else if (inputSCE == "n") {
						tempScene.setName(inputChtrChoice("What name do you want to insert? "));
					}
					//Scene description
					else if (inputSCE == "d") {
						tempScene.setDescription(inputChtrChoice("Describe the location: "));
					}
					//Scene notes
					else if (inputSCE == "notes") {
						tempScene.setNotes(inputChtrChoice("Would you like to make some notes on the scene?"));
					}
					//Add character to a scene
					else if (inputSCE == "add chtr") {
						Character tempChtr;
						std::cout << "Select Character ID from list, or -1 to cancel: ";
						selectFrom("ID,NAME", "CHARACTER", chaCountWorld, 0, dbNameString, true);
						//Select Character by ID number
						int idLoadChoice =  inputInt();
						if (idLoadChoice < 0 || idLoadChoice > chaCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::string choiceString = std::to_string(idLoadChoice);
						extern std::vector <std::string> returnCount;
						//Select Return
						selectFromWhere("ID,NAME,AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", "ID", choiceString , dbNameString, false);
						
						//Return from selectFrom, adds details to tempchar.
						tempChtr.setCharacterFromDb(returnCount);
						//Clear return
						returnCount.clear();
						tempScene.setCharacters(tempChtr);
						characterListForRemovalPurposes.push_back(idLoadChoice);
						//String representation						
						std::string idToAdd = std::to_string(idLoadChoice) + "N";
						chtrList += idToAdd;
						std::cout << chtrList << std::endl;
						//POSSIBLY OBSOLETE, AS setCharacters automatically increments this (?)
						try {
							numCharacters = returnNumberChtrsScene(sceneCountWorld, dbNameString);
							numCharacters += 1;
						}
						catch (std::out_of_range e) {
							std::cout << "UNABLE TO USE UNTIL WRITEN TO." << std::endl;
						}
					}
					//Remove Character from Loaded scene (i.e. remove from db), or temp pre-saved scene
					else if (inputSCE == "rem chtr") {
						//Remove from load/db
						if (fromLoad == true) {
							sceneCountWorld = tempSceneCount;
							///Who to remove
							std::string stringCount = std::to_string(sceneCountWorld);
							selectFromWhere("CHARACTERS", "SCENE", "SCENE_NUM", stringCount, dbNameString, true);
							std::cout << "Select Character ID from list, or -1 to cancel: ";
							/////HMMMMM!!!!!!!				
							int idLoadChoice = inputInt();
							if (idLoadChoice < 0 || idLoadChoice > chaCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							//SHOULD BE IN SAVE?
							//Covert element to remove, add delimiter 'N'
							std::string quickConvert = std::to_string(idLoadChoice);
							std::string quickConvertNumChtrs = "";
							quickConvert += "N";
							//Remove from string and update db
							boost::erase_all(chtrList, quickConvert);
							updateDb("SCENE", "CHARACTERS", chtrList, sceneCountWorld, dbNameString);
							//Decrement num chtrs
							numCharacters = returnNumberChtrsScene(sceneCountWorld, dbNameString);
							numCharacters -= 1;
							quickConvertNumChtrs = std::to_string(numCharacters);
							updateDb("SCENE", "NUM_CRCTRS", quickConvertNumChtrs, sceneCountWorld, dbNameString);
							//Reset scene counter (Possibly needless)
							//sceneCountWorld = sceneCountersWorld(dbNameString, 0, "read");
							break;
						}
						//remove from new pre-saved scene
						else {
							int rmLim = tempScene.getCharacterList().size();
							int removeThisEle = 0;
							for (int rmc = 0; rmc < rmLim; rmc++) {
								std::cout << rmc << " ";
								std::cout << tempScene.getCharacterList().at(rmc).getName() << "  ";
							}
							std::cout << "Select Character ID from list, or -1 to cancel: ";
							removeThisEle = inputInt();
							if (removeThisEle < 0 || removeThisEle > sceneCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							int realPosition = characterListForRemovalPurposes.at(removeThisEle);
							chtrList = removeFromStringList(realPosition, chtrList);
							tempScene.removeCharacterFromList(removeThisEle);
						}
					}
					//View scene
					else if (inputSCE == "v") {
						printSceneInfo(tempScene,true);
					}
					//Save current scene
					else if (inputSCE == "save") {
						//Check to see if Character details were loaded, if so, deal with ID position from load
						if (fromLoad == true) {
							sceneCountWorld = tempSceneCount;
						}
						//Check existence of scene
						if (tempScene.getExistence() == false) {
							tempScene.setExistence();
							sceneCountWorld += 1;
							insertScene(tempScene, sceneCountWorld, 0, dbNameString, chtrList);
							sceneCountersWorld(dbNameString, sceneCountWorld, "write");
							break;
						}
						//If the character exists, then it is simply updated. Reset sceneCountWorld after.
						else if (tempScene.getExistence() == true) {
							insertScene(tempScene, sceneCountWorld, 1, dbNameString, chtrList);
							sceneCountWorld = sceneCountersWorld(dbNameString, 0, "read");
							break;
						}
					}
					//Load Scene. Character load(s) handled here, rest handled in Scene.cpp
					else if (inputSCE == "load") {
						Character tempChtrScene;
						std::vector <std::string> chtrTokens;
						int tempID = 0;
						std::string tempCharacter;
						chtrList = "";
						//std::stringstream myStream;
						selectFrom("SCENE_NUM,SCENE_NAME,CHARACTERS,NUM_CRCTRS", "SCENE", sceneCountWorld, 0, dbNameString, true);
						int idLoadChoice = tempSceneCount = inputInt();
						if (idLoadChoice < 0 || idLoadChoice > sceneCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						//LOAD CHTRS//
						//External from dbInteract.cpp. Returns from callback used in selectFrom if printOnly = false
						extern std::vector <std::string> returnCount;
						std::string choiceString = std::to_string(idLoadChoice);
						//Select Return
						//selectFrom("CHARACTERS", "SCENE", 1, idLoadChoice, dbNameString, false);
						selectFromWhere("CHARACTERS", "SCENE", "SCENE_NUM", choiceString, dbNameString, false);
						std::cout << returnCount.at(0) << std::endl;
						std::string tempChtrsFromReturn = chtrList = returnCount.at(0);
						returnCount.clear();
						//Tokenize character return list
						boost::char_separator<char> sep("N");
						boost::tokenizer<boost::char_separator<char>> tokens(tempChtrsFromReturn, sep);
						//Extract CHARACTES from db, and LOAD to tempchtr.
						for (const auto& t : tokens) {
							//std::cout << t << std::endl;
							//chtrTokens.push_back(t);
							
							//std::stringstream myStream(t);
							//myStream >> tempID;
							//myStream >> tempCharacter;
							//tempID -= 1;

							selectFromWhere("ID,NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", "ID", t, dbNameString, false);
							tempChtrScene.setCharacterFromDb(returnCount);
							tempScene.setCharacters(tempChtrScene);
							returnCount.clear();
							
							//selectFrom("ID,NAME,AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, tempID, dbNameString, false);							tempChtrScene.setCharacterFromDb(returnCount);
							//tempScene.setCharacters(tempChtrScene);
							//returnCount.clear();
						}
						//LOAD REST//
						selectFromWhere("LOCATION,TIME_DATE,SCENE_NAME,GEN_DSCRPT,NOTES,SCENE_NUM,NUM_CRCTRS,EXISTS_BOOL","SCENE","SCENE_NUM",choiceString,dbNameString,false);
						tempScene.setSceneFromDb(returnCount);
						returnCount.clear();
						fromLoad = true;
					}
					//Delete scene
					else if (inputSCE == "del") {
						selectFrom("ID,SCENE_NAME", "SCENE", sceneCountWorld, 0, dbNameString, true);
						std::cout << "Choose by id. -1 to cancel delete process: " << std::endl;
						int delChoice = inputInt();
						if (delChoice < 0 || delChoice > sceneCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
							std::cout << delChoice;
							removeIDFromTable("SCENE", delChoice, dbNameString);
							//Prevent counter from getting out of sync
							if (delChoice == sceneCountWorld) {
								sceneCountWorld -= 1;
								sceneCountersWorld(dbNameString,sceneCountWorld, "write");
							}
					}
				}
			}
			//////////////////////
			//MAIN CHAPTER LOOP//
			////////////////////
			else if (input == "chapter") {
				//exit condition
				int exitChapter = 1;
				//Character class temp
				Chapter tempChapt;
				bool fromLoad = false;
				int tempChaptCount = 0;
				//Read write scene lists
				std::string sceneList = "";
				std::vector <int> scenelistForRemovalPurposes;
				int numScenes = 0;
		        //INPUT//
				while (exitChapter) {
					std::cout << "(n)ame, (d)escribe, Assign (num)ber, (v)eiw, (notes), (add scene), "
						"(save), (load), (rem)ove (scene),(del)ete (exit)" << std::endl;
					std::string inputCHPT;
					std::getline(std::cin, inputCHPT);
					//Exit Condition
					if (inputCHPT == "exit") {
						exitChapter = 0;
						break;
					}
					//Name chapter
					else if (inputCHPT == "n") {
						tempChapt.setName(inputChtrChoice("Name the chapter?"));
					}
					//Describe chapter
					else if (inputCHPT == "d") {
						tempChapt.setDescription(inputChtrChoice("Describe the chapter: "));
					}
					//Notes on chapter
					else if (inputCHPT == "notes") {
						tempChapt.setNotes(inputChtrChoice("Any notes to make about this chapter? "));
					}
					//Assign a number to chapter. PROBABLY AUTOMATE THIS
					else if (inputCHPT == "num") {
						std::cout << "Please assign a chapter number: ";
						tempChapt.setChapterNumber(inputInt());
					}
					//View selected chapter
					else if (inputCHPT == "v") {
						printChapterInfo(tempChapt);
					}
					//Add scene to chapter
					else if (inputCHPT == "add scene") {
						Scene tempScene;
						std::cout << "Select Scene Number from list, or -1 to cancel: ";
						selectFrom("SCENE_NAME, SCENE_NUM", "SCENE", sceneCountWorld, 0, dbNameString, true);
						//Select Scene by ID number
						int idLoadChoice = inputInt();
						if (idLoadChoice < 0 || idLoadChoice > sceneCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::string choiceString = std::to_string(idLoadChoice);
						extern std::vector <std::string> returnCount;
						selectFromWhere("LOCATION, TIME_DATE, SCENE_NAME, GEN_DSCRPT, NOTES, SCENE_NUM, EXISTS_BOOL", "SCENE", "SCENE_NUM", choiceString, dbNameString, false);
						//Clear and set
						tempScene.setSceneFromDb(returnCount);
						returnCount.clear();
						tempChapt.setScenes(tempScene);
						//Record what has been added by sceneNum
						scenelistForRemovalPurposes.push_back(idLoadChoice);
						std::string idToAdd = std::to_string(idLoadChoice) + "N";
						sceneList += idToAdd;
						std::cout << sceneList << std::endl;
						try {
							numScenes = returnNumberScenesChapter(chaptCountWorld, dbNameString);
							numScenes += 1;
						}
						catch (std::out_of_range e) {
							std::cout << "NOT YET USABLE. NEEDS SCENE SAVED TO TABLE." << std::endl;
						}
					}
					//Remove scene
					else if (inputCHPT == "rem scene") {
						//Remove from load/db
						if (fromLoad == true) {
							chaptCountWorld = tempChaptCount;
							///Select scene for removal, and convert for removal string
							std::string chaptStringCount = std::to_string(chaptCountWorld);
							selectFromWhere("SCENES", "CHAPTER","CHPTR_NUM", chaptStringCount, dbNameString, true);
							std::cout << "Select Scene ID from list, or -1 to cancel: ";
										
							int idLoadChoice = inputInt();
							if (idLoadChoice < 0 || idLoadChoice > sceneCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							std::string quickConvert = std::to_string(idLoadChoice);
							std::string quickConvertNumScenes = "";
							quickConvert += "N";
							//Remove from string and update db
							boost::erase_all(sceneList, quickConvert);
							updateDb("CHAPTER", "SCENES", sceneList, chaptCountWorld, dbNameString);
							//Decrement num chtrs
							numScenes = returnNumberScenesChapter(chaptCountWorld, dbNameString);
							numScenes -= 1;
							quickConvertNumScenes = std::to_string(numScenes);
							updateDb("CHAPTER", "NUM_SCENES", quickConvertNumScenes, chaptCountWorld, dbNameString);
							//Reset scene counter (Possibly needless)
							//chaptCountWorld = chapterCountersWorld(dbNameString, 0, "read");
							break;
						}
						//remove from new pre - saved scene
						else {
							//Get number of scenes
							//tempChapt.getNumberOfScenes(); <- why not this?
							int rmLim = tempChapt.getSceneList().size();
							int removeThisEle = 0;
							//Display
							for (int rmc = 0; rmc < rmLim; rmc++) {
								std::cout << rmc << " ";
								std::cout << tempChapt.getSceneList().at(rmc).getName() << "  ";
							}
							//Choose for dissmissal
							std::cout << "Select Scene ID from list, or -1 to cancel: ";
							removeThisEle = inputInt();
							if (removeThisEle < 0 || removeThisEle > chaptCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							int realPosition = scenelistForRemovalPurposes.at(removeThisEle);
							sceneList = removeFromStringList(realPosition, sceneList);
							tempChapt.removeSceneFromList(removeThisEle);
							std::cout << std::endl;
						}
					}
					//Save chapter
					else if (inputCHPT == "save") {
						if (fromLoad == true) {
							chaptCountWorld = tempChaptCount;
						}
						//Check existence of scene
						if (tempChapt.getExistence() == false) {
							tempChapt.setExistence();
							chaptCountWorld += 1;
							insertChapter(tempChapt, chaptCountWorld, 0, dbNameString, sceneList);
							chapterCountersWorld(dbNameString, chaptCountWorld, "write");
							break; 
						}
						//If the chapter exists, then it is simply updated. Reset chaCountWorld after.
						else if (tempChapt.getExistence() == true) {
							insertChapter(tempChapt, chaptCountWorld, 1, dbNameString, sceneList);;
							chaptCountWorld = chapterCountersWorld(dbNameString, 0, "read");
							break;
						}
					}
					//Load chapter
					else if (inputCHPT == "load") {
						//Clear and ready temps
						Scene tempSceneChapt;
						std::vector <std::string> sceneTokens;
						int tempID = 0;
						std::string tempScene;
						sceneList = "";
						//Select chapter
						selectFrom("CHPTR_NAME,CHPTR_NUM,NUM_SCENES", "CHAPTER", chaptCountWorld, 0, dbNameString, true);
						int idLoadChoice = tempChaptCount = inputInt();
						if (idLoadChoice < 0 || idLoadChoice > chaptCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::string choiceString = std::to_string(idLoadChoice);
						//LOAD SCENES//
						//External from dbInteract.cpp. Returns from callback used in selectFrom if printOnly = false
						extern std::vector <std::string> returnCount;
						//Select Return
						selectFromWhere("SCENES", "CHAPTER", "CHPTR_NUM", choiceString, dbNameString, false);
						std::cout << returnCount.at(0) << std::endl;
						std::string tempScenesFromReturn = sceneList = returnCount.at(0);
						returnCount.clear();
						//Tokenize scene return list
						boost::char_separator<char> sep("N");
						boost::tokenizer<boost::char_separator<char>> tokens(tempScenesFromReturn, sep);
						//Extract SCENES from db, and LOAD to tempSCENE.
						for (const auto& t : tokens) {
							//std::stringstream myStream(t);
							//myStream >> tempID;
							//tempID -= 1;
							selectFromWhere("LOCATION, TIME_DATE, SCENE_NAME, GEN_DSCRPT, NOTES, SCENE_NUM, NUM_CRCTRS", "SCENE","SCENE_NUM", t, dbNameString, false);
							tempSceneChapt.setSceneFromDb(returnCount);
							tempChapt.setScenes(tempSceneChapt);
							returnCount.clear();
						}
						//LOAD REST//
						selectFromWhere("CHPTR_NUM, CHPTR_NAME, NUM_SCENES, GEN_DSCRPT, NOTES, EXISTS_BOOL", "CHAPTER","CHPTR_NUM", choiceString,dbNameString, false);
						tempChapt.setChapterFromDb(returnCount);
						returnCount.clear();
						fromLoad = true;
					}
					//Delete chapter
					else if (inputCHPT == "del") {
						selectFrom("ID,CHPTR_NAME,CHPTR_NUM", "CHAPTER", chaptCountWorld, 0, dbNameString, true);
						std::cout << "Choose by id. -1 to cancel delete process: " << std::endl;
						int delChoice = inputInt();
						if (delChoice < 0 || delChoice > chaptCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::cout << delChoice;
						removeIDFromTable("CHAPTER", delChoice, dbNameString);
						//Prevent counter from getting out of sync
						if (delChoice == chaptCountWorld) {
							chaptCountWorld -= 1;
							chapterCountersWorld(dbNameString, chaptCountWorld, "write");
						}
					}
				}
			}
			//////////////////
			//Main NGI loop//
			////////////////
			else if (input == "ngi") {
				//exit condition
				int exitNGI = 1;
				//Character class temp
				NarativeGeneralInfo tempNGI;
				bool fromLoad = false;
				int tempNGICount = 0;
				std::string chapterList = "";
				std::vector <int> chapterlistForRemovalPurposes;
				int numChapters = 0;
				while (exitNGI) {
					std::cout << "(t)itle, (s)etting, (g)enre, (d)escription"
						"(v)iew, (notes), (add chapter), (rem)ove chapter,"
						"(save),(load),(del)ete, (exit)" << std::endl;
					std::string inputNGI;
					std::getline(std::cin, inputNGI);
					//Exit Condition
					if (inputNGI == "exit") {
						exitNGI= 0;
						break;
					}
					else if (inputNGI == "t") {
						tempNGI.setTitle(inputChtrChoice("Tack on a title to the tale? "));
					}
					else if (inputNGI == "s") {
						tempNGI.setSetting(inputChtrChoice("Set Setting: "));
					}
					else if (inputNGI == "g") {
						tempNGI.setGenre(inputChtrChoice("Genre: "));
					}
					else if (inputNGI == "d") {
						tempNGI.setDescription(inputChtrChoice("Describe the narrative? "));
					}
					else if (inputNGI == "notes") {
						tempNGI.setNotes(inputChtrChoice("Any notes about the story?"));
					}
					else if (inputNGI == "v") {
						printNarativeGeneralInfo(tempNGI);
					}
					else if (inputNGI == "add chapter") {
						Chapter tempChapter;
						std::cout << "Select Chapter Number from list, or -1 to cancel: ";
						selectFrom("CHPTR_NAME, CHPTR_NUM", "CHAPTER", chaptCountWorld, 0, dbNameString, true);
						//Select chapter by ID number
						int idLoadChoice = inputInt();
						if (idLoadChoice < 0 || idLoadChoice > chaptCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::string choiceString = std::to_string(idLoadChoice);
						extern std::vector <std::string> returnCount;
						//CHPTR_NUM, CHPTR_NAME, NUM_SCENES, GEN_DSCRPT, NOTES, EXISTS_BOOL
						selectFromWhere("CHPTR_NUM, CHPTR_NAME, NUM_SCENES, GEN_DSCRPT, NOTES, EXISTS_BOOL", "CHAPTER", "CHPTR_NUM", choiceString, dbNameString, false);
						//Destructor
						tempChapter.setChapterFromDb(returnCount);
						
						//Clear return
						returnCount.clear();
						tempNGI.setChapter(tempChapter);
						chapterlistForRemovalPurposes.push_back(idLoadChoice);
						std::string idToAdd = std::to_string(idLoadChoice) + "N";
						chapterList += idToAdd;
						std::cout << chapterList << std::endl;
						//Remove when ready to use
						try {
							numChapters = returnNumberChaptersNGI(ngiCountWorld, dbNameString);
							numChapters += 1;
						}
						catch (std::out_of_range e) {
							std::cout << "NOT USABLE YET. NEEDS SAVED NGI TABLE." << std::endl;
						}
					}
					else if (inputNGI == "rem chapter") {
						//Remove from load/db
						if (fromLoad == true) {
							ngiCountWorld = tempNGICount;
							///Select scene for removal, and convert for removal string
							std::string ngiStringCount = std::to_string(ngiCountWorld);
							selectFromWhere("CHAPTERS", "NGI", "ID", ngiStringCount, dbNameString, true);
							std::cout << "Select chapter ID from list, or -1 to cancel: ";
							//Select chapter to remove
							int idLoadChoice = inputInt();
							if (idLoadChoice < 0 || idLoadChoice > chaptCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							std::string quickConvert = std::to_string(idLoadChoice);
							std::string quickConvertNumChapters = "";
							quickConvert += "N";
							//Remove from string and update db
							boost::erase_all(chapterList, quickConvert);
							updateDb("NGI", "CHAPTERS", chapterList, ngiCountWorld, dbNameString);
							//Decrement num chtrs
							numChapters = returnNumberChaptersNGI(ngiCountWorld, dbNameString);
							numChapters -= 1;
							quickConvertNumChapters = std::to_string(numChapters);
							updateDb("NGI", "NUM_CHAPTERS", quickConvertNumChapters, ngiCountWorld, dbNameString);
							break;
						}
						//remove from new pre - saved scene
						else {
							//Get number of scenes
							//tempChapt.getNumberOfScenes(); <- why not this?
							int rmLim = tempNGI.getChapters().size();
							int removeThisEle = 0;
							//Display
							for (int rmc = 0; rmc < rmLim; rmc++) {
								std::cout << rmc << " ";
								std::cout << tempNGI.getChapters().at(rmc).getName() << "  ";
							}
							//Choose for dissmissal
							std::cout << "Select Scene ID from list, or -1 to cancel: ";
							removeThisEle = inputInt();
							if (removeThisEle < 0 || removeThisEle > ngiCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							int realPosition = chapterlistForRemovalPurposes.at(removeThisEle);
							chapterList = removeFromStringList(realPosition, chapterList);
							tempNGI.removeChapterFromList(removeThisEle);
							std::cout << std::endl;
						}
					}
					else if (inputNGI == "save") {
						if (fromLoad == true) {
							ngiCountWorld = tempNGICount;
						}
						//Check existence of scene
						if (tempNGI.getExistence() == false) {
							tempNGI.setExistence();
							ngiCountWorld += 1;
							insertNGI(tempNGI, ngiCountWorld, 0, dbNameString, chapterList);
							ngiCountersWorld(dbNameString, ngiCountWorld, "write");
							break;
						}
						//If the chapter exists, then it is simply updated. Reset chaCountWorld after.
						else if (tempNGI.getExistence() == true) {
							insertNGI(tempNGI, ngiCountWorld, 1, dbNameString, chapterList);
							ngiCountWorld = ngiCountersWorld(dbNameString, 0, "read");
							break;
						}
					}
					else if (inputNGI == "load") {
						//Clear and ready temps
						Chapter tempChaptNGI;
						std::vector <std::string> chapterTokens;
						int tempID = 0;
						std::string tempChapter;
						chapterList = "";
						//Select ngi
						selectFrom("TITLE, ID, NUM_CHAPTERS, GEN_DSCRPT", "NGI", ngiCountWorld, 0, dbNameString, true);
						int idLoadChoice = tempNGICount = inputInt();
						if (idLoadChoice < 0 || idLoadChoice > ngiCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::string choiceString = std::to_string(idLoadChoice);
						//LOAD SCENES//
						//External from dbInteract.cpp. Returns from callback used in selectFrom if printOnly = false
						extern std::vector <std::string> returnCount;
						//Select Return
						selectFromWhere("CHAPTERS", "NGI", "ID", choiceString, dbNameString, false);
						std::cout << returnCount.at(0) << std::endl;
						std::string tempChaptersFromReturn = chapterList = returnCount.at(0);
						returnCount.clear();
						//Tokenize scene return list
						boost::char_separator<char> sep("N");
						boost::tokenizer<boost::char_separator<char>> tokens(tempChaptersFromReturn, sep);
						//Extract CHAPTERS from db, and LOAD to tempSCENE.
						for (const auto& t : tokens) {
							selectFromWhere("CHPTR_NUM, CHPTR_NAME, NUM_SCENES, GEN_DSCRPT, NOTES, EXISTS_BOOL", "CHAPTER", "CHPTR_NUM", t, dbNameString, false);
							tempChaptNGI.setChapterFromDb(returnCount);
							tempNGI.setChapter(tempChaptNGI);
							returnCount.clear();
						}
						//LOAD REST//
						selectFromWhere("TITLE, SETTING, GENRE, GEN_DSCRPT, NUM_CHAPTERS, NOTES, EXISTS_BOOL", "NGI", "ID", choiceString, dbNameString, false);
						tempNGI.setNGIFromDb(returnCount); //setChapterFromDb(returnCount);
						returnCount.clear();
						fromLoad = true;
					}
					else if (inputNGI == "del") {
						selectFrom("ID, TITLE, GEN_DSCRPT", "NGI",ngiCountWorld, 0, dbNameString, true);
						std::cout << "Choose by id. -1 to cancel delete process: " << std::endl;
						int delChoice = inputInt();
						if (delChoice < 0 || delChoice > ngiCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						std::cout << delChoice;
						removeIDFromTable("NGI", delChoice, dbNameString);
						//Prevent counter from getting out of sync
						if (delChoice == ngiCountWorld) {
							ngiCountWorld -= 1;
							ngiCountersWorld(dbNameString, ngiCountWorld, "write");
						}
					}
				}
			}
			else if (input == "World") {
				int exitWorld = 1;
				//Character class temp
				World tempWorld;
				
				std::string ngiList = "";
				std::vector <int> ngilistForRemovalPurposes;
				while (exitWorld) {
					std::string inputWRLD;
					std::getline(std::cin, inputWRLD);
					//Load on entry?
					//Only really need to save to it, as only one world per file.
					//Just need to add and remove NGI. Actually, that is achieved withing the creation and deletion of NGI, so not necesarry.
					//Only need to view ngi's
				
					//Exit Condition. 
					if (inputWRLD == "exit") {
						exitWorld = 0;
						break;
					}
					else if (inputWRLD == "n") {
						tempWorld.setName(inputChtrChoice("Name of series or narative universe. "));
					}
					else if (inputWRLD == "d") {
						tempWorld.setDescription(inputChtrChoice("Describe the universe your strories take place in: "));
					}
					else if (inputWRLD == "notes") {
						tempWorld.setNotes(inputChtrChoice("Notes on the universe your stories inhabit. "));
					}
					else if (inputWRLD == "v") {
						queryAllFieldsTable("WORLD", dbNameString);
						std::cout << "Include in this world are the following narratives: " << std::endl;
						queryAllFieldsTable("NGI", dbNameString);
					}
					else if (inputWRLD == "save") {
						insertWorld(tempWorld, dbNameString, ngiList);
						break;
					}
					else if (inputWRLD == "add ngi") {///NOT NEEDED
						//Should be Automatic, see below.
					}
					else if (inputWRLD == "rem ngi") {///NOT NEEDED
						//No need? As ngi is the last level of class that has multiplicity in this system, 
						//within the confines of each seperate world/file. 
					}
				
				}

			}
		}
	}
	//TEMPORARY EARLY TESTING. WILL BE REMOVED FOLLOWING IMPROVEMENTS
	if (visTest) {
		//Create Characters
		Character c1;
		Character c2;
		Character c3; //("Dr.Bamboo", 77, "A nice old doctor, retired now. Enjoys tending to his garden.",
			//"Execution of ingrates", "Man");
		//std::string sql(selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, 2));
		//exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
		selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, 2, dbNameString, true);
		//c3.setCharacterFromDb(returnThis);
		//displayAndError(exit);
		Character Tom("Tom", 44, "Beer beast", "Create new beery world order", "bloke");
		Character a1("Mick", 55, "Nice enough, but... ", "Stealing and love", "Chromeman");
		Character a2("Nan", 700, "An old nan", "Getting blood out of the carpet", "Serpent");
		
		//Set Some Names and ages
		c1.setName("Mark");
		c1.setCharacterAge(6);
		c1.setGender("Boy");
		c1.setMotive("Chrisps");
		c2.setName("Babdoo");
		c2.setCharacterAge(13);
		c2.setGender("Female");
		c2.setDescription("Teenage girl");

		//Evidence 'notes' working.
		//a1.setNotes("Always, he gets into the fighting on tarmac over beer.\n"
		//	"'Why are you like this?' is the sort of thing his wife asks.\n"
		//	"'My Dyspraxia drives me to it, NOW LEAVE ME!' would be a typical reply.");

		/*std::string sql(insertCharacter(c1,1));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
					 sql =(insertCharacter(c2, 2));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(c3, 3));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(Tom, 4));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(a1, 5));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(a2, 6));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		*/
		//std::string sql22(insertCharacter(a1, 5));
		//sqlite3_exec(db, sql22.c_str(), callback, 0, &errMsg);
		//sqlite3_close(db);
		//END DB STUFF

		//Creating scenes (Uh oh!)
		Scene sceneOne;
		Scene sceneTwo("Nan's car", "A bit later", "Escape.", "Dr.Bamboo legs it", 2);
		Scene sceneThree("Nan's Garden", "Thursday", "Conclusions in RED!", "Only one person died", 3);
		Scene sceneFour("Hell", "No!", "Dr Dr Dr", "dsgGGGGGfyes", 4);
		Scene sceneFive("Nan's House", "Friday", "End now", "Nan is watching TV, in her chair", 5);
		sceneFive.setCharacters(a2);
		sceneFive.setCharacters(c1);
		sceneFive.setNotes("Nan is pleased with her week. Everything went as she had hoped, and now the one show is on.");
		sceneThree.setNotes("This is not the end.");
		sceneOne.setLocation("Nan's House");
		sceneOne.setName("Dr. Bamboo kills two people.");
		sceneOne.setTimeAndOrDate("A Wednesday");
		sceneOne.setSceneNumber(1);


		//Link characters to the scenes
		sceneOne.setCharacters(c1);
		sceneOne.setCharacters(c2);
		sceneOne.setCharacters(c3);
		sceneOne.setCharacters(Tom);
		sceneOne.setCharacters(a1);
		sceneTwo.setCharacters(c3);
		sceneThree.setCharacters(a2);
		sceneThree.setCharacters(c1);
		sceneThree.setCharacters(c2);
		sceneThree.setCharacters(Tom);

		//Chapters 
		Chapter chap1(1, "Etchings of FEAR!");
		Chapter chap2(2, "Epilogue... OF FEAR!");
		chap1.setScenes(sceneOne);
		chap1.setScenes(sceneTwo);
		chap1.setScenes(sceneThree);
		chap2.setScenes(sceneFour);
		chap2.setScenes(sceneFive);

		//Set Narrative General Info
		NarativeGeneralInfo ngi1;
		NarativeGeneralInfo ngi2;
		ngi1.setTitle("Bad day at Nan's");
		ngi1.setSetting("Nan's house, car, and garden");
		ngi1.setGenre("Romance");
		ngi1.setDescription("Book about a murder spree by a bad Dr.");

		//Include chapters
		ngi1.setChapter(chap1);
		ngi1.setChapter(chap2);

		//Display Narrative info, Chapters, Scenes, and a character.
		printNarativeGeneralInfo(ngi1);

		printChapterInfo(chap1);

		printSceneInfo(sceneOne, false);
		printSceneInfo(sceneTwo, true);
		printSceneInfo(sceneThree, false);

		printChapterInfo(chap2);
		printSceneInfo(sceneFour, false);
		printSceneInfo(sceneFive, true);

		printCharacterInfo(c3);
		//Example of value passing through classes
		printNarativeGeneralInfo(ngi2);

	}
	sqlite3_close(db);
return 0;
}
//Return from database//SOON OBSOLETE
int callback(void* data, int argc, char** argv, char** azColName) { 
	
	int i;
	std::string toReturn;
	fprintf(stderr, "%s: ", (const char*)data);
	chaCount += 1;
	idCount += 1;
	//Recieve data
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		//Return to global
		if (argv[i]) {
			returnThis.push_back(argv[i]);	
		}
		identifyThis.push_back(azColName[i]);
	}

	printf("\n");
	
	return 0; }

void displayAndError(int exit, bool display)
{
	if (display == true) {
		for (size_t retList = 0; retList < returnThis.size(); retList++) {
			std::cout << "Output from db= " << returnThis.at(retList) <<
				" Identity= " << identifyThis.at(retList) << std::endl;
		}
	}
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
	}

}

std::string removeFromStringList(int idToRemove, std::string stringlist)
{
	std::string quickConvert; 
	quickConvert = std::to_string(idToRemove);
	//std::string quickConvertNumScenes = "";
	quickConvert += "N";
	//Remove from string and update db
	boost::erase_all(stringlist, quickConvert);
	return stringlist;
}

//Safley input integer, and parse.
int inputInt()
{
	std::string input = "";
	int id;
	while (true) {
		std::cout << "Please enter a valid number: ";
		std::getline(std::cin, input);
		if (input == "exit") {
			id = -1;
			break;
		}
		// This converts from string to int.
		std::stringstream myStream(input);
		if (myStream >> id)
			break;
		std::cout << "Invalid number, please try again" << std::endl;
	}
	return id;
}

//Return a string. Helper. Mostly for making choices.
std::string inputChtrChoice(std::string message)
{	
	std::string choice;
	std::cout << message;
	std::getline(std::cin, choice);
	boost::replace_all(choice, "'", "`");
	return choice; 
}
//Print scenes
void printSceneInfo(Scene scene, bool charInfoOn)
{
	//General information about the scene, from Scene.
	std::cout <<
		"Scene: " << scene.getSceneNumber() << std::endl <<
		"Location: " << scene.getLocation() << std::endl <<
		"Number of Characters: " << scene.getNumberOfCharacters() << std::endl <<
		"Name of scene: " << scene.getName() << std::endl <<
		"Time/date/etc: " << scene.getTimeAndOrDate() << std::endl <<
		"What happened?: " << scene.getDescription() << std::endl <<
		"Notes: " << scene.getNotes() << std::endl << std::endl;
	//Characters displayed following being Linked to a scene
	if (charInfoOn == true) {
		std::cout << "Characters who apeer in this scene:\n\n";
		int numCharacters = scene.getCharacterList().size();
		if (numCharacters != 0) {
			for (int i = 0; i < numCharacters; i++) {
				std::cout <<
					"Name of Character " << i + 1 << ": " <<
					scene.getCharacterList().at(i).getName() <<
					" Aged: " << scene.getCharacterList().at(i).getCharacterAge() << std::endl <<
					"\nWho can be described as: " << scene.getCharacterList().at(i).getDescription() << std::endl <<
					"Who's motive seems to be: " << scene.getCharacterList().at(i).getMotive() << std::endl <<
					scene.getCharacterList().at(i).getName() << " is a " << scene.getCharacterList().at(i).getGender() <<
					std::endl << std::endl;
			}
		}
		else {
			std::cout << "No characters in this Scene." << std::endl << std::endl;
		} 
	}
	else { /*nothing*/ }
}
//Print Characters
void printCharacterInfo(Character character)
{
	std::cout << character.getName() << "'s details." << std::endl <<
		"Age: " << character.getCharacterAge() << std::endl <<
		"Description:  " << character.getDescription() << std::endl <<
		"Motive: " << character.getMotive() << std::endl <<
		"Gender: " << character.getGender() << std::endl << 
		"Notes: " << character.getNotes() << std::endl << std::endl;
}
//Print Chapters
void printChapterInfo(Chapter chapter)
{   //Number of scenes
	std::cout << "Chapter No: " << chapter.getChapterNumber() << std::endl;
	std::cout << "Chapter Name: " << chapter.getName() << std::endl;
	std::cout << "Scenes in Chapter: " << chapter.getNumberOfScenes() << std::endl;
	std::cout << "Chapter Description: " << chapter.getDescription() << std::endl;
	std::cout << "Chapter Notes: " << chapter.getNotes() << std::endl;
	int chapSize = chapter.getSceneList().size();
	if (chapSize != 0) {
		for (int i = 0; i < chapSize; i++) {
			std::cout << i + 1 << ": ";
			std::cout << chapter.getSceneList().at(i).getName() << std::endl;
		}
		std::cout << std::endl;
		//Access first character name, from first scene in Chapter.
		if (chapter.getSceneList().at(0).getCharacterList().size() != 0) {
			std::cout << "The name of the first character from the first scene is "
				<< chapter.getSceneList().at(0).getCharacterList().at(0).getName() <<
				", taken from character class via scene class." << std::endl;
		}
		else {/*Do nothing*/ }
	}
	else { std::cout << "No Scenes to display"; }
	std::cout << std::endl;
}
//Print NGI
void printNarativeGeneralInfo(NarativeGeneralInfo ngi)
{
	std::cout << "Title: ";
	std::cout << ngi.getTitle() << std::endl;
	std::cout << "Setting: ";
	std::cout << ngi.getSetting() << std::endl;
	std::cout << "Genre: ";
	std::cout << ngi.getGenre() << std::endl;
	std::cout << "Description: ";
	std::cout << ngi.getDescription() << std::endl;
	std::cout << "Notes: ";
	std::cout << ngi.getNotes() << std::endl;
	std::cout << "Number of Chapters: ";
	std::cout << ngi.getNumberOfChapters();
	std::cout << std::endl << std::endl;
	//Display Chapter Names and Numbers
	int narSize = ngi.getChapters().size();
	if (narSize != 0) {
		for (int k = 0; k < narSize; k++) {
			if (ngi.getChapters().at(k).getName() != "") {
				std::cout << "Chapter ";
				std::cout << ngi.getChapters().at(k).getChapterNumber() << " :";
				std::cout << ngi.getChapters().at(k).getName() << std::endl;
			}
			else{/*Do Nothing*/ }
		}
		std::cout << std::endl;
	}
	else { std::cout << "No chapters to display" << std::endl; }
}

