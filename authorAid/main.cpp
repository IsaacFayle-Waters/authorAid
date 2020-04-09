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
//TODO DEBUG Update scene does not work after loading scene. Possibly same problem in insert chtr. 

//NOTE! POSSIBLE RE-DESIGN?: INCLUDE Db INTERACTION IN CLASSES INSTEAD? MIGHT MAKE THINGS LESS CONVOLOUTED. 

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

int inputInt();
std::string inputChtrChoice(std::string message);
//Strings
std::string data("CALLBACK FUNCTION");
char dbNameString[] = "counterTest.db";
char dbNameString0[] = "exampleUpdateTest.db";
char dbNameString2[] = "example.db";

//Return strings from db (identifyThis possibly redundant)
std::vector <std::string> returnThis;
std::vector <std::string> identifyThis;
std::vector <int> deletedIDs;

//GLOBAL CHARACTER COUNT, CURRENTLY DRAWN FROM CALLBACK FUNCTION, BUT MUST CHANGE TO DB.
int chaCount = 0;//OBSOLETE
int chaCountWorld = 0;
int sceneCountWorld = 0;

//Used in a display function. Possibly redundent
int idCount = 0;
//save error messages. Possibly only used in test functions.
char* errMsg = 0;
//Testing from manually set values on/off
int visTest = 0;
int updateTest = 1;
int testUI = 1;

int main(int argc, char** argv) {
	//Read Counters from World Table
	//countersWorld(dbNameString, 15, "write");
	//sceneCountersWorld(dbNameString, 0, "write");
	chaCountWorld = countersWorld(dbNameString, 0, "read");
	sceneCountWorld = sceneCountersWorld(dbNameString, 0, "read");
	
	//updateDb("SCENE", "NUM_CRCTRS", "1", 1, dbNameString);
    //Create db instance
	sqlite3 *db;
	//exit deals with sqlite read and write	
	int exit = 0;
	
	/*std::string testCL = "3,4,8";
	Scene test;
	insertScene(test, 1, 0, dbNameString, testCL);
	insertScene(test, 1, 1, dbNameString, testCL);*/

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
	
	//QUERIES AND TABLE SET UP, TEMPORARY UNTIL SYSTEM MORE ROBUST
	//tableBaseCreate(dbNameString);
	//std::string query("UPDATE SCENE SET CHARACTERS = '15N8N14N' WHERE ID=1;");
	//std::string query("ALTER TABLE SCENE ADD COLUMN EXISTS_BOOL INT (0);");
	//exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	//displayAndError(exit,false);
	//std::string query(removeIDFromTable(5));
	//exit = sqlite3_exec(db, create.c_str(), callback, (void*)data.c_str(), NULL);

	//Visual tests
	
	queryAllFieldsTable("WORLD",dbNameString);
	queryAllFieldsTable("SCENE", dbNameString);
	queryAllFieldsTable("CHARACTER", dbNameString);
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
			std::cout << "Enter an option: (view chtr), (insert chtr), (scene), (exit). " <<std::endl;
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
						tempChtr.~Character();
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
						tempChtr.~Character();
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
				std::string chtrList = "";
				int numCharacters = 0;
				int removalID = 0;
				while (exitScene) {
					std::cout << "Choose an option: (l)ocation, (t)ime, (n)ame,(d)escription,(notes)"
						"(add chtr), (rem)ove (chtr),(v)iew, (save), (load),(exit). " << std::endl;
					std::string inputSCE;
					std::getline(std::cin, inputSCE);

					//Exit Condition
					if (inputSCE == "exit") {
						exitScene = 0;
						tempScene.~Scene();
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
					else if (inputSCE == "add chtr") {
						Character tempChtr;
						tempChtr.setRemovalID(removalID);
						removalID += 1;
						std::cout << "Select Character ID from list, or -1 to cancel: ";
						selectFrom("ID,NAME", "CHARACTER", chaCountWorld, 0, dbNameString, true);
						//Select Character by ID number
						int idLoadChoice =  inputInt() - 1;
						if (idLoadChoice < 0 || idLoadChoice > chaCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						extern std::vector <std::string> returnCount;
						//Select Return
						selectFrom("ID,NAME,AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, idLoadChoice, dbNameString, false);
						//Destructor
						tempChtr.~Character();
						//Return from selectFrom, adds details to tempchar.
						tempChtr.setCharacterFromDb(returnCount);
						//Clear return
						returnCount.clear();
						tempScene.setCharacters(tempChtr);
						//String representation						
						std::string idToAdd = std::to_string(idLoadChoice + 1) + "N";
						chtrList += idToAdd;
						std::cout << chtrList << std::endl;
						//POSSIBLY OBSOLETE, AS setCharacters automatically increments this (?)
						numCharacters = returnNumberChtrsScene(sceneCountWorld, dbNameString);
						numCharacters += 1;
					}
					else if (inputSCE == "rem chtr") {
						if (fromLoad == true) {
							sceneCountWorld = tempSceneCount + 1;

							selectFrom("CHARACTERS", "SCENE", 1, sceneCountWorld - 1, dbNameString, true);
							std::cout << "Select Character ID from list, or -1 to cancel: ";
							/////HMMMMM!!!!!!!				

							//std::cout << returnCount.at(0);
							int idLoadChoice = inputInt();
							if (idLoadChoice < 0 || idLoadChoice > chaCountWorld) {
								std::cout << "removal Cancelled" << std::endl;
								break;
							}
							//SHOULD BE IN SAVE?
							std::string quickConvert = std::to_string(idLoadChoice);
							std::string quickConvertNumChtrs = "";
							quickConvert += "N";
							boost::erase_all(chtrList, quickConvert);
							updateDb("SCENE", "CHARACTERS", chtrList, sceneCountWorld, dbNameString);
							//Decrement num chtrs
							int numCharacters = returnNumberChtrsScene(sceneCountWorld, dbNameString);
							numCharacters -= 1;
							quickConvertNumChtrs = std::to_string(numCharacters);
							updateDb("SCENE", "NUM_CRCTRS", quickConvertNumChtrs, sceneCountWorld, dbNameString);
							sceneCountWorld = sceneCountersWorld(dbNameString, 0, "read");
							std::cout << std::endl;
							break;
						}
						else {
							int rmLim = tempScene.getCharacterList().size();
							int removeThisEle = 0;
							for (int rmc = 0; rmc < rmLim; rmc++) {
								std::cout << rmc << " ";
								std::cout << tempScene.getCharacterList().at(rmc).getName() << "  ";
							}
							std::cout << "Select Character ID from list, or -1 to cancel: ";
							removeThisEle = inputInt();
							tempScene.removeCharacterFromList(removeThisEle);
							numCharacters -= 1;
							//break;
						}
					}
					else if (inputSCE == "v") {
						printSceneInfo(tempScene,true);
					}
					else if (inputSCE == "save") {
						//Check to see if Character details were loaded, if so, deal with ID position from load
						if (fromLoad == true) {
							sceneCountWorld = tempSceneCount + 1;
						}
						//Check existence of scene
						if (tempScene.getExistence() == false) {
							tempScene.setExistence();
							sceneCountWorld += 1;
							insertScene(tempScene, sceneCountWorld, 0, dbNameString, chtrList);
							sceneCountersWorld(dbNameString, sceneCountWorld, "write");
							break;
						}
						//If the character exists, then it is simply updated. Reset chaCountWorld after.
						else if (tempScene.getExistence() == true) {
							insertScene(tempScene, sceneCountWorld, 1, dbNameString, chtrList);
							sceneCountWorld = sceneCountersWorld(dbNameString, 0, "read");
							break;
						}
					}
					//Load Scene. Character load(s) handled here, rest handled in Scene.cpp
					else if (inputSCE == "load") {
						tempScene.~Scene();
						Character tempChtrScene;
						std::vector <std::string> chtrTokens;
						int tempID = 0;
						std::string tempCharacter;
						chtrList = "";
						//std::stringstream myStream;
						selectFrom("ID,SCENE_NAME,CHARACTERS,NUM_CRCTRS", "SCENE", sceneCountWorld, 0, dbNameString, true);
						int idLoadChoice = tempSceneCount = inputInt() - 1;
						if (idLoadChoice < 0 || idLoadChoice > chaCountWorld) {
							std::cout << "Load Cancelled" << std::endl;
							break;
						}
						//LOAD CHTRS//
						//External from dbInteract.cpp. Returns from callback used in selectFrom if printOnly = false
						extern std::vector <std::string> returnCount;
						//Select Return
						selectFrom("CHARACTERS", "SCENE", 1, idLoadChoice, dbNameString, false);
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
							
							std::stringstream myStream(t);
							myStream >> tempID;
							//myStream >> tempCharacter;
							tempID -= 1;
							
							selectFrom("ID,NAME,AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, tempID, dbNameString, false);
							tempChtrScene.setCharacterFromDb(returnCount);
							tempScene.setCharacters(tempChtrScene);
							returnCount.clear();
							tempChtrScene.~Character();
						}
						//LOAD REST//
						selectFrom("LOCATION,TIME_DATE,SCENE_NAME,GEN_DSCRPT,NOTES,SCENE_NUM,NUM_CRCTRS,EXISTS_BOOL","SCENE",1,idLoadChoice,dbNameString,false);
						tempScene.setSceneFromDb(returnCount);
						returnCount.clear();
						fromLoad = true;
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

//Safley input integer, and parse.
int inputInt()
{
	std::string input = "";
	int id;
	while (true) {
		std::cout << "Please enter a valid number: ";
		std::getline(std::cin, input);
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
	std::cout << "Scenes in Chapter: " << chapter.getNumberOfScenes() << std::endl;
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
	std::cout << "Description: ";
	std::cout << ngi.getDescription() << std::endl;
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

